#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 7;
const long long LINF = 1e18 + 14;
#define ll long long

int mex(vector<int> &vec)
{
    sort(vec.begin(), vec.end());
    if (vec.empty() || vec[0] != 0) {
        return 0;
    }
    for (int i = 0; i < (int)vec.size() - 1; ++i) {
        if (vec[i] + 1 < vec[i + 1]) {
            return vec[i] + 1;
        }
    }
    return vec.back() + 1;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    ++n;
    vector<int> sg(2);
    sg[0] = 0; sg[1] = 1;
    for (int i = 2; i < n; ++i) {
        vector<int> next;
        for (int j = 1; (j*j) <= i; ++j) {
            next.push_back(sg[i - (j*j)]);
        }
        sg.push_back(mex(next));
    }
    if (sg[n - 1]) {
        cout << "1\n";
        return 0;
    }
    cout << "2\n";
    return 0;
}