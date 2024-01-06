#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N;
    int A,B,C;
    cin>>N>>A>>B>>C;
    vector<int> stud(3);
    stud[0]=A;
    stud[1]=B;
    stud[2]=C;
    vector<int> X(N);
    for(int i=0;i<N;++i){
        cin>>X[i];
    }
    sort(stud.begin(), stud.end());
    sort(X.begin(), X.end());
    int ans=0;
    while(!X.empty()){
        vector<int> stud1 = stud;
        auto it=X.end()-1;
        while(!stud1.empty()){
            auto a = upper_bound(stud1.begin(), stud1.end()-1, *it);
            if(a==stud1.end() && a!=stud1.begin()){
                cout<<"WTF "<<"a "<<*a<<endl;
                --a;
            }
                            cout<<"WTF "<<"a "<<*a<<endl;

            // cout<<"IT "<<*it<<endl;
            *it -= *a;
            cout<<"it "<<*it<<endl;
            stud1.erase(a, stud1.end());
            if(*it<=0){
                cout<<"it1 "<<*it<<endl;
                X.erase(it);
                it = X.end()-1;
            }
        }
        ++ans;
    }
    cout<<ans-1<<endl;




    // while(!X.empty()){
    //     auto it = X.end()-1;
    //     vector<int> stud1 = stud;
    //     while(!stud1.empty()){
    //         auto a=upper_bound(stud1.begin(), stud1.end(), *it);
    //         if(a==stud1.end() && a!=stud1.begin()){
    //             --a;
    //             cout<<*a<<endl;
    //         }
    //         cout<<"X at the begin "<<*it<<endl;
    //         *it -= *a;
    //         cout<<"stud "<<*a<<endl;
    //         cout<<"X at the end "<<*it<<endl;
    //         stud1.erase(a);
    //         if(*it<=0){
    //             cout<<"X if <=0 "<<*it<<endl;
    //             X.erase(it);
    //             it = X.end()-1;
    //             cout<<"New X "<<*it<<endl;
    //         }
    //     }
    // }


}
