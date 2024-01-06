#include <iostream>
#include <vector>
using namespace std;
using ll = int64_t;
ll INF = 1e9+1;

struct segtree
{
    struct node
    {
        node *left = nullptr;
        node *right = nullptr;
        ll data;

        node(ll v) : data(v) {}
    };
    using ptr = node *;
    ll n;
    ptr root = nullptr;
    segtree(ll _n) : n(_n) { root = new node(0); }
    ll get(ll l, ll r) { return get(root, 1, n, l, r); }

    ll get(ptr u, ll l, ll r, ll ql, ll qr)
    {
        if (u == nullptr)
        {
            return 0;
        }
        if (ql <= l and r <= qr)
        {
            return u->data;
        }
        ll m = (l + r) / 2;
        if (qr <= m)
        {
            return get(u->left, l, m, ql, qr);
        }
        if (ql > m)
        {
            return get(u->right, m + 1, r, ql, qr);
        }
        return get(u->left, l, m, ql, qr) + get(u->right, m + 1, r, ql, qr);
    }

    ll get_data(ptr u)
    {
        if (u == nullptr)
        {
            return 0;
        }
        else
        {
            return u->data;
        }
    }

    void set(ll p, ll x) { root = set(root, 1, n, p, x); }

    ptr set(ptr u, ll l, ll r, ll p, ll x)
    {
        if (u == nullptr)
        {
            u = new node(0);
        }
        if (l == r)
        {
            u->data += x;
            return u;
        }
        ll m = (l + r) / 2;
        if (p <= m)
        {
            u->left = set(u->left, l, m, p, x);
        }
        else
        {m
            u->right = set(u->right, m + 1, r, p, x);
        }
        u->data = get_data(u->left)+ get_data(u->right);
        return u;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll  q;
    cin >> q;
    segtree st(INF);
    while (q--)
    {
        ll t;
        cin >> t;
        if (t == 0)
        {
            ll l, r;
            cin >> l >> r;
            cout << st.get(l, r) << "\n";
        }
        else if (t == 1)
        {
            ll p, x;
            cin >> p >> x;
            st.set(p, x);
        }
    }
}