#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = unsigned long long;
const ll mod = 1e9 + 7;

ll fact(ll n) {
  ll ans = 1;
  for (ll i = 1; i <= n; ++i)
	ans = (ans * i) % mod;
  if (ans == 0) {
	return 1;
  } else
	return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string a;
  cin >> a;
  ll n = a.size();
  vector<ll> word(27, 1);
  for (ll i = 0; i < n; ++i) {
	char e = a[i];
	int c = e - 97;
	// cout << c << " ";
	++word[c];
  }
  ll ans = fact(n);
  for (int i = 0; i < 26; ++i) {
	if (word[i] == 1) {
	  ans = (ans/ fact(word[i]))%mod;
	} else {
	  ans = (ans/ fact(word[i] - 1))%mod;
	}
    if(ans==0){
        ans = 1;
    }
  }
  cout << ans << "\n";
}
