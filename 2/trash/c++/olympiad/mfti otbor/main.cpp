#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

map<int, int> factorize(int x) {
    map<int, int> factors;

    for (int i = 2; i <= sqrt(x); i++) {
        while (x % i == 0) {
            factors[i]++;
            x /= i;
        }
    }

    if (x != 1) {
        factors[x]++;
    }

    return factors;
}

int main(){
    int n;
    cin>>n;
    map<int, int> vec = factorize(n);
    for(size_t i=0; i<vec.size();++i){
        cout<<i<<" "<<vec[i]<<"\n";
    }
}