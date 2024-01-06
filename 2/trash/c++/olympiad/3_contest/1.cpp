#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
using ll = double;

const ll INF = 1.7976931348623158e+308;

ll distance(ll x, ll y, ll x1, ll y1){
    ll dist = sqrt(pow(x1-x, 2) + pow(y1-y, 2));
    return dist;
}




struct coor{
    ll x,y;
};

struct jud_tar{
    int judge_ind=-1;
    ll value = INF;
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m,p;
    cin>>n>>m>>p;
    vector<coor> judge(n);
    vector<coor> tar(n);
    vector<coor> storehouse(n);

    vector<jud_tar> j_tar(m);
    vector<jud_tar> j_store(p);

    for(ll i=0;i<n;++i){
        ll x, y;
        cin>>x>>y;
        judge[i].x=x;
        judge[i].y=y;
    }
    for(ll i=0;i<m;++i){
        ll x, y;
        cin>>x>>y;
        tar[i].x=x;
        tar[i].y=y;
    }
    for(ll i=0;i<p;++i){
        ll x, y;
        cin>>x>>y;
        storehouse[i].x=x;
        storehouse[i].y=y;
    }

    for(int i=0;i<n;++i){
        for(int j=0; j<m;++j){
            ll dist = distance(judge[i].x, judge[i].y, tar[i].x, tar[i].y);
            if(j_tar[j].judge_ind>-1){
                if(dist<j_tar[j].value){
                    j_tar[j].value = dist;
                    ll min = INF;
                    int j1_ind;
                    for(int j1=0;j1<m;++j1){
                        if(j_tar[j1].judge_ind>-1)
                            continue; 
                        else{
                            ll dist1 = distance(judge[i].x, judge[i].y, tar[i].x, tar[i].y);
                            if (dist1<min){

                                min=dist1;
                                j1_ind = j1;

                            }
                        }
                    }
                    if (min!=INF && j_tar[j].judge_ind< j_tar[j1_ind].judge_ind){
                        cout<<"min "<<min<<endl;
                        j_tar[j1_ind].judge_ind = j_tar[j].judge_ind;
                        j_tar[j].judge_ind =i;
                        j_tar[j].value =min;
                    }

                }
            }else{
                j_tar[j].judge_ind = i;
                j_tar[j].value = dist;
            }
        }
    }


        for(int i=0;i<n;++i){
        for(int j=0; j<p;++j){
            ll dist = distance(judge[i].x, judge[i].y, storehouse[i].x, storehouse[i].y);
            if(j_store[j].judge_ind>-1){
                if(dist<j_store[j].value){
                    j_store[j].value = dist;
                    ll min = INF;
                    int j1_ind;
                    for(int j1=0;j1<p;++j1){
                        if(j_store[j1].judge_ind>-1)
                            continue; 
                        else{
                            ll dist1 = distance(judge[i].x, judge[i].y, storehouse[i].x, storehouse[i].y);
                            if (dist1<min){

                                min=dist1;
                                j1_ind = j1;

                            }
                        }
                    }
                    if (min!=INF && j_store[j].judge_ind< j_store[j1_ind].judge_ind){
                        cout<<"min "<<min<<endl;
                        j_store[j1_ind].judge_ind = j_store[j].judge_ind;
                        j_store[j].judge_ind =i;
                        j_store[j].value =min;
                    }

                }
            }else{
                j_store[j].judge_ind = i;
                j_store[j].value = dist;
            }
        }
    }

    ll sum=0;
    for(int i=0;i<m;++i){
        sum += j_tar[i].value;
        cout<<"i "<< j_tar[i].judge_ind<< " ";
            std::cout << std::fixed;
    cout.precision(6);
        cout<<j_tar[i].value<<" ";
    }
    cout<<endl;

    for(int i=0;i<p;++i){
        sum += j_store[i].value;
            std::cout << std::fixed;
    cout.precision(6);
        cout<<j_store[i].value<<" ";
    }
    cout<<endl;
    std::cout << std::fixed;
    cout.precision(6);
    cout<<sum<<endl;

}