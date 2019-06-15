#include<iostream>
using namespace std;
class node
{
    int data;
    node *right, *down;
public:
    node()
    {
        data=0;
        right=down=NULL;
    }
    friend class matrix;
};
class matrix
{
    float mat[3][3];
    float trans[3][3];
public:
    void input();
    node* newNode(int d);
    node* constructLinkedMatrix(int i);
    void display(node* head);
    void transpose();
    float ComputeSum();
    float ComputeSumSquare();

};
void matrix::input()
{
     for(int i=0;i<3;i++)
     {
         for(int j=0;j<3;j++)
            cin>>mat[i][j];
     }
}
node* matrix::newNode(int d)
{
    node* temp = new node;
    temp->data = d;
    temp->right = temp->down = NULL;
    return temp;
}
node* matrix::constructLinkedMatrix(int k)
{
    node* mainhead = NULL;          // stores the head of the linked list
    node* head[3];                            // stores the head of linked lists of each row
    node *righttemp, *newptr;

    // Firstly, we create m linked lists
    // by setting all the right nodes of every row
    for (int i = 0; i < 3; i++)
    {
        head[i] = NULL;                    // initially set the head of ith row as NULL
        for (int j = 0; j < 3; j++)
        {
            if(k==0)
            {
                newptr = newNode(mat[i][j]);
            }
            else
            {
                newptr = newNode(trans[i][j]);
            }
            if (!mainhead)                    // stores the mat[0][0] node as, the mainhead of the linked list
                mainhead = newptr;
            if (!head[i])
                head[i] = newptr;
            else
                righttemp->right = newptr;

            righttemp = newptr;
        }
    }
    /* Then, for every ith and (i+1)th list,
     we set the down pointers of
     every node of ith list
    with its corresponding
     node of (i+1)th list*/
    for (int i = 0; i < 3 - 1; i++)//row-1
    {
            node *temp1 = head[i], *temp2 = head[i + 1];
            while (temp1 && temp2)
            {
                temp1->down = temp2;
                temp1 = temp1->right;
                temp2 = temp2->right;
            }
    }

    // return the mainhead pointer of the linked list
    return mainhead;
}
void matrix::display(node* head)
{
    node *rp, *dp = head;
     while (dp)
    {
        rp = dp;

        while (rp)              // loop until the right pointer is not NULL
        {
            cout <<"\t "<<rp->data<< "    --> ";
            rp = rp->right;
            if(rp==NULL)
            {
                cout<<"NULL";
                break;
            }
        }
        cout <<"\n\n";
        dp = dp->down;
    }
}
float matrix::ComputeSumSquare()
{
    float res;
    int i,j;
    for(i=0;i<3;i++)
    {
        if(i==0 || i==2)
        {
            for(j=0;j<3;j++)
            {
                res+=mat[i][j];
            }
        }
        else
        {
            for(j=0;j<3;j++)
            {
                if(j==0 || j==2)
                {
                    res+=mat[i][j];
                }
            }
        }
    }
    return res;
}
float matrix::ComputeSum()
{
    float res;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
                res+=mat[i][j];
            }
        }
    }
     return res;
}
void matrix::transpose()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            trans[i][j]=mat[j][i];
        }
    }
}
int main()
{
    matrix m;
    int ch;
    float result,perimeter;
    node *head;
    int flag=0;
    do
    {
        cout<<"\n\n\t*** MENU ***\n\n\t1) CREATE 2D LINKED LIST\n\t2) COMPUTE PERIMETER\n\t3) SUM OF DIAGONAL ELEMENTS\n\t4) TRANPOSE\n\t5) EXIT\n\n\tENTER YOUR CHOICE :-";
        cin>>ch;
        switch(ch)
        {
        case 1:
            m.input();
            head =m.constructLinkedMatrix(0);
            cout<<"\n\t2D LINKED LIST :-";
            cout<<"\n\n";
            m.display(head);
            flag=1;
            break;
        case 2:
            if(flag==0)
            {
                cout<<"\n\tCREATE LIST FIRST.!!!";
            }
            else
            {
                perimeter=m.ComputeSumSquare();
                cout<<"\n\tTHE PERIMETER OF ELEMENTS FORMING THE SQUARE :-"<<perimeter;
            }
            break;
        case 3:
            if(flag==0)
            {
                cout<<"\n\tCREATE LIST FIRST.!!!";
            }
            else
            {
                result=m.ComputeSum();
                cout<<"\n\tSUM OF DIAGONAL ELEMENTS :-"<<result;
            }
            break;
        case 4:
            if(flag==0)
            {
                cout<<"\n\tCREATE LIST FIRST.!!!";
            }
            else
            {
                cout<<"\n\tTRANPOSE OF LIST :-";
                cout<<"\n\n";
                m.transpose();
                head =m.constructLinkedMatrix(1);
                m.display(head);
                m.transpose();
                head =m.constructLinkedMatrix(1);
            }
            break;
        case 5:
            cout<<"\n\t*** PROGRAM SUCCESSFULLY TERMINATED ***";
            break;
        default:
            cout<<"\n\tINVALID CHOICE ENTERED,ENTER VALID CHOICE (1-4) ONLY";
            break;
        }
    }while(ch!=5);
    return 0;
}
