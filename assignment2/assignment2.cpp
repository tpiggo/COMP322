#include <iostream>
#include <map>
#include <cstdlib>
#include <time.h>
using namespace std;

class Node
{
    private:
        int data;
        Node *next;
        Node *previous;
    public:
        Node();
        Node(int data, Node *next, Node *previous);
        int getData();
        Node* getNext();
        void setNext(Node *next);
        void setPrevious(Node *previous);
        Node *getPrevious();
        void printNode();
};

/**
 * Constructor 
 * 
 */ 
Node::Node()
{
    this->next = NULL;
    this->previous = NULL;
    this->data = 0;
}

/**
 * Constructor 
 */ 
Node::Node(int data, Node *next, Node *previous)
{
    this->next = next;
    this->previous = previous;
    this->data = data;
}

int Node::getData()
{
    return this->data;
}

void Node::setNext(Node *next)
{
    this->next = next;
}

Node* Node::getNext()
{
    return this->next;
}

void Node::setPrevious(Node *previous)
{
    this->previous = previous;
}

Node *Node::getPrevious()
{
    return this->previous;
}

void Node::printNode()
{
    cout << "Data: " << this->data << " hasNext: " << (this->next != NULL) << " hasPrevious: " << (this->previous != NULL) << endl;
}

class DLLStructure
{
    private:
        Node *first = NULL, *last = NULL;
        int size, maxVal = INT32_MIN, minVal = INT32_MAX;
        void setMin();
        void setMax();
        void mergeSort();
    public:
        DLLStructure();
        DLLStructure(int array[], int size);
        ~DLLStructure();
        void printDLL();
        void printReverse();
        void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
        void InsertBefore(int valueToInsertBefore, int valueToBeInserted);
        void Delete(int value);
        void Sort();
        bool IsEmpty();
        int getHead();
        int getTail();
        int getSize();
        int getMax();
        int getMin();
};

/**
 * Private functions
 */ 

void DLLStructure::setMax()
{
    Node *cur = this->first;
    while (cur != NULL)
    {
        if (cur->getData() > this->maxVal)
            this->maxVal = cur->getData(); 
        cur = cur->getNext();
    }
}

void DLLStructure::setMin()
{
    Node *cur = this->first;
    while (cur != NULL)
    {
        if (cur->getData() < this->minVal)
            this->minVal = cur->getData(); 
        cur = cur->getNext();
    }
}


DLLStructure::DLLStructure()
{
    this->size = 0;
}

DLLStructure::DLLStructure(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        Node *newNode = new Node(array[i], NULL, this->last);
        // The list hasn't be initialized.
        if (this->first == NULL)
        {
            this->first = newNode;
        }
        // the list exists and we are adding a new node to the end.
        if (this->last != NULL)
        {
            this->last->setNext(newNode);
        }
        // set and get the min value
        if (this->minVal > array[i])
            this->minVal = array[i];
        if (this->maxVal < array[i])
            this->maxVal = array[i];
        this->last = newNode;
    }

    this->size = size;
}

DLLStructure::~DLLStructure()
{
    while (this->first->getNext() != NULL)
    {
        Node *temp = this->first; 
        this->first = this->first->getNext();
        this->first->setPrevious(NULL);
        delete temp;
    }
    // There is only one node left!
    Node *temp = this->first;
    this->first = NULL;
    this->last = NULL;
    delete temp;
}

void DLLStructure::printDLL()
{
    Node *temp = this->first;
    while (temp != NULL)
    {
        cout << temp->getData();
        if (temp->getNext() != NULL)
        {
            cout << " -> ";
        }
        temp = temp->getNext();
    }
    cout << endl;
}

void DLLStructure::printReverse()
{
    Node *temp = this->last;
    while (temp != NULL)
    {
        cout << temp->getData();
        if (temp->getPrevious() != NULL)
        {
            cout << " -> ";
        }
        temp = temp->getPrevious();
    }
    cout << endl;
}

void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted)
{
    bool inserted = false;
    Node *cur = this->first;
    while (cur != NULL)
    {
        if (cur->getData() == valueToInsertAfter)
        {
            Node *newNode = new Node(valueToBeInserted, cur->getNext(), cur);
            if (cur->getNext() != NULL)
            {
                cur->getNext()->setPrevious(newNode);
            }
            cur->setNext(newNode);
            inserted = true;
            break;
        }
        cur = cur->getNext();
    }
    // If we got here then we clearly didn't find the element in the list. Add to the end.
    if (!inserted)
    {
        Node *newNode = new Node(valueToBeInserted, NULL, this->last);
        this->last->setNext(newNode);
        this->last = this->last->getNext();
    }
    // increase the size
    this->size++;
    if (valueToBeInserted > this->maxVal)
        this->maxVal = valueToBeInserted;
    if (valueToBeInserted < this->minVal)
        this->minVal = valueToBeInserted;
}

void DLLStructure::InsertBefore(int valueToInsertBefore, int valueToBeInserted)
{
    bool inserted = false;
    if (this->first->getData() == valueToInsertBefore)
    {
        Node *newNode = new Node(valueToBeInserted, this->first, NULL);
        this->first->setPrevious(newNode);
        this->first = newNode;
        inserted = true;
        this->size++;
    } 
    else if (this->size > 1)
    {
        // Completely useless way of inserting a node.
        Node *cur = this->first;
        int valueAfter = this->first->getData();
        while (cur != NULL && !inserted)
        {
            if (cur->getData() == valueToInsertBefore)
            {
                valueAfter = cur->getPrevious()->getData();
                this->InsertAfter(valueAfter, valueToBeInserted);
                inserted = true;
            }
            cur = cur->getNext();
        }
    }

    if (!inserted)
    {
        Node *newNode = new Node(valueToBeInserted, this->first, NULL);
        this->first->setPrevious(newNode);
        this->first = newNode;
        this->size++;
    }

    if (valueToBeInserted > this->maxVal)
        this->maxVal = valueToBeInserted;
    if (valueToBeInserted < this->minVal)
        this->minVal = valueToBeInserted;
}

/**
 * Deletes the FIRST occurence of the value in the list.
 * 
 **/ 
void DLLStructure::Delete(int value)
{
    Node *cur = this->first;
    while (cur != NULL)
    {
        if (cur->getData() == value)
        {
            if (cur != this->last && cur != this->first)
            {
                // Most often case
                cur->getPrevious()->setNext(cur->getNext());
                cur->getNext()->setPrevious(cur->getPrevious());
            }
            else if (cur == this->last && cur != this->first)
            {
                this->last = this->last->getPrevious();
                this->last->setNext(NULL);
            } 
            else if (cur != this->last && cur == this->first)
            {
                this->first = this->first->getNext();
                this->first->setPrevious(NULL);
            }
            else 
            {
                this->first = NULL;
                this->last = NULL;
            }
            delete cur;
            this->size--;
            if (value == this->minVal)
            {
                this->minVal = INT32_MAX;
                this->setMin();
            }
            if (value == this->maxVal)
            {
                this->maxVal = INT32_MIN;
                this->setMax();
            }
            return;
        }
        cur = cur->getNext();
    }
    // value was not in the list
}

/**
 * Mergesort the list
 * 
 **/ 
void DLLStructure::Sort()
{

}

/**
 * Returns if the list is empty.
 * We implicity keep track of the emptiness of the list by the size of the list.
 * 
 **/ 
bool DLLStructure::IsEmpty()
{
    return this->size == 0;
}

int DLLStructure::getHead()
{
    // return garbage if the list is empty
    if (this->first == NULL)
    {
        return INT32_MIN;
    }
    return this->first->getData();
}

int DLLStructure::getTail()
{
    // return garbage if the list is empty
    if (this->last == NULL)
    {
        return INT32_MAX;
    }
    return this->last->getData();
}

/**
 * Returns the size of the list
 * 
 **/ 
int DLLStructure::getSize()
{
    return this->size;

}

/**
 * Finds the maximum value in the list
 * 
 **/ 
int DLLStructure::getMax()
{
    return maxVal;
}

/**
 * Finds the minimum value in the list
 * 
 **/ 
int DLLStructure::getMin()
{
    return minVal;
}

void testList()
{
    int array[] = {1,5,2,6,4};
    DLLStructure *list = new DLLStructure(array, 5);
    list->printDLL();
    cout << "Length: " <<list->getSize() << endl;
    list->InsertAfter(7,9);
    list->printDLL();
    cout << "Length: " <<list->getSize() << endl;
    list->Delete(9);
    list->printDLL();
    cout << "MAX: " << list->getMax() << endl;
    cout << "MIN: " << list->getMin() << endl;
    cout << "Length: " <<list->getSize() << endl;
    delete list;
}

int properTest() {
    // Q 1, 2, 3 should obviously be implemented successfully
    // in order to run the following code
    int array[5] = {11, 2, 7, 22, 4};
    DLLStructure dll(array, 5); // note that 5 is the size of the array
    dll.printDLL(); // the output should be: 11, 2, 7, 22, 4
    // Q 4
    dll.InsertAfter(7, 13); // To insert 13 after the first occurence of 7
    dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4
    dll.InsertAfter(25, 7); // To insert 7 after the first occurence of 25
    dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4, 7
    // Q 5
    dll.InsertBefore(7, 26); // To insert 26 before the first occurence of 7
    dll.printDLL(); // the output should be: 11, 2, 26, 7, 13, 22, 4, 7
    dll.InsertBefore(19, 12); // To insert 12 before the first occurence of 19
    dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 22, 4, 7
    // Q 6
    dll.Delete(22);
    dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 4, 7
    // Q 7
    dll.Sort();
    dll.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    // Q 8
    if (dll.IsEmpty())
        cout << "The list is empty" << endl;
    // Q 9
    cout << "Head element is: " << dll.getHead() << endl;
    cout << "Tail element is: " << dll.getTail() << endl;
    // Q 10
    cout << "Number of elements in the list is: " << dll.getSize() << endl;
    // Q 11
    cout << "Max element is: " << dll.getMax() << endl;
    cout << "Min element is: " << dll.getMin() << endl;

    // Q 11 theory question
    // print to the screen the written answer for the theory question
    // Q 12 theory question
    // print to the screen the written answer for the theory question
    // Q 12
    //DLLStructure dll2 (dll);
    //dll2.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    return 0;
}

int tester() {
    // Q 1, 2, 3 should obviously be implemented successfully
    // in order to run the following code
    int array[5] = {11, 2, 7, 22, 4};
    DLLStructure dll(array, 5); // note that 5 is the size of the array
    dll.printDLL(); // the output should be: 11, 2, 7, 22, 4
    // Q 4
    dll.InsertAfter(7, 13); // To insert 13 after the first occurence of 7
    dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4
    dll.InsertAfter(25, 7); // To insert 7 after the first occurence of 25
    dll.printDLL(); // the output should be: 11, 2, 7, 13, 22, 4, 7
    // Q 5
    dll.InsertBefore(7, 26); // To insert 26 before the first occurence of 7
    dll.printDLL(); // the output should be: 11, 2, 26, 7, 13, 22, 4, 7
    dll.InsertBefore(19, 12); // To insert 12 before the first occurence of 19
    dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 22, 4, 7
    // Q 6
    dll.Delete(22);
    dll.printDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 4, 7
    // Q 7
    dll.Sort();
    dll.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    // Q 8
    if (dll.IsEmpty())
        cout << "The list is empty" << endl;
    // Q 9
    cout << "Head element is: " << dll.getHead() << endl;
    cout << "Tail element is: " << dll.getTail() << endl;
    // Q 10
    cout << "Number of elements in the list is: " << dll.getSize() << endl;
    // Q 11
    cout << "Max element is: " << dll.getMax() << endl;
    cout << "Min element is: " << dll.getMin() << endl;

    // Q 11 theory question
    // print to the screen the written answer for the theory question
    // Q 12 theory question
    // print to the screen the written answer for the theory question
    // Q 12
    //DLLStructure dll2 (dll);
    //dll2.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    return 0;
}


int main()
{
    tester();
    cout << "DONE" << endl;
}