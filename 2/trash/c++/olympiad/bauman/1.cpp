#include <iostream>
#include <vector>
#include <string>

using namespace std;
using ll = int64_t;

bool is_palindrom(string a){
    int size=a.size();
    int end=size-1;
    int start=0;
    while(start<end){
        if(a[start]!=a[end]){
            return false;
        }
        ++start;
        --end;
    }
    return true;
    
}

int main() {
    ll n;
    cin>>n;
    ll palindrom = n;
    while(1){
        ++palindrom;
        string a=to_string(palindrom);
        if(is_palindrom(a)){
            break;
        }
        // cout<<a<<endl;
    }
    cout<<palindrom-n<<endl;
    // cout<<is_palindrom("10111111111111")<<endl;
}