#include <iostream>
#include <random>
using namespace std;
using ll = int64_t;

mt19937 rng(1);
struct node {
  node *left;
  node *right;
  int x;
  ll y;
  node(int _x, int _y) : x(_x), y(_y) {
	left = nullptr;
	right = nullptr;
	// y = rng();
  }
};

using treap = node *;

void split(treap t, int x0, treap &t1, treap &t2) {
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

void print_t(treap t, int h) {
  if (t == nullptr) {
	cout << "null" << '\n';
	return;
  }
  cout << t->x << ' ' << t->y << '\n';
  print_t(t->left, h + 1);

  print_t(t->right, h + 1);
}

void print(treap t) { print_t(t, 0); }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  treap t = nullptr;
  // for (int i = 1; i < 20; ++i)
  // {
  //     treap m = new node(i);
  //     t = merge(t, m);
  // }
  // print(t);

  int q;
  cin >> q;
  while (q--) {
	int x;
	int y;
	cin >> x >> y;
	treap l = nullptr, m = nullptr, r = nullptr;
	split(t, x, l, r);
	m = new node(x, y);
	t = merge(merge(l, m), r);
	// cout << "Querry\n";
	// cout << "\n";
  }
  print(t);
}