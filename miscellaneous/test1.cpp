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

int main(){
    //printf("Func returns: %d\n", funcAdd(5));
    printf("Func returns: %d\n", funcAdd2(5));
    printf("Length of string: %d\n", getLength("String"));
    createArray();
    return 0;
}