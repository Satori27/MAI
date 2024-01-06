#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = int64_t;

int main() {
  int n;
  cin >> n;
  vector<int> num(6);
  for(int i=0;i<n;++i){
    int a;
    cin>>a;
    ++num[a%5];
  }
  for(int i=0;i<6;++i){
    cout<< num[i]<<" ";
  }
}