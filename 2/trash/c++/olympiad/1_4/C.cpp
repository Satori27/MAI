#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<ll> vec(n);
  for (int i = 0; i < n; ++i) {
	cin >> vec[i];
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
	for (int j = 0; j < i; ++j) {
	  for (int k = 0; k < j; ++k) {
		if (vec[i] < vec[j] + vec[k] && vec[j] < vec[i] + vec[k] && vec[k] < vec[j] + vec[i])
		  ++ans;
	  }
	}
  }
  cout << ans << '\n';
}