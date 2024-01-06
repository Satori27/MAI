#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<ll>::iterator a_begin = a.begin();
    vector<ll>::iterator a_end = a.end();

    sort(a_begin, a_end);

    // for (k = 1; k <= n * (n - 1) / 2; ++k) {
        ll l = 1,
        r = 1e12 + 1,
        m;

        ll quantity1,
        quantity2;

        vector<ll>::iterator IT1;
        vector<ll>::iterator IT2;

        while (l != r) {
            m = (l + r) / 2;

            quantity1 = 0;
            quantity2 = 0;

            bool ok = false;

            IT1 = a_end;
            IT2 = a_end;

            for (int i = 0; a[i] <= m && i < n; ++i) {
                ll num1 = m / a[i];
                ll num2 = (m - 1) / a[i];
                
                auto it1 = upper_bound(a_begin, IT1, num1); // for <=
                auto it2 = upper_bound(a_begin, IT2, num2); // for <

                if (!ok && num1 * a[i] == m && it1 != a_begin && *(it1 - 1) == num1) {
                    ok = true;
                }

                IT1 = it1;
                IT2 = it2;

                quantity1 += it1 - a_begin;
                quantity2 += it2 - a_begin;

                if (it2 == a_end || *it2 > a[i]) {
                    --quantity1;
                    --quantity2;
                } else if (it1 == a_end || *it1 > a[i]) {
                    --quantity1;
                }
            }

            quantity1 /= 2;
            quantity2 /= 2;

            if (quantity1 >= k && k > quantity2 && ok)
                break;
            
            if (k > quantity1) {
                l = m + 1;
            } else {
                r = m;
            }
        }

        cout << m << endl;

    //     cout << m << " ";
    // }
    // cout << endl;

    return 0;
}