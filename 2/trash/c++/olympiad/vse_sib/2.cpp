#include <iostream>
using namespace std;
using ll = int64_t;

ll bpow(ll x, ll y)
{
    ll z = 1;
    while (y)
    {
        if (y & 1)
        {
            z = (z * x);
        }
        x = (x * x);
        y = y >> 1;
    }
    return z;
}

int main(){
    
}