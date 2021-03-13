#include <iostream>
#include <map>
#include <cstdlib>
#include <time.h>
using namespace std;

class Node
{
    private:
        int data;
        Node *next = NULL;
        Node *previous = NULL;
    public:
        Node();
        Node(int data);
        Node(int data, Node *next, Node *previous);
        int getData();
        Node* getNext();
        void setNext(Node *next);
        void setPrevious(Node *previous);
        Node *getPrevious();
        void printNode();
};


Node::Node()
{
    // Do nothing
}

/**
 * Constructor 
 * 
 */ 
Node::Node(int data)
{
    this->data = data;
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
    if (this->previous == NULL)
        cout << "Data: " << this->data << " prev: NULL next: " << this->next->data  << endl;
    else if (this->next == NULL)
        cout << "Data: " << this->data << " prev: " << this->previous->data << " next: NULL" << endl;
    else
        cout << "Data: " << this->data << " prev: " << this->previous->data << " next:" << this->next->data << endl;
}

class DLLStructure
{
    private:
        Node *first = NULL, *last = NULL;
        int size, maxVal = INT32_MIN, minVal = INT32_MAX;
        void setMin();
        void setMax();
        void mergeSort(Node arr[], int l, int r);
        void merge(Node arr[], int l, int m, int r);
    public:
        DLLStructure();
        DLLStructure(int array[], int size);
        DLLStructure(DLLStructure &dll);
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


void DLLStructure::mergeSort(Node arr[], int l, int r)
{
    if (l >= r)
        return;
    int m = (l+r)/2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m , r);
}

void DLLStructure::merge(Node arr[], int l, int m, int r)
{
    int c1 = m - l + 1;
    int c2 = r - m;

    Node *leftArr = new Node[c1];
    Node *rightArr = new Node[c2];
    for (int i = 0; i < c1; i++)
        leftArr[i] = arr[l + i];
    for (int i = 0; i < c2; i++)
        rightArr[i] = arr[m+1+i];
    
    int i = 0, j = 0, k = l;

    while (i < c1 && j < c2)
    {
        if (leftArr[i].getData() < rightArr[j].getData())
        {
            arr[k] = leftArr[i];
            i++;
        } 
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }


    while (i < c1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < c2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete [] leftArr;
    delete [] rightArr;
}

/**
 * Public functions
 * 
 **/ 
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

/**
 * Deep copy constructor
 **/ 
DLLStructure::DLLStructure(DLLStructure &dll)
{
    this->size = dll.size;
    if (dll.first == NULL || dll.last == NULL)
    {
        // copying an empty list
        return;
    }
    Node *cur = dll.first->getNext();
    this->first = new Node(dll.first->getData());
    this->last = this->first;

    while (cur != NULL)
    {
        Node *newNode = new Node(cur->getData(), NULL, this->last);
        this->last->setNext(newNode);
        this->last = newNode;
        cur = cur->getNext();
    }
}

DLLStructure::~DLLStructure()
{
    if (this->first != NULL)
    {
        // Destruct the list
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
    if (!inserted && this->size >1)
    {
        Node *newNode = new Node(valueToBeInserted, NULL, this->last);
        this->last->setNext(newNode);
        this->last = this->last->getNext();
    } 
    else if (!inserted)
    {
        Node *aNode = new Node(valueToBeInserted);
        this->first = aNode;
        this->last = aNode;
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
    
    //empty list corner case
    if (this->size == 0)
    {
        Node *aNode = new Node(valueToBeInserted);
        this->first = aNode;
        this->last = aNode;
        this->size++;
        return;
    }
    
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
        if (valueToBeInserted > this->maxVal)
            this->maxVal = valueToBeInserted;
        if (valueToBeInserted < this->minVal)
            this->minVal = valueToBeInserted;
    }
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
    // Nothing to do in this case
    if (this->size <= 1)
    {
        return;
    }
    // create an array for easy manipulation.
    Node *aNode = new Node[this->size];
    Node *cur = this->first;
    int i = 0;
    while (cur != NULL)
    {
        aNode[i] = *cur;
        i++;
        cur = cur ->getNext();
    }
    
    // The actual sorting algorithm
    this->mergeSort(aNode, 0, this->size-1);
    
    for (int i = 0; i < this->size; i++)
    {
        
        // Should use switch statement but unable to get the following expression to be evaluated as a constant:
        // const int end = this->size-1; 
        if (i == 0)
        {
            aNode[i].setNext(&(aNode[i+1]));
            aNode[i].setPrevious(NULL);
            this->first = &(aNode[i]);
            continue;
        }
        
        if (i+1 == this->size)
        {
            aNode[i].setNext(NULL);
            aNode[i].setPrevious(&(aNode[i-1]));
            this->last = &(aNode[i]);
            continue;
        }

        aNode[i].setNext(&(aNode[i+1]));
        aNode[i].setPrevious(&(aNode[i-1]));
    }
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
        return INT32_MIN;
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


int main()
{
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
    // Q10 Theory!
    cout << "==========================================================================================================================================================================" <<endl;
    cout << "Q10: We must simply keep a counter of the size, which takes up more memory however is much more time efficient. The counter can be updated in O(1) time (increment or decrement) " << endl;
    cout << "while looping over the list would take O(n) time every time. Thus, during insertion and deletion of elements, we must be sure to increment or decrement accordingly " << endl;
    cout << "(being sure not to have a size which doesn't correspond to the actual size of the list.). " <<endl;
    cout << "==========================================================================================================================================================================" <<endl;
    cout << "Number of elements in the list is: " << dll.getSize() << endl;
    // Q 11
    cout << "Max element is: " << dll.getMax() << endl;
    cout << "Min element is: " << dll.getMin() << endl;

    // Q 11 theory question
    // print to the screen the written answer for the theory question
    cout << "==========================================================================================================================================================================" <<endl;
    cout << "Q11: In order to avoid repeatedly looping over the list, we can create integer variables which can be used to hold the largest and smallest values in our" << endl;
    cout << "list thereby when calling DLLStructure::GetMax() or DLLStructure::GetMin() we simply return those variables. This is the most speed efficient, however, during deletion" << endl;
    cout << "and insertion, we must make sure to update these if something changes. For insertion, you must only care about if the new element is actually the largest/smallest value. " << endl;
    cout << "and remedy this in O(1) time. However, during deletion, you may end up removing the largest/smallest variable and then you must loop through the list and find the new value O(n) time." << endl;
    cout << "==========================================================================================================================================================================" <<endl;
    // Q 12 theory question
    // print to the screen the written answer for the theory question
    cout << "==========================================================================================================================================================================" <<endl;
    cout << "Q12: The default constructor is not suitable for copying when we need a deep copy, which is the case here. When we delete a shallow copy" << endl;
    cout << "we are deleting the same object. There, when the program would end and it calls delete on dll and dll2, dll2 would seg fault as it is already" << endl;
    cout << "free. By this I mean the DLLStructure is a new object however, the internal nodes are shared between both lists. To remedy this, we create a" << endl;
    cout << "deep copy constructor which creates an entirely new object and entirely new nodes objects as well, therefore no long referencing any of the objects of dll. "<<endl;
    cout << "==========================================================================================================================================================================" <<endl;
    // Q 12
    DLLStructure dll2 (dll);
    dll2.printDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    DLLStructure dll3; // Creating the empty list for testing purposes
    dll3.printDLL();
    DLLStructure dll4 (dll3);
    dll4.InsertAfter(0, 1);
    dll4.InsertBefore(1, 2);
    dll4.printDLL();
    dll4.printReverse();
    dll4.Delete(3); // NOT IN THE LIST
    dll4.Delete(1);
    dll4.Delete(2);
    dll4.Delete(3); // NOT IN THE LIST
    dll4.printDLL();
    cout << "Number of elements in the list is: " << dll4.getSize() << endl;
    cout << "DONE" << endl;
    return 0;
}