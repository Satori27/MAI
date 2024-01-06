#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<ll> vec(n);
  for (int i = 0; i < n; ++i) {
	cin >> vec[i];
  }
  sort(vec.begin(), vec.end());
  ll m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
	ll s, f;
	cin >> s >> f;
	if (s > f) {
	  swap(s, f);
	}
	cout << lower_bound(vec.begin(), vec.end(), f) -
				lower_bound(vec.begin(), vec.end(), s)
		 << '\n';
  }
}