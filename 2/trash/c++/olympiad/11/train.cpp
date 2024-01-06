// #include <iostream>
// #include <random>
// using namespace std;
// using ll = int64_t;

// mt19937 rng(1);
// struct node
// {
//     node *left;
//     node *right;
//     int x;
//     ll y;
//     node(int _x) : x(_x)
//     {
//         left = nullptr;
//         right = nullptr;
//         y = rng();
//     }
// };

// using treap = node *;

// void split(treap t, int x0, treap &t1, treap &t2)
// {
//     if (t == nullptr)
//     {
//         t1 = nullptr;
//         t2 = nullptr;
//         return;
//     }
//     if (x0 > t->x)
//     {
//         split(t->right, x0, t->right, t2);
//         t1 = t;
//     }
//     else
//     {
//         split(t->left, x0, t1, t->left);
//         t2 = t;
//     }
// }

// treap merge(treap t1, treap t2)
// {
//     if (t1 == nullptr)
//     {
//         return t2;
//     }
//     if (t2 == nullptr)
//     {
//         return t1;
//     }
//     if (t1->y > t2->y)
//     {
//         t1->right = merge(t1->right, t2);
//         return t1;
//     }
//     else
//     {
//         t2->left = merge(t1, t2->left);
//         return t2;
//     }
// }

// void print_t(treap t, int h)
// {
//     if (t == nullptr)
//     {
//         return;
//     }
//     print_t(t->left, h + 1);
//     cout << t->x << ' ';
//     print_t(t->right, h + 1);
// }

// void print(treap t) { print_t(t, 0); }

// int main()
// {
//     treap t = nullptr;
//     // for (int i = 1; i < 20; ++i)
//     // {
//     //     treap m = new node(i);
//     //     t = merge(t, m);
//     // }
//     // print(t);

//     int q;
//     cin >> q;
//     while (q--)
//     {
//         int x;
//         cin >> x;
//         treap l = nullptr, m = nullptr, r = nullptr;
//         split(t, x, l, r);
//         m = new node(x);
//         t = merge(merge(l, m), r);
//         cout << "Querry\n";
//         print(t);
//         cout << "\n";
//     }
// }
// -----------------------------------------------------------------------
// #include <chrono>
// #include <iostream>
// #include <random>
// using namespace std;
// using ll = int64_t;
// // ll INF = 1e18;

// mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// struct node {
//   node *left;
//   node *right;
//   ll x;
//   ll y;
//   ll val;
//   node(ll _val) : val(_val) {
// 	left = nullptr;
// 	right = nullptr;
// 	x = 1;
// 	y = rng();
//   }
// };

// using treap = node *;

// ll getx(treap t) { return (t == nullptr ? 0 : t->x); }

// void update(treap t) {
//   if (t == nullptr) {
// 	return;
//   }
//   t->x = 1 + getx(t->left) + getx(t->right);
// }

// void split(treap t, ll x0, treap &t1, treap &t2) {
//   if (t == nullptr) {
// 	t1 = nullptr;
// 	t2 = nullptr;
// 	return;
//   }
//   ll szleft = (1 + getx(t->left));
//   if (x0 >= szleft) {
// 	split(t->right, x0 - szleft, t->right, t2);
// 	t1 = t;
//   } else {
// 	split(t->left, x0, t1, t->left);
// 	t2 = t;
//   }
//   update(t);
// }

// treap merge(treap t1, treap t2) {
//   if (t1 == nullptr) {
// 	return t2;
//   }
//   if (t2 == nullptr) {
// 	return t1;
//   }
//   if (t1->y > t2->y) {
// 	t1->right = merge(t1->right, t2);
// 	update(t1);
// 	return t1;
//   } else {
// 	t2->left = merge(t1, t2->left);
// 	update(t1);
// 	return t2;
//   }
// }

// void print_t(treap t, ll h) {
//   if (t == nullptr) {
// 	return;
//   }
//   print_t(t->left, h + 1);
//   cout << t->val << ' ';
//   print_t(t->right, h + 1);
// }

// void print(treap t) { print_t(t, 0); }

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(0);
//   treap t = nullptr;
//   // for (ll i = 1; i < 20; ++i)
//   // {
//   //     treap m = new node(i);
//   //     t = merge(t, m);
//   // }
//   // print(t);

//   ll q;
//   cin >> q;
//   while (q--) {
// 	ll p, x;
// 	cin >> p >> x;
// 	treap l, r;
// 	split(t, p, l, r);
// 	treap m = new node(x);
// 	t = merge(merge(l, m), r);

//   }
//   	print(t);
// 	cout << '\n';
// }

// -------------------------------------------------------------






// MAX

#include <chrono>
#include <iostream>
#include <random>
using namespace std;
using ll = int64_t;
ll INF = 1e18;

mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
struct node {
  node *left;
  node *right;
  ll x;
  ll y;
  ll val;
  ll max_val;
  node(ll _val) : val(_val), max_val(_val) {
	left = nullptr;
	right = nullptr;
	x = 1;
	y = rng();
  }
};

using treap = node *;

ll getx(treap t) { return (t == nullptr ? 0 : t->x); }

ll get_max(treap t) { return (t == nullptr ? 0 : t->max_val); }

void update(treap t) {
  if (t == nullptr) {
	return;
  }
  t->x = 1 + getx(t->left) + getx(t->right);
  t->max_val = t->val;
  t->max_val = max(t->max_val, get_max(t->left));
  t->max_val = max(t->max_val, get_max(t->right));
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
	update(t2);
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
  // for (ll i = 1; i < 20; ++i)
  // {
  //     treap m = new node(i);
  //     t = merge(t, m);
  // }
  // print(t);

  ll q;
  cin >> q;
  while (q--) {
	ll p, x;
	cin >> x >> p;
	treap l, r;
	split(t, p, l, r);
	treap m = new node(x);
	t = merge(merge(l, m), r);
  }
  print(t);
  cout << '\n';
}

// --------------------------------------------------------

// Отложенный апдейт

// #include <chrono>
// #include <iostream>
// #include <random>
// using namespace std;
// using ll = int64_t;
// ll INF = 1e18;

// mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// struct node {
//   node *left;
//   node *right;
//   ll x;
//   ll y;
//   ll val;
//   ll max_val;
//   bool rev = false;
//   node(ll _val) : val(_val), max_val(_val) {
// 	left = nullptr;
// 	right = nullptr;
// 	x = 1;
// 	y = rng();
//   }
// };

// using treap = node *;

// ll getx(treap t) { return (t == nullptr ? 0 : t->x); }

// ll get_max(treap t) { return (t == nullptr ? -INF : t->max_val); }

// void update(treap t) {
//   if (t == nullptr) {
// 	return;
//   }
//   t->x = 1 + getx(t->left) + getx(t->right);
//   t->max_val = t->val;
//   t->max_val = max(t->max_val, get_max(t->left));
//   t->max_val = max(t->max_val, get_max(t->right));
// }

// void reverse(treap t) {
//   if (t == nullptr) {
// 	return;
//   }
//   t->rev = t->rev ^ 1;
// }

// void push(treap t) {
//   if (t == nullptr or t->rev == false) {
// 	return;
//   }
//   t->rev = false;
//   swap(t->left, t->right);
//   reverse(t->left);
//   reverse(t->right);
// }

// void split(treap t, ll x0, treap &t1, treap &t2) {
//   if (t == nullptr) {
// 	t1 = nullptr;
// 	t2 = nullptr;
// 	return;
//   }
//   push(t);
//   ll szleft = (1 + getx(t->left));
//   if (x0 >= szleft) {
// 	split(t->right, x0 - szleft, t->right, t2);
// 	t1 = t;
//   } else {
// 	split(t->left, x0, t1, t->left);
// 	t2 = t;
//   }
//   update(t);
// }

// treap merge(treap t1, treap t2) {
//   if (t1 == nullptr) {
// 	return t2;
//   }
//   if (t2 == nullptr) {
// 	return t1;
//   }
//   if (t1->y > t2->y) {
// 	push(t1);
// 	t1->right = merge(t1->right, t2);
// 	update(t1);
// 	return t1;
//   } else {
// 	push(t2);
// 	t2->left = merge(t1, t2->left);
// 	update(t2);
// 	return t2;
//   }
// }

// void print_t(treap t, ll h) {
//   if (t == nullptr) {
// 	return;
//   }
//   push(t);
//   print_t(t->left, h + 1);
//   cout << t->val << ' ';
//   print_t(t->right, h + 1);
// }

// void print(treap t) {
//   print_t(t, 0);
//   cout << "\n";
// }

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(0);
//   treap t = nullptr;
//   // for (ll i = 1; i < 20; ++i)
//   // {
//   //     treap m = new node(i);
//   //     t = merge(t, m);
//   // }
//   // print(t);

//   int n;
//   cin >> n;
//   for (int i = 0; i < n; ++i) {
// 	int a;
// 	cin >> a;
// 	treap m = new node(a);
// 	t = merge(t, m);
//   }
//   ll q;
//   cin >> q;
//   while (q--) {
// 	int type, l, r;
// 	cin >> type >> l >> r;
// 	treap tl, tm, tr;
// 	split(t, r, tm, tr);
// 	split(tm, l - 1, tl, tm);
// 	if (type == 1) {
// 	  reverse(tm);
// 	} else if (type == 2) {
// 	  cout << get_max(tm) << '\n';
// 	}
// 	t = merge(merge(tl, tm), tr);
// 	print(t);
//   }
// }

// -----------------------------------------------------------------

// Перемещение отрезков в начало
// Вставлять в начало

// #include <chrono>
// #include <iostream>
// #include <random>
// using namespace std;
// using ll = int64_t;
// ll INF = 1e18;

// mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// struct node {
//   node *left;
//   node *right;
//   ll x;
//   ll y;
//   ll val;
//   node(ll _val) : val(_val) {
// 	left = nullptr;
// 	right = nullptr;
// 	x = 1;
// 	y = rng();
//   }
// };

// using treap = node *;

// ll getx(treap t) { return (t == nullptr ? 0 : t->x); }

// void update(treap t) {
//   if (t == nullptr) {
// 	return;
//   }
//   t->x = 1 + getx(t->left) + getx(t->right);
// }

// void split(treap t, ll x0, treap &t1, treap &t2) {
//   if (t == nullptr) {
// 	t1 = nullptr;
// 	t2 = nullptr;
// 	return;
//   }
//   ll szleft = (1 + getx(t->left));
//   if (x0 >= szleft) {
// 	split(t->right, x0 - szleft, t->right, t2);
// 	t1 = t;
//   } else {
// 	split(t->left, x0, t1, t->left);
// 	t2 = t;
//   }
//   update(t);
// }

// treap merge(treap t1, treap t2) {
//   if (t1 == nullptr) {
// 	return t2;
//   }
//   if (t2 == nullptr) {
// 	return t1;
//   }
//   if (t1->y > t2->y) {
// 	t1->right = merge(t1->right, t2);
// 	update(t1);
// 	return t1;
//   } else {
// 	t2->left = merge(t1, t2->left);
// 	update(t2);
// 	return t2;
//   }
// }

// void print_t(treap t, ll h) {
//   if (t == nullptr) {
// 	return;
//   }
//   print_t(t->left, h + 1);
//   cout << t->val << ' ';
//   print_t(t->right, h + 1);
// }

// void print(treap t) {
//   print_t(t, 0);
//   cout << "\n";
// }

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(0);
//   treap t = nullptr;
//   //   for (ll i = 1; i < 20; ++i) {
//   // 	treap m = new node(i);
//   // 	t = merge(t, m);
//   //   }
//   // print(t);
//   int n;
//   cin >> n;
//   for (int i = 0; i < n; ++i) {
// 	int a;
// 	cin >> a;
// 	treap m = new node(a);
// 	t = merge(t, m);
//   }

//   ll q;
//   cin >> q;
//   while (q--) {
// 	int l, r;
// 	cin >> l >> r;
// 	treap tl, tm, tr;
// 	split(t, r, tm, tr);
// 	split(tm, l - 1, tl, tm);
// 	merge(merge(tm, tl), tr);

//   }
//   	print(t);
// }
