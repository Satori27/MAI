#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  ll e;

  for (int i = 0; i < n; ++i) {
	cin >> e;
	vector<ll> a = {100, 200, 500, 1000, 5000};
	vector<ll> ans(5, 0);
	while (e / a[4] >= 1) {
	  ++ans[4];
	  e -= a[4];
	}
	while (e / a[3] >= 1) {
	  ++ans[3];
	  e -= a[3];
	}
	while (e / a[2] >= 1) {
	  ++ans[2];
	  e -= a[2];
	}
	while (e / a[1] >= 1) {
	  ++ans[1];
	  e -= a[1];
	}
	while (e / a[0] >= 1) {
	  ++ans[0];
	  e -= a[0];
	}
	for (int i = 0; i < 5; ++i) {
	  cout << ans[i] << " ";
	}
	cout << "\n";
  }
}