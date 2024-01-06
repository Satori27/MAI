#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

using ll=int64_t;

struct Point{
    ll x;
    ll y;
    bool operator==(Point b){
        return this->x==b.x && this->y==b.y;
    }

    bool operator<(Point b) const{
        return this->x<b.x && this->y<b.y;
    }
    bool operator>(Point b)const {
        return this->x>b.x && this->y>b.y;
    }

};

bool distance(Point a, Point b){
    return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y,2))<=1;
}


bool cmpX(Point a, Point b){
    return a.x<b.x;
}

bool cmpY(Point a, Point b){
    return a.y<b.y;
}


int main(){
    ll n;
    cin>>n;
    // Вектор точек
    vector<Point> points(n);
    for(int i=0;i<n;++i){
        Point a;
        cin>>a.x>>a.y;
        points[i] = a;
    }

    // Вычисляю сами стороны
    vector<Point> side(n);
    for(int i=0;i<n;++i){

        if(i==n-1){
            ll x = points[0].x-points[i].x;
            ll y = points[0].y-points[i].y;
            side[i].x=x;
            side[i].y=y;
                    cout<<"\n"<<side[i].x<<" "<<side[i].y<<"\n\n";

            continue;
        }
        ll x = side[i+1].x-points[i].x;
        ll y = points[i+1].y-points[i].y;
        side[i].x=x;
        side[i].y=y;
        cout<<"\n"<<side[i].x<<" "<<side[i].y<<"\n\n";

    }

    // получаю координаты деревьев
    ll m;
    cin>>m;
    vector<Point > trees(m);
    for(int i=0;i<m;++i){
        ll x;
        ll y;
        cin>>x>>y;
        trees[i].x = x;
        trees[i].y = y;
    }
    vector<Point> treesX(trees);
    vector<Point> treesY(trees);

    sort(treesX.begin(), treesX.end(), cmpX);
    sort(treesY.begin(), treesY.end(), cmpY);
    vector<vector<Point>> ans(n);

cout<<"\n\n";
    for(int i=0; i<n; ++i){
        auto it = upper_bound(treesX.begin(), treesX.end(), side[i]);
        auto it1=it;
        cout<<it->x<<" "<<it->y<<"\n";
        while(it1!=treesX.begin()){
            if(abs(it1->x-side[i].x)>1 && abs(it1->y-side[i].y)>1){
                break;
            }
            if(distance(side[i], *it1)){
                ans[i].push_back(*it1);
            }
            --it1;
        }
        --it1;
        if(distance(side[i], *it1)){
            ans[i].push_back(*it1);
        }

        auto it2=it;

        while(it2!=treesX.end()){
            if(abs(it2->x-side[i].x)>1 && abs(it2->y-side[i].y)>1){
                continue;
            }
            if(distance(side[i], *it2)){
                ans[i].push_back(*it2);
            }
            ++it2;
        }


        auto itY = upper_bound(treesY.begin(), treesY.end(), side[i]);
        auto it1Y=itY;
        while(it1Y!=treesY.begin()){
            if(abs(it1Y->x-side[i].x)>1 && abs(it1Y->y-side[i].y)>1){
                continue;
            }
            if(distance(side[i], *it1Y)){
                ans[i].push_back(*it1Y);
            }
            --it1Y;
        }
        --it1Y;
        if(distance(side[i], *it1Y)){
            ans[i].push_back(*it1Y);
        }

        auto it2Y=itY;

        while(it2Y!=treesY.end()){
            if(abs(it2Y->x-side[i].x)>1 && abs(it2Y->y-side[i].y)>1){
                break;
            }
            if(distance(side[i], *it2Y)){
                ans[i].push_back(*it2Y);
            }
            ++it2Y;
        }
    }

    
    cout<<"\n\n";
    for(int i=0;i<n;++i){
        size_t sz = ans[i].size();
            cout<<i+1<<" "<<sz<<" ";
        for(size_t j=0;j<sz;++j){
            cout<<ans[i][j].x<<" "<<ans[i][j].y<<" ";
        }
        cout<<"\n";
    }
}