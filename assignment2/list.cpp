#include <iostream>
#include <string>
using namespace std;

/**
 * Basic Comparison types.
 */
template<typename T>
struct comparison
{
    using type = less<T>;
};

template <>
struct comparison<string>
{
    using type = struct string_comp
    {
        bool operator() (const string a, const string b) const 
        {
            return a.compare(b);
        }
    };
};

template<typename T>
using compare = typename comparison<T>::type;

/**
 * List class
 * 
 */ 
template<typename T>
class List
{
    private:
        class Node 
        {
            public:
                T data;
                Node *next;
                Node *previous;
                Node()
                {
                    this->next = NULL;
                    this->previous = NULL;
                }

                Node(int data)
                {
                    this->data = data;
                    this->next = NULL;
                    this->previous = NULL;
                }
                Node(T data, Node *next, Node *previous)
                {
                    this->data = data;
                    this->next = next;
                    this->previous = previous;
                }
        };
        Node *head = NULL;
        Node *tail = NULL;
        // NEED TO SET THESE!
        T minVal, maxVal;
        int size;
        compare<T> comparator;
        void setMin()
        {
            Node *cur = this->head;
            while (cur != NULL)
            {
                if (comparator(this->minVal, cur->data))
                    minVal = cur->data;
            }
        }
        void setMax()
        {
            Node *cur = this->head;
            while (cur != NULL)
            {
                if (comparator(cur->data, this->maxVal))
                    maxVal = cur->data;
            }
        }
    public:
        List();
        List(T array[], int size);
        List(List<T> &dll);
        ~List();
        void printDLL();
        void printReverse();
        void InsertAfter(T valueToInsertAfter, T valueToBeInserted);
        void InsertBefore(T valueToInsertBefore, T valueToBeInserted);
        void Delete(T value);
        void Sort();
        bool isEmpty()
        {
            return this->size == 0;
        }
        T getHead()
        {
            if (this->isEmpty())
            {
                return INTMAX_MIN;
            }
            return this->head->data;
        }
        T getTail()
        {
            if (this->isEmpty())
            {
                return INTMAX_MIN;
            }
            return this->head->data;
        }

        int getSize()
        {
            return this->size;
        } 

        T getMax()
        {
            return this->maxVal;
        }

        T getMin()
        {
            return this->minVal;
        }
};


template<typename T>
List<T>::List()
{
    this->size = 0;
}

template<typename T>
List<T>::List(T array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        Node *newNode = new Node(array[i], NULL, this->tail);
        // First element to be inserted
        if (this->head == NULL)
        {
            this->head = newNode;
        }
        // the list exists and we are adding a new node to the end.
        if (this->tail != NULL)
        {
            this->tail->next = newNode;
        }
        // set and get the min value
        if (comparator(this->minVal, array[i]))
            this->minVal = array[i];
        if (comparator(array[i], this->maxVal))
            this->maxVal = array[i];
        this->tail = newNode;
    }

    this->size = size;
}


template<typename T>
List<T>::List(List &dll)
{
    this->size = dll.size;
    if (dll.head == NULL || dll.tail == NULL)
    {
        // copying an empty list
        return;
    }
    Node *cur = dll.head->next;
    this->head = new Node(dll.head->data);
    this->tail = this->head;

    while (cur != NULL)
    {
        Node *newNode = new Node(cur->data, NULL, this->tail);
        this->tail->next = newNode;
        this->tail = newNode;
        cur = cur->next;
    }
}

template<typename T>
List<T>::~List()
{
    if (this->head != NULL)
    {
        // Destruct the list
        while (this->head->next != NULL)
        {
            Node *temp = this->head; 
            this->head = this->head->next;
            this->head->previous = NULL;
            delete temp;
        }
        // There is only one node left!
        Node *temp = this->head;
        this->head = NULL;
        this->tail = NULL;
        delete temp;   
    }
}

template<typename T>
void List<T>::printDLL()
{
    if (this->isEmpty())
    {
        cout << "Empty list!" << endl;
        return;
    }
    Node *temp = this->head;
    while (temp != NULL)
    {
        cout << temp->data;
        if (temp->next != NULL)
        {
            cout << ", ";
        }
        temp = temp->next;
    }
    cout << endl;
}

template<typename T>
void List<T>::printReverse()
{
    if (this->isEmpty())
    {
        cout << "Empty list!" << endl;
        return;
    }
    Node *temp = this->tail;
    while (temp != NULL)
    {
        cout << temp->data;
        if (temp->previous != NULL)
        {
            cout << ", ";
        }
        temp = temp->previous;
    }
    cout << endl;
}

template<typename T>
void List<T>::InsertAfter(T valueToInsertAfter, T valueToBeInserted)
{
    bool inserted = false;
    Node *cur = this->head;
    while (cur != NULL)
    {
        if (cur->data == valueToInsertAfter)
        {
            Node *newNode = new Node(valueToBeInserted, cur->next, cur);
            if (cur->next != NULL)
                cur->next->previous = newNode;
            cur->next = newNode;
            inserted = true;
            break;
        }
        cur = cur->next;
    }
    // If we got here then we clearly didn't find the element in the list. Add to the end.
    if (!inserted && this->size > 1)
    {
        Node *newNode = new Node(valueToBeInserted, NULL, this->tail);
        this->tail->next = newNode;
        this->tail = this->tail->next;
    } 
    else if (!inserted)
    {
        Node *aNode = new Node(valueToBeInserted);
        this->head = aNode;
        this->tail = aNode;
    }
    // increase the size
    this->size++;
    if (comparator(this->maxVal, valueToBeInserted))
        this->maxVal = valueToBeInserted;
    if (comparator(valueToBeInserted, this->minVal))
        this->minVal = valueToBeInserted;
}

template<typename T>
void List<T>::InsertBefore(T valueToInsertBefore, T valueToBeInserted)
{
    //empty list corner case
    if (this->size == 0)
    {
        Node *aNode = new Node(valueToBeInserted);
        this->head = aNode;
        this->tail = aNode;
        this->size++;
        // the extreme values
        this->minVal = valueToBeInserted;
        this->maxVal = valueToBeInserted;
        return;
    }
    
    // Non-empty list
    bool inserted = false;
    if (this->head->data == valueToInsertBefore)
    {
        // First node is the value to insert ahead.
        Node *newNode = new Node(valueToBeInserted, this->head, NULL);
        this->head->previous = newNode;
        this->head = newNode;
        this->size++;
        // Check if this is a new max or min
        if (comparator(this->maxVal, valueToBeInserted))
            this->maxVal = valueToBeInserted;
        if (comparator(valueToBeInserted, this->minVal))
            this->minVal = valueToBeInserted;
        return;
    }
    else if (this->size > 1)
    {
        // Completely useless way of inserting a node.
        Node *cur = this->head;
        int valueAfter = this->head->data;
        while (cur != NULL && !inserted)
        {
            if (cur->data == valueToInsertBefore)
            {
                valueAfter = cur->previous->data;
                this->InsertAfter(valueAfter, valueToBeInserted);
                inserted = true;
            }
            cur = cur->next;
        }
    }

    if (!inserted)
    {
        Node *newNode = new Node(valueToBeInserted, this->head, NULL);
        this->head->previous = newNode;
        this->head = newNode;
        this->size++;
        if (comparator(this->maxVal, valueToBeInserted))
            this->maxVal = valueToBeInserted;
        if (comparator(valueToBeInserted, this->minVal))
            this->minVal = valueToBeInserted;
    }
}

template<typename T>
void List<T>::Delete(T value)
{
    Node *cur = this->head;
    while (cur != NULL)
    {
        if (cur->data == value)
        {
            
            // 1st is the case which occurs most often. Otherwise, Checking corner cases.
            if (cur != this->tail && cur != this->head)
            {
                // Most often case
                cur->previous->next = cur->next;
                cur->next->previous = cur->previous;
            }
            else if (cur == this->tail && cur != this->head)
            {
                this->tail = this->tail->previous;
                this->tail->next = NULL;
            } 
            else if (cur != this->tail && cur == this->head)
            {
                this->head = this->head->next;
                this->head->previous = NULL;
            }
            else 
            {
                this->head = NULL;
                this->tail = NULL;
            }
            // delete the node, decrement size.
            delete cur;
            this->size--;
            // fix the max and/or min values
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
        cur = cur->next;
    }
    // value was not in the list
}

template<typename T>
void List<T>::Sort()
{

}

void intListTest()
{
    int array[5] = {1,2,3,4,5};
    List<int> dll(array,5);
    dll.printDLL();
    dll.InsertAfter(4, 6);
    dll.InsertAfter(1,9);
    dll.InsertBefore(5,10);
    dll.InsertAfter(0,12);
    dll.InsertBefore(7,22);
    dll.printDLL();
    cout << "length: " << dll.getSize() << endl;
    cout << "Max: " << dll.getMax() << endl;
    cout << "Min: " << dll.getMin() << endl;
}

void stringTest()
{
    string array[] = {"string1", "String2", "long String"};
    List<string> dll (array, 3);
    dll.printDLL();
}

int main()
{
    stringTest();
    return 0;
}