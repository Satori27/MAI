#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = int64_t;

struct segtree
{
    ll gcd(ll x, ll y)
    {
        while (x != 0) {
            y %= x;
            swap(x, y);
        }
        return y;
    }
    ll n;
    vector<ll> data;

    segtree(ll _n) : n(_n), data(4 * n) {}
    segtree(const vector<ll> &a)
        : segtree(a.size())
    {
        build(1, 1, n, a);
    }
    void build(ll id, ll l, ll r, const vector<ll> &a)
    {
        if (l == r)
        {
            data[id] = a[l - 1];
            return;
        }
        ll m = (l + r) / 2;
        build(id * 2, l, m, a);
        build(id * 2 + 1, m + 1, r, a);
        data[id] = gcd(data[id * 2], data[id * 2 + 1]);
    }

    void set(ll p, ll x)
    {
        set(1, 1, n, p, x);
    }
    void set(ll id, ll l, ll r, ll p, ll x)
    {
        if (l == r)
        {
            data[id] += x;
            return;
        }
        ll m = (l + r) / 2;
        if (p <= m)
        {
            set(id * 2, l, m, p, x);
        }
        else
        {
            set(id * 2 + 1, m + 1, r, p, x);
        }
        data[id] = gcd(data[id * 2], data[id * 2 + 1]);
    }
    ll get(ll ql, ll qr)
    {
        return get(1, 1, n, ql, qr);
    }
    ll get(ll id, ll l, ll r, ll ql, ll qr)
    {
        if (ql <= l and r <= qr)
        {
            return data[id];
        }
        ll m = (l + r) / 2;
        if (qr <= m)
        {
            return get(id * 2, l, m, ql, qr);
        }
        if (ql >= m + 1)
        {
            return get(id * 2 + 1, m + 1, r, ql, qr);
        }
        return gcd(get(id * 2, l, m, ql, qr), get(id * 2 + 1, m + 1, r, ql, qr));
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    segtree st(a);
    ll q;
    cin >> q;
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        cout << st.get(l, r) << '\n';
    }
}