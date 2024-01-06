#include <iostream>
#include <vector>
using namespace std;
using ll = int64_t;

struct segtree
{
    ll n;
    vector<ll> data, delay;
    segtree(const vector<ll> &v) : n(v.size()), data(4 * n), delay(4 * n)
    {
        build(1, 1, n, v);
    }
    segtree(ll _n) : n(_n), data(4 * n), delay(4 * n) {}

    void build(ll id, ll l, ll r, const vector<ll> &v)
    {
        if (l == r)
        {
            data[id] = v[l - 1];
            return;
        }
        ll m = (l + r) / 2;
        build(id * 2, l, m, v);
        build(id * 2 + 1, m + 1, r, v);
        data[id] = max(data[id * 2], data[id * 2 + 1]);
    }
    void push(ll id)
    {
        if (delay[id] == 0)
        {
            return;
        }
        if (id * 2 < 4 * n)
        {
            delay[id * 2] += delay[id];
        }
        if (id * 2 + 1 < 4 * n)
        {
            delay[id * 2 + 1] += delay[id];
        }
        data[id] += delay[id];
        delay[id] = 0;
    }

    void set(ll p, ll x) { set(1, 1, n, p, x); }

    void set(ll id, ll l, ll r, ll p, ll x)
    {
        if (l == r)
        {
            data[id] = x;
            return;
        }
        push(id);
        ll m = (l + r) / 2;
        if (p <= m)
        {
            set(id * 2, l, m, p, x);
        }
        else
        {
            set(id * 2 + 1, m + 1, r, p, x);
        }
        data[id] = max(data[id * 2], data[id * 2 + 1]);
    }

    ll get(ll l, ll r) { return get(1, 1, n, l, r); }

    ll get(ll id, ll l, ll r, ll ql, ll qr)
    {
        if (ql <= l and r <= qr)
        {
            return data[id];
        }
        push(id);
        ll m = (l + r) / 2;
        if (qr <= m)
        {
            return get(id * 2, l, m, ql, qr);
        }
        if (ql > m)
        {
            return get(id * 2 + 1, m + 1, r, ql, qr);
        }
        return max(get(id * 2, l, m, ql, qr), get(id * 2 + 1, m + 1, r, ql, qr));
    }

    void update(ll l, ll r, ll x) { update(1, 1, n, l, r, x); }

    void update(ll id, ll l, ll r, ll ql, ll qr, ll x)
    {
        if (ql > r or qr < l)
        {
            return;
        }
        if (ql <= l and r <= qr)
        {
            delay[id] += x;
            push(id);
            return;
        }
        ll m = (l + r) / 2;
        update(id * 2, l, m, ql, qr, x);
        update(id * 2 + 1, m + 1, r, ql, qr, x);
        data[id] = max(data[id * 2], data[id * 2 + 1]);
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
        ll l, r, x;
        cin >> l >> r >> x;
        st.update(l, r, x);
        cout << st.get(l, r) << "\n";
    }
}