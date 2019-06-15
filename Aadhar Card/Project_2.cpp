#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;
struct aadhar {
	char fname[20];
	char guard[20];
	char lname[20];
	long long int id;
	int chain; 
	int blist;
};

class record{

	aadhar ag;
	aadhar ap;

public:
	record();
	virtual ~record();
	inline int index_calc(long long int);
	void init();
	void create();
	void display();
	void add_record();
	int search_record(long long int);
	int modify_record(long long int);
	void search_recordn();
	int phone_record(long long int);
	void delete_record();
	
};

record::record() {
	ag.chain=-1;
	ap.chain=-1;
}

record::~record() {
}

void record::init()
{
	ofstream fout;
	fout.open("data.dat",ios::out |ios::binary );
			ap.fname[0]='$';
			ap.id=-1;
			ap.lname[0]='$';
			ap.guard[0]='$';
			ap.chain=-1;
			ap.blist=-1;
			for(int i=0;i<10;i++)
				fout.write((char*)&ap,sizeof(ap));

			fout.close();
}

inline int record::index_calc(long long int x)
{
	return(x%10);
}

void record::create()
{
	fstream fp,fp2;

	int index,temp2,temp;

	fp.open("data.dat",ios::in|ios::out|ios::binary); 
	fp2.open("data.dat",ios::in|ios::binary); 
	label1:cout<<"Enter name on aadhar card :";
	cin>>ap.fname;
	cout<<"Enter id of aadhar card:";
	label:                          					//Adhaar ID input Validation
	cin>>ap.id;
	if(ap.id<100000000000 || ap.id>999999999999){
		cout<<"invalid aadhar id!!Enter again: ";
		goto label;
		}
    	while(fp2.read((char*)&ag,sizeof(ag)))
	{
		if(ag.id==ap.id){
			cout<<"id already exists..Please enter details again!";
			goto label1;
			}
	}
	cout<<"Enter surname on aadhar card :";
	cin>>ap.lname;
	cout<<"Enter guardian on aadhar card :";
	cin>>ap.guard;
	cout<<"Is the id blacklisted??(0/1):";
	cin>>ap.blist;
	index=index_calc(ap.id);
	fp.seekg((sizeof(ag))*index,ios::beg);
	fp.read((char*)&ag,sizeof(ag));
	
	
	if(ag.id==-1)
	{
		fp.seekp((sizeof(ap))*index,ios::beg);
		fp.write((char*)&ap,sizeof(ap));
		return;
	}

	temp2=index;
	while(temp2!=index_calc(ag.id) && ag.id!=-1)
	{
			index=(index+1)%10;
			fp.seekg((sizeof(ag))*index,ios::beg);
			fp.read((char*)&ag,sizeof(ag));
	}

	while(ag.chain!=-1) //Now using chain bits go till end of chain for given index
	{
				index=ag.chain;
				fp.seekg((sizeof(ag))*index,ios::beg);
				fp.read((char*)&ag,sizeof(ag));
	}

	temp=index;
	fp.seekg((sizeof(ag))*temp,ios::beg);
	fp.read((char*)&ag,sizeof(ag));
		while(ag.id!=-1) //Now increment index by one till we get empty place to store new record
			{
				temp=(temp+1)%10;
				fp.seekg((sizeof(ag))*temp,ios::beg);
				fp.read((char*)&ag,sizeof(ag));

			}

	if(index!=temp)
	{
		fp.seekg((sizeof(ag))*index,ios::beg);
		fp.read((char*)&ag,sizeof(ag));
		ag.chain=temp;
		fp.seekp((sizeof(ag))*index,ios::beg);
		fp.write((char*)&ag,sizeof(ag));

	}

	fp.seekp((sizeof(ap))*temp,ios::beg);
	fp.write((char*)&ap,sizeof(ap));



	fp.close();
	fp2.close();
}


void record::display()
{
	ifstream fin;
	fin.open("data.dat",ios::in|ios::binary);

	cout<<"----------------------------------------------------------------\n";
	cout<<"|    AADHAR ID   |    First name    |     Last name     |   Guardian name   |    Chain    |\n";
	cout<<"----------------------------------------------------------------\n";

	while(fin.read((char*)&ag,sizeof(ag)))
	{
		 cout<<"|"<<setw(14)<<ag.id<<"|"<<setw(11)<<ag.fname<<"|"<<setw(11)<<ag.lname<<"|"<<setw(11)<<ag.guard<<"|"<<setw(11)<<ag.chain<<"|"<<endl;
	}

	cout<<"----------------------------------------------------------------\n";

	fin.close();
}
void record::search_recordn()
{
	ifstream fp;
	int i,j=0,count=0,n=0;
	char name[20];
	cout<<"Enter the first name you want to search(any number of chracters):";
	cin>>name;
	while(name[j]!='\0'){
		j++;
		n++;
		}
	fp.open("data.dat",ios::in|ios::binary);
	while(fp.read((char*)&ag,sizeof(ag))){
	j=0;
	i=0;
	count=0;
		//cout<<ag.fname;
		while(name[j]!='\0' && ag.fname[i]!='\0'){
			if(name[j]==ag.fname[i]){
				//flag=1;
				cout<<count<<endl;
				count++;
				j++;
				i++;
				}
			else if(name[j]!=ag.fname[i]){
				//flag=2;
				j=0;
				count=0;
				i++;
				}
	}
	if(count==n){
		 cout<<"|"<<setw(14)<<ag.id<<"|"<<setw(11)<<ag.fname<<"|"<<setw(11)<<ag.lname<<"|"<<setw(11)<<ag.guard<<"|"<<setw(11)<<ag.chain<<"|"<<endl;
		}
		
	}
	fp.close();
	fp.open("data.dat",ios::in|ios::binary);
	while(fp.read((char*)&ag,sizeof(ag))){
	j=0;
	i=0;
	count=0;
		//cout<<ag.fname;
		while(name[j]!='\0' && ag.lname[i]!='\0'){
			if(name[j]==ag.lname[i]){
				//flag=1;
				cout<<count<<endl;
				count++;
				j++;
				i++;
				}
			else if(name[j]!=ag.lname[i]){
				//flag=2;
				j=0;
				count=0;
				i++;
				}
	}
	if(count==n){
		 cout<<"|"<<setw(14)<<ag.id<<"|"<<setw(11)<<ag.fname<<"|"<<setw(11)<<ag.lname<<"|"<<setw(11)<<ag.guard<<"|"<<setw(11)<<ag.chain<<"|"<<endl;
		}
		
	}
	fp.close();
	fp.open("data.dat",ios::in|ios::binary);
	while(fp.read((char*)&ag,sizeof(ag))){
	j=0;
	i=0;
	count=0;
		//cout<<ag.fname;
		while(name[j]!='\0' && ag.guard[i]!='\0'){
			if(name[j]==ag.guard[i]){
				//flag=1;
				cout<<count<<endl;
				count++;
				j++;
				i++;
				}
			else if(name[j]!=ag.guard[i]){
				//flag=2;
				j=0;
				count=0;
				i++;
				}
	}
	if(count==n){
		 cout<<"|"<<setw(14)<<ag.id<<"|"<<setw(11)<<ag.fname<<"|"<<setw(11)<<ag.lname<<"|"<<setw(11)<<ag.guard<<"|"<<setw(11)<<ag.chain<<"|"<<endl;
		}
		
	}
	fp.close();
	
}
int record::phone_record(long long int x){
	fstream fp;
	fp.open("data.dat",ios::in|ios::out|ios::binary);
	int index=index_calc(x);
	string name;
	cout<<"Enter first name of aadhar card : ";
	cin>>name;
	 while(fp.read((char*)&ag,sizeof(ag)))
		{
		if(ag.id==x){
			if(ag.blist==0){
				if(ag.fname==name){
					cout<<"----------------------------------------------------------------\n";
					cout<<"|   AADHAR ID    |       First name     |     Last name    |   Guardian name   |    Chain    |\n";
					cout<<"----------------------------------------------------------------\n";

					cout<<"|"<<setw(11)<<ag.id<<"|"<<setw(14)<<ag.fname<<"|"<<setw(11)<<ag.lname<<"|"<<setw(11)<<ag.guard<<"|"<<setw(11)<<ag.chain<<"|"<<endl;
					cout<<"----------------------------------------------------------------\n";
					cout<<"The phone number generated is 908765432"<<index<<" Please use this for further enquiry!";
					return 0;
						}
				else{
					cout<<"Id and first name do not match!!Please enter correct details!";
					return 0;
					}
				}
			else{
				cout<<"id is blacklisted!!";
				return 0;

			}

				}
			}
		cout<<"Record not found";
		return -1;
	
}
			


int record::search_record(long long int x)     //Search by ID
{

	fstream fp;
	fp.open("data.dat",ios::in|ios::binary);
	int index=index_calc(x);
	int i=-1;

		 while(fp.read((char*)&ag,sizeof(ag)))
		{
			i++;
			if(ag.id==x){
				cout<<"\n Record found at index "<<i;


					cout<<"----------------------------------------------------------------\n";
					cout<<"|     AADHAR ID    |       First name     |     Last name    |   Guardian name   |    Chain    |\n";
					cout<<"----------------------------------------------------------------\n";

					cout<<"|"<<setw(11)<<ag.id<<"|"<<setw(14)<<ag.fname<<"|"<<setw(11)<<ag.lname<<"|"<<setw(11)<<ag.guard<<"|"<<setw(11)<<ag.chain<<"|"<<endl;
					cout<<"----------------------------------------------------------------\n";

					return index;
				}
		}
		cout<<"Record not found";
		return -1;
}

int record::modify_record(long long int x)
{
		fstream fp;
		int ch,i=-1;
		fp.open("data.dat",ios::in|ios::out|ios::binary);

		int index=index_calc(x);
		
			 while(fp.read((char*)&ag,sizeof(ag)))
			{
				i++;
				if(ag.id==x){
				cout<<"\n Record found at index "<<i;
					cout<<"----------------------------------------------------------------\n";
					cout<<"|     AADHAR ID    |       First name     |     Last name    |   Guardian name   |    Chain    |\n";
					cout<<"----------------------------------------------------------------\n";

					cout<<"|"<<setw(11)<<ag.id<<"|"<<setw(14)<<ag.fname<<"|"<<setw(11)<<ag.lname<<"|"<<setw(11)<<ag.guard<<"|"<<setw(11)<<ag.chain<<"|"<<endl;
					cout<<"----------------------------------------------------------------\n";
					cout<<"\n\n\t---Select field to modify--- :\n1.first name\n2.last name\n3.guardian name\n4.Add to blacklist\n5.Remove from blacklist\n";
										cout<<"\n\n\tEnter choice : ";
										cin>>ch;

										switch(ch)
										{
											case 1:cout<<"Enter modified first name: ";
											cin>>ag.fname;
											break;

											case 2:cout<<"Enter modified last name: ";
											cin>>ag.lname;
											break;

											case 3:cout<<"Enter modified guardian name: ";
											cin>>ag.guard;
											break;
                                            
                                            case 4:
												   ag.blist=1;
												   cout<<"\nRecord Added to blacklist!!!";
												   break;
                                            case 5:
                                            	   ag.blist=0;
												   cout<<"\nRecord Removed from blacklist!!!";
												   break;

											default:	break;
										}

						fp.seekp((sizeof(ag))*index,ios::beg);
						fp.write((char*)&ag,sizeof(ag));
						return index;
				}
		}
			cout<<"Record not found";
			return -1;



}
void record::delete_record(){
	fstream fp;
	long long int x;
	int index,temp,j;
	fp.open("data.dat",ios::in|ios::out|ios::binary); 
	cout<<"Enter id of aadhar card to delete:";                        					
	cin>>x;
	index=index_calc(x);
	temp=index;
	fp.seekg((sizeof(ag))*index,ios::beg);
	fp.read((char*)&ag,sizeof(ag));
	if(ag.id==x){
		j=ag.chain;
		ag.id=-1;
		ag.chain=-1;
		ag.fname[0]='$';
		ag.lname[0]='$';
		ag.guard[0]='$';
		ag.blist=-1;
		fp.seekp((sizeof(ag))*index,ios::beg);
		fp.write((char*)&ag,sizeof(ag));
		fp.close();
		fp.open("data.dat",ios::in|ios::out|ios::binary); 
		index=0;
		while(index<10){
			if(ag.chain==index){
				ag.chain=j;
				break;
			}
			index++;
		}
		return;
	}
	fp.close();
	fp.open("data.dat",ios::in|ios::out|ios::binary); 
	index=0;	
	temp=0;
		while(index<10){
			temp=index;
			fp.seekg((sizeof(ag))*index,ios::beg);
			fp.read((char*)&ag,sizeof(ag));
			cout<<ag.id<<endl;
			if(ag.id==x){
				j=ag.chain;
				ag.id=-1;
				ag.chain=-1;
				ag.fname[0]='$';
				ag.lname[0]='$';
				ag.guard[0]='$';
				ag.blist=-1;
				fp.seekp((sizeof(ag))*index,ios::beg);
				fp.write((char*)&ag,sizeof(ag));
				break;
				}
			index++;
			}
		fp.close();
		fp.open("data.dat",ios::in|ios::out|ios::binary); 
		index=0;
		while(index<10){
			fp.seekg((sizeof(ag))*index,ios::beg);
			fp.read((char*)&ag,sizeof(ag));
			if(ag.chain==temp){
				ag.chain=j;
				fp.seekp((sizeof(ag))*index,ios::beg);
				fp.write((char*)&ag,sizeof(ag));
				break;
			}
			index++;
		}
	fp.close();
	return;
	cout<<"Id does not exist!!";
}
				
int main() {

	record s;
	int ch,n,i;
	long long int roll;
	char name[20];
	do
	{

			cout<<"\nMenu\n1:Create New Database \n2:Display records\n3:Add Record(s)\n4:Search Record By Id\n5:Modify Record\n6:Search Record By Name\n7:Allote phone number\n8:Delete record\n9:Exit\n";
			cout<<"\nEnter choice : ";
			cin>>ch;


	switch(ch)
	{

	case 1: s.init();
			cout<<"\n*** Database Created  Successfully*** \n";
			s.display();
			break;

	case 2: s.display();
			break;

	case 3: cout<<"Enter no of records you want to add :";
			cin>>n;
			for(i=1;i<=n;i++)
				s.create();

			cout<<"\n*** Records Added Successfully*** \n";
			s.display();
			break;

	case 4: s.display();
			cout<<"Enter id of user to search record: ";
			cin>>roll;
			s.search_record(roll);
			break;


	case 5: s.display();
			cout<<"Enter id of aadhar card to modify record: ";
				cin>>roll;
				if(s.modify_record(roll)!=-1)
				{
					cout<<"*** Record Successfully Modified ***\n";
					s.display();
				}


		    break;

	case 6:s.search_recordn();
		break;
	case 7:cout<<"Enter id of aadhar card : ";
		cin>>roll;
		s.phone_record(roll);
		break;
	case 8: s.delete_record();
		break;		
	case 9:break;
	}
	}while(ch!=9);


	return 0;
}
