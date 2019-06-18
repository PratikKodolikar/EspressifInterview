#ifndef TWODLINKEDLIST_H
#define TWODLINKEDLIST_H

class Node
{
    private:

        int data;
        Node* next;
        Node* down;

    public:

        Node();

        void setData(int newData);
        int getData();

        void setNext(Node* newNode);
        Node* getNext();

        void setDown(Node* newNode);
        Node* getDown();

        ~Node();
};

class twoDLinkedList
{
    private:

        Node* head;
        int sqrMatrix[3][3];
        int noCols;
        int noRows;
        int perimeter;
        int diagonalSum;
    public:

        twoDLinkedList();

        void setMatrixElement(int row,int col,int value);
        int getMatrixElement(int row,int col);

        int getPerimeter();
        int getDiagonalSum();

        void setHead(Node* temp);

        void reset();

        void create2DList();
        void setMatrix();
        void calPerimeter();
        void sumDiagonal();
        void transpose();
        void transposeMatrix();

        ~twoDLinkedList();
};

#endif // TWODLINKEDLIST_H

