#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <functional>
using namespace std;

bool cmp(int a, int b){
    return a>b;
}

int main(){
// std::set<std::vector<int>, std::greater<std::vector<int>>> ans;
//     int n,m;
//     cin>>n>>m;
//     for(int i=0;i<n;++i){
//         vector<int> a;
//         for(int j=0;j<m;++j){
//             int x; 
//             cin>>x;
//             a.push_back(x);
//         }
//         sort(a.begin(), a.end(), cmp);
//         ans.insert(a);
//     }
    
//     cout<<"\n";
//     for(auto a: ans){
//         for(int b: a){
//             cout<<b<<" ";
//         }
//         cout<<"\n";
//     }

    int n,m;
    cin>>n>>m;
    vector<int> a;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            int x; 
            cin>>x;
            a.push_back(x);
        }
        sort(a.begin(), a.end(), cmp);

    }

    for(int i=0;i<n*m;++i){
        cout<<a[i]<<" ";
        if(i%m-1==0 && i!=0){
            cout<<"\n";
        }
    }

}