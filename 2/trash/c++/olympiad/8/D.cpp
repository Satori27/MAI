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
  vector<int> ans(n + 1);
  for (int i = 1; i < n + 1; ++i) {
	vector<int> prom;
	for (int j = 1; j < (i - 1) / 2+1; ++j) {
	  if (j == i - j)
		continue;
	  prom.push_back(ans[j] xor ans[i - j]);
	}
	ans[i] = mex(prom);
  }

  if (ans[n-1] == 0) {
	cout << "2\n";
  } else {
	cout << "1\n";
  }
}
