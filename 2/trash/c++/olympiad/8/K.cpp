#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m;
  cin >> n >> m;
  ll res = 0;
  for (ll i = 0; i < n; ++i) {
	ll l, r;
	cin >> l >> r;
	ll a = r - l - 1;
	res = res ^ a;
  }
  if (res) {
	cout << "1 1"<< "\n";
  } else {
	cout << "2 2" << "\n";
  }
}