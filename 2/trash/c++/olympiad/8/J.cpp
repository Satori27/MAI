#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = int64_t;

int main() {
  ll n;
  cin >> n;
  ll res = 0;

  for (ll i = 2; i <= n/i; ++i) {
	if (n % i != 0) {
	  continue;
	}
	ll count = 0;
	while (n % i == 0) {
	  ++count;
	  n /= i;
	}
	res = res ^ count;
  }
  if (n != 1) {
	res = res^1;
  }
  if (res) {
	cout << 1 << "\n";
  } else {
	cout << 2 << "\n";
  }
}