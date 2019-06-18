#include "twodlinkedlist.h"
#include<iostream>
#include<queue>

using namespace std;

twoDLinkedList :: twoDLinkedList()
{
    head = nullptr;
    noRows = 3;
    noCols = 3;
    perimeter = 0;
    diagonalSum = 0;
    setMatrix();
}

void twoDLinkedList :: setMatrix()
{
    int countRow,countCol;
    for(countRow = 0 ; countRow < noRows ; countRow++)
    {
         for(countCol = 0 ; countCol < noCols ; countCol++)
         {
             sqrMatrix[countRow][countCol] = 0;
         }
    }
}

void twoDLinkedList :: setMatrixElement(int row, int col, int value)
{
    if(row>=0 && row<3 && col>=0 && col<3)
    {
        sqrMatrix[row][col] = value;
    }
    else
    {
        sqrMatrix[row][col]  = 0;
    }
}

int twoDLinkedList :: getMatrixElement(int row, int col)
{
    return sqrMatrix[row][col];
}

int twoDLinkedList :: getPerimeter()
{
    return perimeter;
}

int twoDLinkedList :: getDiagonalSum()
{
    return diagonalSum;
}

void twoDLinkedList :: setHead(Node* temp)
{
    head = temp;
}

void twoDLinkedList :: create2DList()
{
    int countRow,countCol;
    queue<Node*> Q;
    Node* prev = nullptr;
    Node* node = nullptr;
    Node* holder = nullptr;
    head = nullptr;

    for(countRow = 0 ; countRow < noRows ;countRow++)
    {
        prev = nullptr;
        for(countCol = 0 ; countCol < noCols ;countCol++)
        {
            node  = new Node;
            node->setData(sqrMatrix[countRow][countCol]);

            if(head == nullptr)
            {
                head = node;
            }

            if(prev != nullptr)
            {
                prev->setNext(node);
            }

            prev = node;

            if(Q.empty() == false && countRow != 0)
            {
                holder = Q.front();
                Q.pop();
                holder->setDown(node);
            }

            Q.push(node);
        }
    }
}

void twoDLinkedList :: calPerimeter()
{
    Node* temp1;
    Node* temp2;

    temp1 = head;
    temp2 = head->getDown();

    while(temp1->getNext() != nullptr)
    {
        perimeter += temp1->getData();
        temp1 = temp1->getNext();
    }

    while(temp1->getDown() != nullptr)
    {
         perimeter += temp1->getData();
         temp1 =  temp1->getDown();
    }

     perimeter += temp1->getData();

    while(temp2->getDown() != nullptr)
    {
        perimeter += temp2->getData();
        temp2 = temp2->getDown();
    }

    while(temp2->getNext() != nullptr)
    {
        perimeter += temp2->getData();
        temp2 = temp2->getNext();
    }
}

void twoDLinkedList :: sumDiagonal()
{
    Node* temp1 = nullptr;

    temp1 = head;

    while(temp1->getNext() != nullptr)
    {
        diagonalSum += temp1->getData();
        temp1 = temp1->getNext();
        temp1 = temp1->getDown();
    }
    diagonalSum+=temp1->getData();
}

void twoDLinkedList :: transpose()
{
    queue<Node*> Q;
    Node* temp1 = nullptr;
    Node* temp2 = nullptr;

    temp1 = head;

    while(temp1 != nullptr)
    {
        temp2 = temp1;
        while(temp2 != nullptr)
        {
            Q.push(temp2);
            temp2 = temp2->getNext();
        }
        temp1 = temp1->getDown();
    }

    while(Q.empty() == false)
    {
        temp1 = Q.front();
        Q.pop();
        temp2 = temp1->getNext();
        temp1->setNext(temp1->getDown());
        temp1->setDown(temp2);
    }
}

void twoDLinkedList :: transposeMatrix()
{
    int trans[3][3];
    int countRow,countCol;

    for(countRow = 0;countRow < noRows;countRow++)
    {
        for(countCol = 0;countCol < noCols;countCol++)
        {
            trans[countCol][countRow] = sqrMatrix[countRow][countCol];
        }
    }

    for(countRow = 0;countRow < noRows;countRow++)
    {
        for(countCol = 0;countCol < noCols;countCol++)
        {
            sqrMatrix[countRow][countCol] = trans[countRow][countCol];
        }
    }
}

void twoDLinkedList :: reset()
{
    perimeter = 0;
    diagonalSum = 0;
}

twoDLinkedList :: ~twoDLinkedList()
{
    delete head;
}

Node :: Node()
{
    data = 0;
    next = nullptr;
    down = nullptr;
}

void Node :: setData(int newData)
{
    data = newData;
}

int Node :: getData()
{
    return data;
}

void Node :: setNext(Node* newNode)
{
    next = newNode;
}

Node* Node :: getNext()
{
    return next;
}

void Node :: setDown(Node* newNode)
{
    down = newNode;
}

Node* Node :: getDown()
{
    return down;
}

Node :: ~Node()
{
    delete this;
}

