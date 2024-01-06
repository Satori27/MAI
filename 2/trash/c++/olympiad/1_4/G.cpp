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
  ll n, a0, anext, an, max1 = -1, max2 = -1;
  cin >> n >> a0;
  anext = (a0 * 5) % MOD;
  max1 = anext;
  for (int i = 0; i < n - 1; ++i) {
	// an = anext;
	anext = (anext * 5) % MOD;
	if (anext >= max1) {
	  max2 = max1;
	  max1 = anext;
	} else if (anext < max2) {
	  continue;
	} else if (anext < max1 && anext >= max2) {
	  max2 = anext;
	}
  }
  if (max1 < max2)
	cout << max1 << ' ' << max2 << "\n";
  else
	cout << max2 << ' ' << max1 << "\n";
}