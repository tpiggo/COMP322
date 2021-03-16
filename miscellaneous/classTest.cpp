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
using comparator = typename comparison<T>::type;

template <typename T>
class A
{
    public:
        T data;
        comparator<T> comparator;
        A(T data)
        {
            this->data = data;
        }
        void tryComp(const T &compData) const
        {
            cout << "a is less than b (strings object):" << comparator(this->data, compData) << endl;
        }
};

template <typename T, typename Comp = std::less<T>>
bool compare(const T &obj, const T &obj2, Comp c = Comp())
{
    return c(obj, obj2);
}


int main()
{
    A<string> a("Tim");
    A<string> b("John");
    a.tryComp(b.data);
    
}