#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int mex(vector<int> a) {
  int n = a.size();
  sort(a.begin(), a.end());
  if (a.empty() || a[0] > 0) {
	return 0;
  }
  for (int i = 0; i < n; ++i) {
	if (a[i] + 1 < a[i + 1]) {
	  return a[i] + 1;
	}
  }
  return a.back() + 1;
}

int main() {
  int n;
  cin >> n;
  ++n;
  vector<int> dp;
  vector<int> sq;
  for (int i = 0; i * i <= n; ++i) {
	sq.push_back((i * i));
  }

  dp.push_back(0);
  dp.push_back(1);
  for (int i = 2; i <= n; ++i) {
	vector<int> prom;
	for (int j = 1; j*j <= i; ++j) {
	  prom.push_back(dp[i - j*j]);
	}
	dp.push_back(mex(prom));
  }
  if (dp[n - 1]) {
	cout << 1 << "\n";
  } else {
	cout << 2 << "\n";
  }
}