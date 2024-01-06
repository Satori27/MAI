#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = int64_t;
ll MOD = 1e9 + 7;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, a, m, k, mod;
  cin >> n >> a;
  cin >> m >> k;
  cin >> mod;
  //   vector<ll> vec(n);
  vector<ll> cnt(mod, 0);

  for (ll i = 0; i < n; ++i) {
	++cnt[a];
	a = (a * m + k) % mod;
  }
  // for (ll j = 0; j < mod; ++j) {
  // if (cnt[j] == 0)
  //   continue;
  // else {
  //   for (ll k = 0; k < cnt[j]; ++k) {
  // 	cout << j << " ";
  //   }
  // }

  //   for (ll i = 0; i < mod; ++i) {
  // 	++cnt[vec[i]];
  //   }

  // for (ll i = 0; i < mod; ++i) {
  // ll a = cnt[i];
  // for (ll j = 0; j < a; ++j) {

  //   ans += (a * (i+1));
  //   ++i;
  // }
  // }
  // cout << ans%MOD << "\n";
  ll ans = 0;
  ll i = 0;
  for (ll j = 0; j < mod; ++j) {
	if (cnt[j] == 0)
	  continue;
	else {
	  for (ll k = 0; k < cnt[j]; ++k) {
		ans += ((i + 1) * j) % MOD;
		++i;
	  }
	}
  }
  cout << ans % MOD << "\n";
}
