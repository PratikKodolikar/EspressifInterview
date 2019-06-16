#include<iostream>
using namespace std;
class node
{
        node *right;
        node *down;
        int data;
        public:
        node()
        {
                right=NULL;
                down=NULL;
                data=0;

        }
        friend class Matrix;

};
class Matrix
{
public:
        node *head;
        int m[3][3];

                Matrix()
                {
                        head=NULL;
                }
                void input() //utility function to accept the input
                {
                        cout<<"\n Enter the 3*3 matrix : ";
                        for(int i=0;i<=2;i++)
                        {
                                for(int j=0;j<3;j++)
                                {
                                        cin>>m[i][j];
                                }

                        }
                }
                node* create(node *x,int i,int j) //utility function for creation of the 2d linked list
                {
                        if(i>2||j>2) //3*3 matrix
                        {
                                return NULL;
                        }
                        else
                        {

                x=new node;
                x->data=m[i][j];
                x->right=create(x->right,i,j+1);
                x->down=create(x->down,i+1,j);
                return x;
                }
                }
                void display(node *x)//utility function to display of the 2D linked list
                {
                        node *t=x;
                        while(x)
                        {
                        t=x;
                                while(t)//to traverse all the elements in a particular row
                                {
                                        cout<<t->data<<" ";
                                        t=t->right;
                                }
                                cout<<endl;
                        x=x->down;
                        }

                }
                int diagonal(node *x)//utility function to find the sum of the diagonal
                {
                int sum=0,cnt=0;
                        while(1)
                        {
                                sum=sum+x->data;
                                if(x->right==NULL)
                                {
                                        break;
                                }
                                x=x->right->down;//to traverse the diagonal elements
                        }

                        return sum;

                }
                node* transpose(node *x)//utility function to find the transpose
                {

                        if(x!=NULL)
                        {

                                node *temp;
                                temp=x->right;
                                x->right=x->down;
                                x->down=temp;
                                x->right=transpose(x->right);
                                x->down=transpose(x->down);
                                return x;
                        }

                        else
                        {
                        return NULL;
                        }




                } 
                int perimeter(node *x)//utility function to find the perimeter
                                {
                                int sum=0;
                                node *rp = x;
                               

                                while(rp!=NULL)
                                {
                                  sum = sum + rp->data;
                                  if(rp->right!=NULL)
                                    {
                                     rp = rp->right;
                                     }
                                  else
                                    {
                                     rp = rp->down;
                                    }
                                 }
                                rp = x;
                                while(1)
                                {
                                
                                  if(rp->down!=NULL)
                                   {
                                    rp = rp->down;
                                    }
                                  else
                                   {
                                    rp = rp->right;
                                
                                     if(rp->right == NULL)
                                       {
                                         break;
                                       }
                                   }
                                   sum = sum +rp->data;
                                   }
                   return sum;

                                }


};
int main()
{
        Matrix obj;
        int n;
        int k =1;
        int a;
        cout<<"\n --------------------------------------------------------------------------------------------- ";
        cout<<"\n ";
        obj.input();
        obj.head=obj.create(obj.head,0,0);
       while(k==1)
       {
      cout<<"\n  Enter 1 to display the matrix .\n Enter 2 to display the transpose. \n Enter 3 to display the sum of the diagonal elements.\n Enter 4 to display the perimeter. ";
      cin>>n;
        switch(n)
        {
        case 1:
        
        obj.display(obj.head);
        break;
        case 2:
               	obj.head=obj.transpose(obj.head);
               	obj.display(obj.head);
              break;
        case 3:	
         a=obj.diagonal(obj.head);
        cout<<"\n The sum of the diagonal is : "<<a;
        break;
        case 4:
        a = obj.perimeter(obj.head);
        cout<<"\n The perimeter is : "<<a;
        break;
        default:
        cout<<"\n Wrong Input.";
        }
        cout<<"\n Enter 1 to continue and 0 to stop the execution: ";
                 cin>>k;
     
     return 0;
}
}