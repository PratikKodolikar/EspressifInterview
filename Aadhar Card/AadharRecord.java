package fileManagement;

class AadharRecord {
	
	private long mAadharId;			//12 digits -> saved as 24 bytes
	private String mFirstName;		//30 chars -> 60 bytes
	private String mMiddleName;		//30 chars -> 60 bytes
	private String mLastName; 		//30 chars -> 60 bytes

	public static final int size = 111 - 4;
	
	public AadharRecord(String rec) {
		fromString(rec);
	}
	
	//constructor for Aadhar record 
	public AadharRecord (long aadharId, String firstName, String middleName, String lastName) {
		this.mAadharId = aadharId;
		this.mFirstName = String.format("%" + 30 + "." + 30 + "s", firstName);
		this.mMiddleName = String.format("%" + 30 + "." + 30 + "s", middleName);
		this.mLastName = String.format("%" + 30 + "." + 30 + "s", lastName);
	
	}
	
	//getters
	public final long getAadharId () {
		return this.mAadharId;
	}
	
	public final String getFirstName () {
		return this.mFirstName.replaceAll(" ", "");
	}
	
	public final String getMiddleName () {
		return this.mMiddleName.replaceAll(" ", "");
	}
	
	public final String getLastName () {
		return this.mLastName.replaceAll(" ", "");
	}
	
	//function to calculate size
	public final int size () {
		return this.toString().length();
	}
	
	//function to convert record to string
	public final String toString () {
		return new String(Long.valueOf(mAadharId) + "@" + mFirstName + "@" + mMiddleName + "@" + mLastName );
	}

	//function to convert string to record
	public void fromString (String rec) {
		String[] str = rec.split("@", 4);
		
		for (String s : str)
			System.out.println(s);
		
		System.out.println("ID = ="+str[0]);
		this.mAadharId = Long.parseLong(str[0]);
		this.mFirstName = str[1];
		this.mMiddleName = str[2];
		this.mLastName = str[3];

	}
	
}
