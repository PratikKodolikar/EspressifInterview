package fileManagement;

import java.io.*;
import java.util.ArrayList;

class IndexFile extends RandomAccessFile {

	private String mIndexFileName;

	//constructor for index file
	public IndexFile (String indexFileName) throws IOException {
		
		super(indexFileName, "rw");
		
		this.mIndexFileName = indexFileName;
		
		//create a file with 101 records
		seek(8 * 101);
		writeInt(0);
		
	}
	
	//function to insert index
	public void insertIndex (String key, int position, AadharFile file ,int fileFlag ) throws IOException {
		
		int indexPosition = Hashing.getIndexPosition(key);
		
		seek(8 * indexPosition);
	
		if(readInt() <= 0) {			//if hashed position is empty
			seek(8 * indexPosition);
			
			writeInt(position);
			writeInt(-1);
			
		} else {						//if hashed position is full
			int prevIndexPosition = indexPosition;
			
			seek(8 * indexPosition);
			
			int posAtIndex = readInt();
			int chainAtIndex = readInt();
			String keyAtIndex = "NULL";
			
			if(fileFlag == 1) {
				keyAtIndex = file.readRecordAt(posAtIndex).getLastName();
			}
			else if(fileFlag == 2) {
				keyAtIndex = file.readRecordAt(posAtIndex).getMiddleName();
			}
			int hashAtIndex = Hashing.getIndexPosition(keyAtIndex);
			
			//hashed position is full and contain a record 
			//with different hash than the hashed position 
			if(hashAtIndex != indexPosition) {
			    
				System.out.println("posAtIndex = " + posAtIndex);
			    
			    int prevPosition = hashAtIndex;
			    seek(8 * prevPosition + 4);
			    int nextPos = readInt();
			    
			    //find previous position of the current hashed position
			    while(nextPos != indexPosition) {
				
			    	prevPosition = nextPos;
			    	seek(8 * nextPos + 4);
			    	nextPos = readInt();
			    }
			    
			    int curIndexPosition = indexPosition;	  
			    seek(8 * curIndexPosition);
			    
			    //find next empty position
			    while(readInt() > 0) {
			    	curIndexPosition++;
			    	if(curIndexPosition > 100)
			    		return;
			    	seek(8 * curIndexPosition);
			    }
			    System.out.println("Cur Pos = " + curIndexPosition);
			    
			    //write at next empty position
			    seek(8 * curIndexPosition);
			    writeInt(posAtIndex);
			    writeInt(chainAtIndex);
			    
			    //update link at previous position calculated earlier
			    seek(8 * prevPosition + 4);
			    writeInt(curIndexPosition);
			    
			    //write record at the hashed index position
			    seek(8 * indexPosition);
			    writeInt(position);
			    writeInt(-1);
			    
			} 
			else //hashed position contains record with correct hash  
			{
			
			    while(read() <= 0) {
			    	seek(8 * prevIndexPosition + 4);
			    	int nextIndexPosition = readInt();
				
			    	//chain is not set at hashed position
			    	if(nextIndexPosition == -1) {
			    		nextIndexPosition = prevIndexPosition + 1;
			    		seek(8 * nextIndexPosition);
			    		
			    		//find next empty position
			    		while(read() > 0) {
			    			nextIndexPosition++;
			    			if(nextIndexPosition > 100)
			    				return;
			    			seek(8 * nextIndexPosition);
			    		}
					
			    	//write the record at new empty position
					seek(8 * nextIndexPosition);
					writeInt(position);
					writeInt(-1);
					
					//update the chain of record present at original hashed position
					seek(8 * prevIndexPosition + 4);
					writeInt(nextIndexPosition);
					
					prevIndexPosition = nextIndexPosition;
					break;
				} 
			    else 	//follow the chain and update link of the the last record in chain 
				{
					seek(8 * nextIndexPosition);
					prevIndexPosition = nextIndexPosition;
				}
			    }
			}
			indexPosition = prevIndexPosition;
		}
		
		System.out.println("Inserted " + key + " at " + indexPosition);
		
	}	
	
	public void updateIndex (String key, int oldPosition,int newPosition, AadharFile file ) throws IOException {
		int indexPosition = Hashing.getIndexPosition(key);
		seek(8 * indexPosition);
		int check  = readInt();
		int next = readInt();
		int prev = indexPosition;
		while(check != oldPosition && next != -1)
		{
			seek(8 * next);
			check = readInt();
			prev = next;
			next = readInt();
		}
		if(next != -1)
		{	
			seek(prev * 8);
			writeInt(newPosition);
		}	
			
	}	
	
	public ArrayList<Integer> searchRecord(String key, AadharFile file) throws IOException {
		
		   System.out.println("checking key : " + key);
	    
		int indexPosition = Hashing.getIndexPosition(key);
		   System.out.println("indexPosition = " + indexPosition);
		   
		   test();
		   
		int traverse = indexPosition;
		ArrayList<Integer> pos = new ArrayList<Integer>();
		while(traverse != -1 /*&& traverse != 0*/)
		{
			System.out.println("traverse = " + traverse);
			seek(8 * traverse);
			pos.add(readInt());
			traverse = readInt();
		}
		
		return pos;
	}
	
	public void test () throws IOException {
		
		seek(0);
		for(int i=0; i<101; i++)
			System.out.println(i + " : " + readInt() + " <> " + readInt());
		
	}

}
