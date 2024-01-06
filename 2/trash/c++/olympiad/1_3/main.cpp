#include <iostream>
#include <algorithm>
#include <vector>
using ll = int64_t;

using namespace std;

// Driver code
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;

    bool res = 1;
    vector<ll> a(n, 0);
    vector<ll> X(n);
    for (ll i = 0; i < n; ++i)
    {
        ll e;
        cin >> e;
        X[i] = e;
    }
    for (ll i = 0; i < n; ++i)
    {
        if (X[i] > n)
        {
            res = 0;
            break;
        }
        if (X[i] > 0 && a[X[i] - 1] == 0)
        {
            a[X[i] - 1] = 1;
            continue;
        }
        else if (a[X[i] - 1] == 1)
        {
            res = 0;
            break;
        }
    }
    if (res)
    {
        vector<ll> b;
        for (ll i = 0; i < n; ++i)
        {
            if (a[i] == 0)
            {
                b.push_back(i + 1);
            }
        }
        reverse(b.begin(), b.end());
        for (ll i = 0; i < n; ++i)
        {
            if (X[i] == 0)
            {
                ll l = b.back();
                X[i] = l;
                b.pop_back();
            }
        }
        for (ll i = 0; i < n; ++i)
        {
            cout << X[i] << ' ';
        }
        cout << '\n';
    }
    else
    {
        cout << -1 << '\n';
    }
}