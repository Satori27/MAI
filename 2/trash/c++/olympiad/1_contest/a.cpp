#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
	int x, y;
	cin >> x >> y;
	int b = 0;
	if (y == 100) {
	  cout << -1 << "\n";
	} else {
	  cout << (x * y) / (100-y)+x << "\n";
	}
  }
}