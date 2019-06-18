#include<iostream>
#include<cmath>
using namespace std;
#define Max 3
class Node{
	int data;
	Node *next,*down;
	public:
		
		Node(){
			data=0;
			next=down=NULL;
		}
		
		Node(int d){
			data=d;
			next=down=NULL;
		}
		friend class LinkedList;
};
class LinkedList{
	Node *head;
	int theMatrix[Max][Max];
	public:
		LinkedList(){
			head=NULL;
			for(int i=0;i<Max;i++)
				for(int j=0;j<Max;j++)
					theMatrix[i][j]=0;
		}
		
		void getMatrix(){
			for(int i=0;i<Max;i++){
				for(int j=0;j<Max;j++){
					cout<<"Enter the element Matrix["<<i<<"]["<<j<<"]: ";
					do{
						cin>>theMatrix[i][j];
					}while(isnan(theMatrix[i][j]));
				}
			}
		}
		
		void displayMatrix(){
			for(int i=0;i<Max;i++){
				for(int j=0;j<Max;j++){
					cout<<theMatrix[i][j]<<"\t";
				}
				cout<<endl;
			}
		}
		
	void createList(){
		Node *temp1=head;
		Node *temp2=head;
		for(int i=0;i<Max;i++){
			temp1=temp2;									//temp2 points to the first element of the row
			for(int j=0;j<Max;j++){
				if(i!=0){									//For second row onwards
					Node *new1 = new Node(theMatrix[i][j]);	
					if(j == 0){
						temp2 = new1;						//temp2 holds the first element
						temp1->down = new1;
					}
					else{
						temp1->down->next = new1;			//linking of nodes in the row
						temp1 = temp1->next;				
						temp1->down = new1;					//linking of nodes in the coloumn
					}					
				}
				else{										//Creation of first row
					Node *new1 = new Node(theMatrix[i][j]);
					if(temp1 == NULL){
						head=new1;							//head is assigned to the first node
						temp1 = new1;
						temp2 = new1;
					}
					else{
						temp1->next = new1;
						temp1 = temp1->next;				//linking of the elements in the row
					}
				}
			}
		}
	}
	
	void displayList(){
		Node *temp1=head;
		Node *temp2=head;
		while(temp2!=NULL){
			temp1=temp2;
			while(temp1!=NULL){
				cout<<temp1->data<<"\t";
				temp1=temp1->next;
			}
			cout<<endl;
			temp2=temp2->down;
		}
	}

	void transpose(){
		Node *temp1=head;						//travel horizontally
		Node *temp2=head;						//travel vertically
		Node *temp3=head;						//travel diagonally
		while(temp3!=NULL){
			temp1=temp3->next;
			temp2=temp3->down;
			while(temp1!=NULL){
				int temp=temp1->data;			//1
				temp1->data=temp2->data;		//2
				temp2->data=temp;				//3 {3 steps to swap data}
				temp1=temp1->next;
				temp2=temp2->down;
			}
			if(temp3->next!=NULL){				
			temp3=temp3->down->next;			//travel diagonally to the next node.
		}
		else
			break;								//terminate
		}
	}
	
	int perimeter(){
		Node *temp1,*temp2;
		temp1 = head;
		temp2 = head;
		int p = 0;
		p += temp1->data;						//first node
		do{
			temp1 = temp1->next;
			temp2 = temp2->down;
			p += temp1->data + temp2->data;
		}while(temp1->next!=NULL);				//travel along the edges {temp1: horizontally, temp2: vertically}
		do{
			temp1 = temp1->down;
			temp2 = temp2->next;
			p += temp1->data + temp2->data;
		}while(temp1->down!=NULL);				//travel along the edges {temp2: horizontally, temp1: vertically}
		p = p - temp2->data;					//last node gets added twice
		return p;
	}

	int diagonal(){
		Node *temp1 = head;
		int d=0;
		do{
			d += temp1->data;
			temp1 = temp1->next->down;
		}while(temp1->next!=NULL);
		d += temp1->data;
		return d;
	}
};
int main(){
	LinkedList l1;
	l1.getMatrix();
	cout<<"The matrix is: "<<endl;
	l1.displayMatrix();
	l1.createList();	
	cout<<"The List is: "<<endl;
	l1.displayList();
	l1.transpose();
	cout<<"The transpose is: "<<endl;
	l1.displayList();
	cout<<"The perimeter is: "<<l1.perimeter()<<endl;
	cout<<"The diagonal is: "<<l1.diagonal()<<endl;
}

