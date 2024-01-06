#include <iostream>
using namespace std;

class A
{
    int a;

public:
    void F()
    {
        a = 10;
        cout << (*this).a << endl;
    }
    
};

int main()
{
    A ObA;
    ObA.F();
}