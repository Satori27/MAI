#include <iostream>
#include <vector>
using namespace std;
struct segtree
{
    int n;
    vector<int> data, delay;
    segtree(const vector<int> &v) : n(v.size()), data(4 * n), delay(4 * n)
    {
        build(1, 1, n, v);
    }
    segtree(int _n) : n(_n), data(4 * n), delay(4 * n) {}

    void build(int id, int l, int r, const vector<int> &v)
    {
        if (l == r)
        {
            data[id] = v[l - 1];
            return;
        }
        int m = (l + r) / 2;
        build(id * 2, l, m, v);
        build(id * 2 + 1, m + 1, r, v);
        data[id] = data[id * 2]+ data[id * 2 + 1];
    }
    void push(int id)
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

    void set(int p, int x) { set(1, 1, n, p, x); }

    void set(int id, int l, int r, int p, int x)
    {
        if (l == r)
        {
            data[id] = x;
            return;
        }
        push(id);
        int m = (l + r) / 2;
        if (p <= m)
        {
            set(id * 2, l, m, p, x);
        }
        else
        {
            set(id * 2 + 1, m + 1, r, p, x);
        }
        data[id] = data[id * 2]+ data[id * 2 + 1];
    }

    int get(int l, int r) { return get(1, 1, n, l, r); }

    int get(int id, int l, int r, int ql, int qr)
    {
        if (ql <= l and r <= qr)
        {
            return data[id];
        }
        push(id);
        int m = (l + r) / 2;
        if (qr <= m)
        {
            return get(id * 2, l, m, ql, qr);
        }
        if (ql > m)
        {
            return get(id * 2 + 1, m + 1, r, ql, qr);
        }
        return get(id * 2, l, m, ql, qr)+ get(id * 2 + 1, m + 1, r, ql, qr);
    }

    void update(int l, int r, int x) { update(1, 1, n, l, r, x); }

    void update(int id, int l, int r, int ql, int qr, int x)
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
        int m = (l + r) / 2;
        update(id * 2, l, m, ql, qr, x);
        update(id * 2 + 1, m + 1, r, ql, qr, x);
        data[id] = data[id * 2]+ data[id * 2 + 1];
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    segtree st(a);
    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << st.get(l, r) << endl;
        }
        else if (t == 2)
        {
            int p, x;
            cin >> p >> x;
            st.set(p, x);
        }
        else if (t == 3)
        {
            int l, r, x;
            cin >> l >> r >> x;
            st.update(l, r, x);
        }
    }
}
