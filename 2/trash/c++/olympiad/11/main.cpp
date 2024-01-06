#include <iostream>
#include <random>
using namespace std;
using ll = int64_t;

mt19937 rng(1);
struct node {
  node *left;
  node *right;
  ll x;
  ll y;
  node(ll _x) : x(_x) {
	left = nullptr;
	right = nullptr;
	y = rng();
  }
};

using treap = node *;

void split(treap t, ll x0, treap &t1, treap &t2) {
  if (t == nullptr) {
	t1 = nullptr;
	t2 = nullptr;
	return;
  }
  if (x0 > t->x) {
	split(t->right, x0, t->right, t2);
	t1 = t;
  } else {
	split(t->left, x0, t1, t->left);
	t2 = t;
  }
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
	return t1;
  } else {
	t2->left = merge(t1, t2->left);
	return t2;
  }
}

void print_t(treap t, ll h) {
  if (t == nullptr) {
	return;
  }
  print_t(t->left, h + 1);
  cout << t->x << ' ';
  print_t(t->right, h + 1);
}

void print(treap t) {
  print_t(t, 0);
  cout << "\n";
}

int main() {
  treap t = nullptr;
  // for (ll i = 1; i < 20; ++i)
  // {
  //     treap m = new node(i);
  //     t = merge(t, m);
  // }
  // print(t);

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
	int a;
	cin >> a;
	treap m = new node(a);
	t = merge(t, m);
  }

  ll q;
  cin >> q;
  while (q--) {
	ll x;
	cin >> x;
	treap l = nullptr, m = nullptr, r = nullptr;
	split(t, x, l, r);
	m = new node(x);
	t = merge(merge(l, m), r);
	cout << "Querry\n";
	print(t);
	cout << "\n";
  }
}
