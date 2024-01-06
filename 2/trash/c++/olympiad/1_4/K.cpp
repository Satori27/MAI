#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
using ll = int64_t;
ll MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  multiset<ll> lms;
  multiset<ll> rms;
  ll n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
	ll ls = lms.size();
	ll rs = rms.size();
	ll med = floor((i) / 2);
	ll a;
	cin >> a;
	if (a >= med) {
	  rms.insert(a);

	} else {
	  lms.insert(a);
	}
	if (rms.size() <= lms.size()) {
	  ll e = *lms.rbegin();
	  auto maxel = lms.find(*lms.rbegin());
	  //   cout << *maxel << 1 << endl;
	  lms.erase(maxel);
	  rms.insert(e);
	}
	if (rms.size() > (lms.size() + 2)) {
	  ll e = *rms.begin();
	  rms.erase(rms.begin());
	  lms.insert(e);
	}
	if (lms.size() > 0) {
	  auto tl = *lms.rbegin();
	//   cout << *lms.begin();
	  ll tr = *(rms.begin());
	  if (tl > tr) {
		auto maxell = lms.find(*lms.rbegin());
		lms.erase(maxell);

		rms.erase(rms.begin());
		rms.insert(tl);
		lms.insert(tr);
	  }
	}
	cout << *rms.begin() << "\n";
  }
}