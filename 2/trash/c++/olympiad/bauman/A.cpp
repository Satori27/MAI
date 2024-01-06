#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

using ll=int64_t;

int main(){
    ll D;
    cin>>D;
    ll D_pow = D*D*2;
    vector<pair<ll,ll>> vec;
    for(ll i=0;i<=D;++i){
        ll a = sqrt(D_pow-i*i);
        // ll b=(ll)a;
        if(a==sqrt(D_pow-i*i)){
            // cout<<i<<" "<< b<<endl;
            vec.push_back({i,a});
        }
    }
    cout<<vec.size()<<"\n";
    for(size_t i=0;i<vec.size();++i){
        cout<<vec[i].first<<" "<<vec[i].second<<"\n";
    }
}