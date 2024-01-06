#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
using ll = int64_t;

bool cmp(long double a, long double b) { return a < b; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<long double> a(n);
  vector<long double> p(n);
  for (int i = 0; i < n; ++i) {
	cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
	cin >> p[i];
  }
  sort(a.begin(), a.end(), cmp);
  sort(p.begin(), p.end(), cmp);

  long double ans = 0;
  long double ans1 = 0;
  for (int i = 0; i < n; ++i) {
	ans = ans + a[i] * p[i];
	ans1 += p[i];
  }
  cout << fixed << setprecision(12) << ans / ans1 << "\n";
}