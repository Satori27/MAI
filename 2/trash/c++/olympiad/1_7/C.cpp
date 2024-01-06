#include <iostream>
using namespace std;
using ll = unsigned long long;
const ll mod = 1e9 + 7;



int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  ll ans = 1;
  if (n <= 20) {
	for (ll i = 3; i <= n - 1; i++) {
	  ans = (ans * i) % mod;
	}
	cout << ans << "\n";
  } else {
	for (ll i = 3; i <= n - 1; i++)
	  ans = (ans * i) % mod;
	cout << ans<< "\n";
  }
}