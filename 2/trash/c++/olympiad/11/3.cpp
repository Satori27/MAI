#include <iostream>
#include <random>
using namespace std;
using ll = int64_t;
ll INF = 1e18;

mt19937 rng(1);
struct node {
  node *left;
  node *right;
  ll val;
  ll x;
  ll y;
  node(ll _val) : val(_val) {
    left = nullptr;
    right = nullptr;
    y = rng();
    x = 1;
  }
};

using treap = node *;

ll getx(treap t) { return (t == nullptr ? 0 : t->x); }

void update(treap t) {
  if (t == nullptr) {
    return;
  }
  t->x = 1 + getx(t->left) + getx(t->right);
}

void split(treap t, ll x0, treap &t1, treap &t2) {
  if (t == nullptr) {
    t1 = nullptr;
    t2 = nullptr;
    return;
  }
  ll szleft = (1 + getx(t->left));
  if (x0 >= szleft) {
    split(t->right, x0 - szleft, t->right, t2);
    t1 = t;
  } else {
    split(t->left, x0, t1, t->left);
    t2 = t;
  }
  update(t);
}

treap merge(treap t1, treap t2) {
  if (t1 == nullptr) {
    return t2;
  }
  if (t2 == nullptr) {
    return t1;
  }
  if (t1->y > t2->y) {
    t1->right = merge(t1->right, t2);
    update(t1);
    return t1;
  } else {
    t2->left = merge(t1, t2->left);
    update(t1);
    return t2;
  }
}

void print_t(treap t, ll h) {
  if (t == nullptr) {
    return;
  }
  print_t(t->left, h + 1);
  cout << t->val << ' ';
  print_t(t->right, h + 1);
}

void print(treap t) { print_t(t, 0); }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  treap t = nullptr;
  ll n;
  cin >> n;
  for (ll i = 0; i < n; ++i) {
    ll a;
    cin >> a;
    treap m = new node(a);
    t = merge(t, m);
  }
  // for (ll i = 1; i < 20; ++i)
  // {
  //     treap m = new node(i);
  //     t = merge(t, m);
  // }
  // print(t);

  ll q;
  cin >> q;
  while (q--) {
    ll l, r;
    cin >> l >> r;
    treap tl, tm, tr;
    split(t, r, tm, tr);
    split(tm, l - 1, tl, tm);
    merge(merge(tm, tl), tr);
    print(t);
    cout << '\n';
  }
}