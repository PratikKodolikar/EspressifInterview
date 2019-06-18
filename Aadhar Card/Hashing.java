package fileManagement;

class Hashing {

	public static long getId(String string) {
	    
		int key1 = 1000,key2 = 1000,key3 = 1000;
		int size = string.length(),looper;
		
	    for(looper = 0 ; looper < (int)(size / 3) ;looper++)
	    {
	    	key1 = key1 + (string.charAt(looper)*100);
		key1 = key1 % 10000;
	    }
	    if(key1 < 1000)
		key1 += 1000;
	    
	    for(; looper < (int)(size / 3)*2 ;looper++)
	    {
	    	key2 = key2 + (string.charAt(looper)*100);
		key2 = key2 % 10000;
	    }
	    
	    for(; looper < size ;looper++)
	    {
	    	key3 = key3 + (string.charAt(looper)*100);
		key3 = key3 % 10000;
	    }
	    
	    long id = 0;
	    
	    id += key1*100000000L;
	    id += key2*10000;
	    id += key3;
	    
	    return id;
		
	}
	
	public static int getPosition(long id) {
		
		long temp = id,temp1;
		int key = 0;
		int counter = 0;
		while(counter<3)
		{	
			temp1 = temp%10000;
			key += temp1;
			temp = temp/10000;
			counter++;
		}
		return key%101;
	}
	
	public static int getIndexPosition(String key) {
		
		int buf = 0;
		
		for(int i=0; i<key.length(); i++)
			buf += key.charAt(i);
		
		return buf%101;
		
	}

}
