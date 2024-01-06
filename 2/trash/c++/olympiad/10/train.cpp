// // Ленивое ДО
// #include <iostream>
// #include <vector>
// using namespace std;

// struct segtree
// {
//     int n;
//     vector<int> data, delay;
//     segtree(const vector<int> &v) : n(v.size()), data(4 * n), delay(4 * n)
//     {
//         build(1, 1, n, v);
//     }
//     segtree(int _n) : n(_n), data(4 * n), delay(4 * n) {}

//     void build(int id, int l, int r, const vector<int> &v)
//     {
//         if (l == r)
//         {
//             data[id] = v[l - 1];
//             return;
//         }
//         int m = (l + r) / 2;
//         build(id * 2, l, m, v);
//         build(id * 2 + 1, m + 1, r, v);
//         data[id] = max(data[id * 2], data[id * 2 + 1]);
//     }
//     void push(int id)
//     {
//         if (delay[id] == 0)
//         {
//             return;
//         }
//         if (id * 2 < 4 * n)
//         {
//             delay[id * 2] += delay[id];
//         }
//         if (id * 2 + 1 < 4 * n)
//         {
//             delay[id * 2 + 1] += delay[id];
//         }
//         data[id] += delay[id];
//         delay[id] = 0;
//     }

//     void set(int p, int x) { set(1, 1, n, p, x); }

//     void set(int id, int l, int r, int p, int x)
//     {
//         if (l == r)
//         {
//             data[id] = x;
//             return;
//         }
//         push(id);
//         int m = (l + r) / 2;
//         if (p <= m)
//         {
//             set(id * 2, l, m, p, x);
//         }
//         else
//         {
//             set(id * 2 + 1, m + 1, r, p, x);
//         }
//         data[id] = max(data[id * 2], data[id * 2 + 1]);
//     }

//     int get(int l, int r) { return get(1, 1, n, l, r); }

//     int get(int id, int l, int r, int ql, int qr)
//     {
//         if (ql <= l and r <= qr)
//         {
//             return data[id];
//         }
//         push(id);
//         int m = (l + r) / 2;
//         if (qr <= m)
//         {
//             return get(id * 2, l, m, ql, qr);
//         }
//         if (ql > m)
//         {
//             return get(id * 2 + 1, m + 1, r, ql, qr);
//         }
//         return max(get(id * 2, l, m, ql, qr), get(id * 2 + 1, m + 1, r, ql, qr));
//     }

//     void update(int l, int r, int x) { update(1, 1, n, l, r, x); }

//     void update(int id, int l, int r, int ql, int qr, int x)
//     {
//         if (ql > r or qr < l)
//         {
//             return;
//         }
//         if (ql <= l and r <= qr)
//         {
//             delay[id] += x;
//             push(id);
//             return;
//         }
//         int m = (l + r) / 2;
//         update(id * 2, l, m, ql, qr, x);
//         update(id * 2 + 1, m + 1, r, ql, qr, x);
//         data[id] = max(data[id * 2], data[id * 2 + 1]);
//     }
// };

// int main()
// {
//     int n;
//     cin >> n;
//     vector<int> a(n);
//     for (int i = 0; i < n; ++i)
//     {
//         cin >> a[i];
//     }
//     segtree st(a);
//     int q;
//     cin >> q;
//     while (q--)
//     {
//         int t;
//         cin >> t;
//         if (t == 1)
//         {
//             int l, r;
//             cin >> l >> r;
//             cout << st.get(l, r) << endl;
//         }
//         else if (t == 2)
//         {
//             int p, x;
//             cin >> p >> x;
//             st.set(p, x);
//         }
//         else if (t == 3)
//         {
//             int l, r, x;
//             cin >> l >> r >> x;
//             st.update(l, r, x);
//         }
//     }
// }

// --------------------------------------------------------------------------------------
// ДО на указателях

// #include <iostream>
// #include <vector>
// using namespace std;

// struct segtree
// {
//     struct node
//     {
//         node *left = nullptr;
//         node *right = nullptr;
//         int data;

//         node(int v) : data(v) {}
//     };
//     using ptr = node *;
//     int n;
//     ptr root = nullptr;
//     segtree(int _n) : n(_n) { root = new node(0); }
//     int get(int l, int r) { return get(root, 1, n, l, r); }

//     int get(ptr u, int l, int r, int ql, int qr)
//     {
//         if (u == nullptr)
//         {
//             return 0;
//         }
//         if (ql <= l and r <= qr)
//         {
//             return u->data;
//         }
//         int m = (l + r) / 2;
//         if (qr <= m)
//         {
//             return get(u->left, l, m, ql, qr);
//         }
//         if (ql > m)
//         {
//             return get(u->right, m + 1, r, ql, qr);
//         }
//         return max(get(u->left, l, m, ql, qr), get(u->right, m + 1, r, ql, qr));
//     }

//     int get_data(ptr u)
//     {
//         if (u == nullptr)
//         {
//             return 0;
//         }
//         else
//         {
//             return u->data;
//         }
//     }

//     void set(int p, int x) { root = set(root, 1, n, p, x); }

//     ptr set(ptr u, int l, int r, int p, int x)
//     {
//         if (u == nullptr)
//         {
//             u = new node(0);
//         }
//         if (l == r)
//         {
//             u->data = x;
//             return u;
//         }
//         int m = (l + r) / 2;
//         if (p <= m)
//         {
//             u->left = set(u->left, l, m, p, x);
//         }
//         else
//         {
//             u->right = set(u->right, m + 1, r, p, x);
//         }
//         u->data = max(get_data(u->left), get_data(u->right));
//         return u;
//     }
// };

// int main()
// {
//     int n, q;
//     cin >> n >> q;
//     segtree st(n);
//     while (q--)
//     {
//         int t;
//         cin >> t;
//         if (t == 1)
//         {
//             int l, r;
//             cin >> l >> r;
//             cout << st.get(l, r) << endl;
//         }
//         else if (t == 2)
//         {
//             int p, x;
//             cin >> p >> x;
//             st.set(p, x);
//         }
//     }
// }

// ---------------------------------------------------------------------

// #include <iostream>
// #include <vector>
// using namespace std;

// struct segtree
// {
//     struct node
//     {
//         node *left = nullptr;
//         node *right = nullptr;
//         int data;

//         node(int v) : data(v) {}
//     };
//     using ptr = node *;
//     int n;
//     vector<ptr> vers;
//     segtree(const vector<int> &v) : n(v.size())
//     {
//         ptr root = build(1, n, v);
//         vers.push_back(root);
//     }
//     ptr build(int l, int r, const vector<int> &v)
//     {
//         ptr u = new node(0);
//         if (l == r)
//         {
//             u->data = v[l - 1];
//             return u;
//         }
//         int m = (l + r) / 2;
//         u->left = build(l, m, v);
//         u->right = build(m + 1, r, v);
//         u->data = u->left->data ^ u->right->data;
//         return u;
//     }

//     ptr copy(ptr u)
//     {
//         ptr v = new node(u->data);
//         v->left = u->left;
//         v->right = u->right;
//         return v;
//     }

//     int get(int k, int l, int r) { return get(vers[k - 1], 1, n, l, r); }

//     int get(ptr u, int l, int r, int ql, int qr)
//     {
//         if (ql <= l and r <= qr)
//         {
//             return u->data;
//         }
//         int m = (l + r) / 2;
//         if (qr <= m)
//         {
//             return get(u->left, l, m, ql, qr);
//         }
//         if (ql > m)
//         {
//             return get(u->right, m + 1, r, ql, qr);
//         }
//         return get(u->left, l, m, ql, qr) ^ get(u->right, m + 1, r, ql, qr);
//     }

//     int get_data(ptr u)
//     {
//         if (u == nullptr)
//         {
//             return 0;
//         }
//         else
//         {
//             return u->data;
//         }
//     }

//     void set(int k, int p, int x)
//     {
//         ptr newroot = set(vers[k - 1], 1, n, p, x);
//         vers.push_back(newroot);
//     }

//     ptr set(ptr u, int l, int r, int p, int x)
//     {
//         u = copy(u);
//         if (l == r)
//         {
//             u->data = x;
//             return u;
//         }
//         int m = (l + r) / 2;
//         if (p <= m)
//         {
//             u->left = set(u->left, l, m, p, x);
//         }
//         else
//         {
//             u->right = set(u->right, m + 1, r, p, x);
//         }
//         u->data = u->left->data ^ u->right->data;
//         return u;
//     }
// };

// int main()
// {
//     int n;
//     cin >> n;
//     vector<int> a(n);
//     for (int i = 0; i < n; ++i)
//     {
//         cin >> a[i];
//     }
//     segtree st(a);
//     int q;
//     cin >> q;
//     while (q--)
//     {
//         int t;
//         cin >> t;
//         if (t == 1)
//         {
//             int k, p;
//             cin >> k >> p;
//             cout << st.get(k, p, p) << '\n';
//         }
//         else if (t == 2)
//         {
//             int k, p, x;
//             cin >> k >> p >> x;
//             st.set(k, p, x);
//         }
//     }
// }