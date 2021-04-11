#include <iostream>
using namespace std;


int funcAdd(int max){
    if (max == 0){
        return 0;
    }
    return max + funcAdd(max-1);
}

// q1
int funcAdd2(int max){
    static int sum = 0;
    if (max == 0){
        printf("Sum is : %d", sum);
        return sum;
    }
    sum += max;
    funcAdd2(max - 1);
}

//q2
int getLength(char * string){
    int l = 0;
    while (*(string+l) != '\0')
        l++;
    return l;
}

void printArr(int * arr, int length){
    cout << "[";
    for (int i = 0; i < length; i++){
        char* a;
        sscanf(a, " %d ", arr[i]); 
        cout << a;
    }
    cout << "]" << endl;
}

// q3
void createArray(void){
    int var;
    cout << "Please give me a number:";
	// Take in input
	cin >> var;
    int * arr = new int [var];
    int * arr2 = new int [var];
    for (int i = 0; i < var; i++){
        arr[i] = i+1;
        arr2[i] = var - i;
    }
    cout << "[";
    for (int i = 0; i < var; i++){
        cout << " " << arr[i] << " ";
    }
    cout << "]" << endl;

    cout << "[";
    for (int i = 0; i < var; i++){
        cout << " " << arr2[i] << " ";
    }
    cout << "]" << endl;

    delete [] arr;
    delete [] arr2;
}

template <typename T>
class SmartAllocator
{
    public:
        SmartAllocator()
        {
            cout << "ERROR: too few arguments" <<endl;
        }

        SmartAllocator(int inputSize)
        {
            this->allocated  = allocateMemory(inputSize);
        }

        ~SmartAllocator()
        {
            delete [] this->allocated;
            this->allocated = NULL;
        }

        T* getAddress()
        {
            return allocated;
        }
    private:
        T* allocated = NULL;
        T* allocateMemory(int inputSize)
        {  
            if (inputSize < 1)
            {
                cout << "ERROR: too few arguments" <<endl;
                return NULL;
            }
            return new T[inputSize]; 
        }
};

class MyUtility
{
    public:
        MyUtility(char* arr)
        {
            this->utility = arr;
            int i = 0;
            char *read = arr;
            while (*read != NULL)
            {
                read++;
                i++;
            }
            this->size = i;
        }

        void arrayCopy(char *toCopy)
        {
            int i = 0;
            char *read = toCopy;
            while (*read != NULL)
            {
                read++;
                i++;
            }
            char *temp = this->utility;
            int newSize = this->size + i;
            this->utility = new char[this->size + i];
            
            for (int j = 0;j < this->size; j++)
            {
                this->utility[j] = temp[j];
            }

            for (int j = 0; j < i; j++)
            {
                this->utility[j+this->size] = toCopy[j];
            }
            this->size = newSize;
            toCopy = this->utility;
        }

        int getLength()
        {
            return this->size;
        }

        char *concatenate(char *toCopy)
        {
            int i = 0;
            char *read = toCopy;
            while (*read != NULL)
            {
                read++;
                i++;
            }
            char *temp = this->utility;
            int newSize = this->size + i;
            this->utility = new char[this->size + i];
            
            for (int j = 0;j < this->size; j++)
            {
                this->utility[j] = temp[j];
            }

            for (int j = 0; j < i; j++)
            {
                this->utility[j+this->size] = toCopy[j];
            }
            this->size = newSize;
            return this->utility;
        }
    private:
        char *utility;
        int size = 0;
};

int main(){
    char a[] = "Hello World";
    MyUtility u2(a);
    MyUtility u(a);
    MyUtility u3(a);

    //cout << "Length: " << u.getLength() << endl;
    char a2[] = "Good bye";
    u.arrayCopy(a2);
    cout << a2 << endl;
    cout << u2.concatenate(a2) << endl;
    // cout << u.concatenate(a2) << endl;
    // cout << "Length: " << u.getLength();
    cout << "Everything good!" <<endl;
    return 0;
}