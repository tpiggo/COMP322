#include <iostream>
#include <string>
using namespace std;

template <typename T>
class A
{
    public:
        T data;
        A(T data)
        {
            this->data = data;
        }
};

template <typename T, typename Comp = std::less<T>>
bool compare(const T &obj, const T &obj2, Comp c = Comp())
{
    return c(obj, obj2);
}


int main()
{
    string a = "tim";
    string b = "john";
    cout << "a is less than b (strings object):" << compare(a,b) << endl;
}