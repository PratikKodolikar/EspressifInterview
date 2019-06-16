
//Aadhar Card Problem


#include<iostream>
#include<limits>
using namespace std;
#define size 10

class node
{
     public:
    long int aadhar;
    string fname;
    string gname;
    string lname;
    string gen;
    int age;
    int blacklist;
    long int ph;
     node *next;
 
    node()
    {
        next=NULL;
        aadhar=0;
        age=0;
    }
   
        
        node(long int k,int age)
    {
        next=NULL;
        aadhar=k;
        this->age=age;
        
    }
    
    friend class Hash;
};

class Hash{

public:
node *chain[size];
void init()
{
    int i;
    for(i = 0; i < size; i++)
        chain[i] = NULL;
}

void insert(long int value)
{
    int a,b;
    string namef,namel,nameg;
    cout<<"enter first name";
    cin>>namef;
    cout<<"\n enter guardian name";
    cin>>nameg;
    cout<<"\n enter last name";
    cin>>namel;
    cout<<"\n enter age";
    cin>>a;
cout<<"\n Enter blacklist status 1 for blacklisted 0 for clear";
cin>>b;
    //create a newnode with value
    node *newNode = new node(value,a);
    newNode->fname=namef;
    newNode->lname=namel;
    newNode->gname=nameg;
    newNode->blacklist=b;
    //calculate hash key
    int key = value % size;

    //check if chain[key] is empty
    if(chain[key] == NULL)
        chain[key] = newNode;
    //collision
    else
    {
        //add the node at the end of chain[key].
        node *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

void print()
{
    int i;

    for(i = 0; i < size; i++)
    {
         node *temp = chain[i];
        cout<<"chain["<<i<<"]-->";
        while(temp)
        {
            cout<<temp->aadhar<<","<<temp->fname<<" "<<temp->lname<<","<<temp->age<<"\t";
            temp = temp->next;
        }
        cout<<endl;
           }
}
//For searching for details of a person
int search(long int value)
{
    int key = value % size;
     node *temp = chain[key];
    while(temp)
    {
        if(temp->aadhar==value)
            return 1;
        temp = temp->next;
    }
    return 0;
}
//For deletion
int del(long int value)
{
    int key = value % size;
     node *temp = chain[key];
     node *ele;
    if(temp != NULL)
    {
        if(temp->aadhar== value)
        {
            ele = temp;
            temp = temp->next;
chain[key]=temp;
            delete ele;
            cout<<"\n Deleted";
return 1;        }
        else
        {
            while(temp->next)
            {
                if(temp->next->aadhar == value)
                {
                    ele = temp->next;
                    temp->next = temp->next->next;
                    delete ele;
cout<<"\n Deleted";
                    return 1;
                }
                temp = temp->next;
            }
        }
    }

    return 0;
}
//For telephone assignment
void check(long int y)
{
long int tel;
int key = y % size;
     node *temp = chain[key];
while(temp)
{
if(temp->aadhar==y)
{
  if(temp->blacklist==0)
{
  cout<<"\n Enter the telephone number";
cin>>tel;
temp->ph=tel;
cout<<"\n Telephone assigned";



}
else
{
cout<<"\n Blacklisted. Prohibited"<<endl;

return;
}



}
temp=temp->next;


}




}


void printfinal()
{
    int i;

    for(i = 0; i < size; i++)
    {
         node *temp = chain[i];
        cout<<"chain["<<i<<"]-->";
        while(temp)
        {
            cout<<temp->aadhar<<","<<temp->fname<<" "<<temp->lname<<","<<temp->age<<"\t"<<temp->ph;
            temp = temp->next;
        }
        cout<<endl;
}

}
};




int main()
{
    Hash h;
    //init array of list to NULL
    h.init();
    int m=1;
    long int k,d;
    while(m!=0)
    {
        cout<<"\nEnter aadhar number";
        cin>>k;
while(1)
{
if(cin.fail())
{
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(),'\n');
cout<<"\nWrong Entry;Enter valid type!"<<endl;
cin>>k;
}
if(!cin.fail())
break;
}
        h.insert(k);
        cout<<"\n Enter another?1/0 ";
        cin>>m;
    }
    
    h.print();
    long int l;
    long int l1;
    cout<<"\nEnter aadhar id to be searched ";
    cin>>l;
    int g=h.search(l);
if(g==1)
{
cout<<"\n Found";
}
else if(g==0)
{
cout<<"\n Not Found";
}
    cout<<"\nEnter number to be deleted";
    cin>>l1;
    h.del(l1);


cout<<"\n For telephone";
int n;
do
{
cout<<"\n Enter aadhar number";
cin>>d;
h.check(d);
cout<<"\n Want to check another? \n Enter 1 for yes 0 for no";
cin>>n;
}while(n!=0);
h.printfinal();
    return 0;
}


