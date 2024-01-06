#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mex(vector<int> a)
{
    int n = a.size();
    sort(a.begin(), a.end());
    if (a[0] > 0)
    {
        return 0;
    }
    for (int i = 0; i < n; ++i)
    {
        if (a[i] + 1 < a[i + 1])
        {
            return a[i] + 1;
        }
    }
    return a.back() + 1;
}

int main()
{
    int n;
    cin >> n;
    vector<int> sg(n + 1);
    sg[0] = 0;
    sg[1] = 1;
    sg[2] = 1;
    for (int i = 3; i <= n; ++i)
    {
        vector<int> tmp;
        int pos = (i + 1) / 2;
        for (int j = 1; j <= pos; ++j)
        {
            int left = max(0, j - 2);
            int right = i - j - 1;
            tmp.push_back(sg[left] ^ sg[right]);
        }
        sg[i] = mex(tmp);
    }
    for(int i=0;i<=n;++i){
        cout << sg[i] << ' ';
    }
    // vector<int> a(n);
    // for(int i=0;i<n;++i){
    //     cin >> a[i];
    // }
    // cout << mex(a) << endl;
}