#include <iostream>
#include <string>
using namespace std;
using ll = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  string s;
  cin >> s;
  ll m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
	string s1;
	ll e;
	cin >> e;
	cin >> s1;
	ll j = 0, k = 0;
	while (j < n && k < e) {
	  if (s[j] == s1[k]) {
		++k;
		++j;
	  } else {
		++j;
	  }
	}
	if (k == e) {
	  cout << 0;
	}
	if (k != e) {
	  cout << 1;
	}
  }
  cout << "\n";
}