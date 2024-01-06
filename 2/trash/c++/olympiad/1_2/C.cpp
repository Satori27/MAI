#include <iostream>
#include <string>
using namespace std;
using ll = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  ll m;
  cin >> n >> m;
  string t, p;
  cin >> t >> p;
  ll ans = 0;
  for (int i = 0; i < n - m + 1; ++i) {
	string e = t.substr(i, m);
	if (e == p) {
	  ++ans;
	}
  }
  cout << ans << "\n";
}