package com.brogrammers.java;

import java.io.*;
import java.util.*;

class AadharFile extends RandomAccessFile {

	private String mFileName;
	
	private IndexFile mLastNameIndexFile;
	
	private IndexFile mMiddleNameIndexFile;
	
	private int mRecordSize;
	
	//costructor for Aadhar File
	public AadharFile (String fileName) throws IOException {
		
		super(fileName, "rw");
		
		this.mFileName = fileName;
		this.mRecordSize = AadharRecord.size + 4;
		
		System.out.println("Opening file " + mFileName);
		
		System.out.println("mRecordSize = " + mRecordSize);

		//create main file with 101 records
		seek(mRecordSize * 101);
		writeInt(0);
		
		//create index file for last name
		this.mLastNameIndexFile = new IndexFile("LastNameIndex.dat");
		
		//create index file for middle name
		this.mMiddleNameIndexFile = new IndexFile("MiddleNameIndex.dat");
		
	}
	
	//function to insert record in aadhar main file
	public void insertRecord (AadharRecord record) throws IOException {
		
		int position = Hashing.getPosition(record.getAadharId());
		
		seek(mRecordSize * position);
	
		if(readInt() <= 0) {			//if hashed position is empty
			seek(mRecordSize * position);
			
			writeUTF(record.toString());
			writeInt(-1);
			
		} else {						//if hashed position is full
			int prevPosition = position;
			
			seek(mRecordSize * position);
			
			AadharRecord recordAtPos = new AadharRecord(readUTF());
			int chainAtPos = readInt();
			int hashAtPos = Hashing.getPosition(recordAtPos.getAadharId());
			
			//hashed position is full and contain a record 
			//with different hash than the hashed position 
			if(hashAtPos != position) {
			    			    
			    int prevPos = hashAtPos;
			    seek(mRecordSize * prevPos + AadharRecord.size);
			    int nextPos = readInt();
			    //find previous position of the current hashed position
			    while(nextPos != position) {
				
			    	prevPos = nextPos;
				seek(mRecordSize * prevPos + AadharRecord.size);
			    	nextPos = readInt();
			    }
			    System.out.println("Prev Pos = " + prevPos);
			    
			    //find next empty position
			    int curPos = position;	  
			    seek(mRecordSize * curPos);
			    while(readInt() > 0) {
			    	curPos++;
			    	if(curPos > 100)
				    return;
			    	seek(mRecordSize * curPos);
			    }
			    System.out.println("Cur Pos = " + curPos);
			    
			    //write at next empty position
			    seek(mRecordSize * curPos);
			    writeUTF(recordAtPos.toString());
			    writeInt(chainAtPos);
			    
			    //update link at previous position calculated earlier
			    seek(mRecordSize * prevPos + AadharRecord.size);
			    writeInt(curPos);
			    
			    //write record at the hashed index position
			    seek(mRecordSize * position);
			    writeUTF(record.toString());
			    writeInt(-1);
			    System.out.println(recordAtPos.getLastName());
			    System.out.println(position);
			    System.out.println(curPos);
			    
			    //update the middle and last name index file respectively
			    mLastNameIndexFile.updateIndex(recordAtPos.getLastName(),position + 1,curPos + 1,this);
			    mMiddleNameIndexFile.updateIndex(recordAtPos.getMiddleName(),position + 1,curPos + 1,this);
			    
			} else  //hashed position contains record with correct hash   
			{
			
			    while(read() <= 0) {
			    	seek(mRecordSize * prevPosition + AadharRecord.size);
			    	int nextPosition = readInt();
				
				System.out.println("nextPosition = " + nextPosition);
				
					//chain is not set at hashed position
			    	if(nextPosition == -1) {
			    		nextPosition = prevPosition + 1;
					
			    		seek(mRecordSize * nextPosition);
			    		
			    		//find next empty position
			    		
			    		while(read() > 0) {
			    			nextPosition = (nextPosition + 1) % 101;
			    			if(nextPosition == prevPosition)
			    				return;
			    			seek(mRecordSize * nextPosition);
			    		}
					
			    	//write the record at new empty position
					seek(mRecordSize * nextPosition);
					writeUTF(record.toString());
					writeInt(-1);
					
					//update the chain of record present at original hashed position
					seek(mRecordSize * prevPosition + AadharRecord.size);
					writeInt(nextPosition);
					
					prevPosition = nextPosition;
					break;
				} 
			    else //follow the chain and update link of the the last record in chain
				{
					seek(mRecordSize * nextPosition);
					prevPosition = nextPosition;
				}
			   }
			}
			position = prevPosition;
		}
		
		System.out.println("Inserted " + record + " at " + position);
        
		//insert the index in lasst and middle name index files respectively
		mLastNameIndexFile.insertIndex(record.getLastName(), position + 1, this ,1);
		
		mMiddleNameIndexFile.insertIndex(record.getMiddleName(), position + 1, this ,2);
		
		   test();
		
	}
	
	//function to read record present at the given position
	public final AadharRecord readRecordAt (int position) throws IOException {
	    
	    seek((position - 1) * (AadharRecord.size + 4));
	    
	    AadharRecord record = new AadharRecord(readUTF());
	    
	    if(record.getAadharId() <= 0)
		return new AadharRecord(0, "N/A", "N/A", "N/A");
	    
	    return record;
	}
	
	//function to search record in Aadhar file
	public final AadharRecord readRecord (long id) throws IOException {
		
		int position = Hashing.getPosition(id);
		   System.out.println("position = " + position);
		
		   test();
		   
		while(position != -1 && read() >= 0)	{	
			seek(position * mRecordSize);
			AadharRecord rec = new AadharRecord(readUTF());
			if(rec.getAadharId() == id)
				return rec;
			seek(position * mRecordSize);
			position = readInt();
			
		}	
		
		return new AadharRecord(0, "N/A", "N/A", "N/A");
	}

	public final String getFileName () {
		return mFileName;
	}
	
	public ArrayList<AadharRecord> searchByMiddleName (String middleName) throws IOException {
		
		ArrayList<Integer> list = mMiddleNameIndexFile.searchRecord(middleName, this);
		ArrayList<AadharRecord> recordList = new ArrayList<AadharRecord>();
		
		for(Integer pos : list) {
		    recordList.add(readRecordAt(pos));
		}
		
		return recordList;
		
	}
	
	public ArrayList<AadharRecord> searchByLastName (String lastName) throws IOException {
		
		ArrayList<Integer> list = mLastNameIndexFile.searchRecord(lastName, this);
		ArrayList<AadharRecord> recordList = new ArrayList<AadharRecord>();
		
		for(Integer pos : list) {
		    recordList.add(readRecordAt(pos));
		}
		
		return recordList;
		
	}
	
	//functions used for testing purpose
	public final void testIndex (int i) throws IOException {
	    if(i == 1)
		mLastNameIndexFile.test();
	    else if(i == 2)
		mMiddleNameIndexFile.test();
	}
	
	public void test () throws IOException {
		
		seek(0);
		for(int i=0; i<101; i++)
			System.out.println(i + " : " + readUTF() + " <> " + readInt());
		
	}

}