#include <iostream>
#include <string>
#include <vector>
using namespace std;
// using int = int64_t;

// int gcd(int a, int b) {
//   while (b != 0) {
// 	int t = b;
// 	b = a % b;
// 	a = t;
//   }
//   return a;
// }

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(0);
//   int n;
//   cin >> n;
//   for (int i = 0; i < n; ++i) {
// 	int Ax, Ay, Bx, By, dx, dy;
// 	cin >> Ax >> Ay >> Bx >> By;
// 	if (Ax == Bx && Ax== By &&Ax== Ay &&Ax== 0) {
// 	  cout << 1 << "\n";
// 	  continue;
// 	}
// 	dx = abs(Bx - Ax);
// 	dy = abs(By - Ay);
// 	int gc = gcd(dx, dy);
// 	cout << 1 + gc << "\n";
//   }
// }

// I
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;

  // vector<int> sv(4 * 1e7, 0);
  const int L = 4*1e7;
  auto sv = new int[L];
  for (int i = 0; i <= 4 * 1e7; ++i) {
	if (sv[i] > 0) {
	  continue;
	}
	for (int j = 2; j * i <= 4 * 1e7; ++j) {
	  sv[i * j]++;
	}
  }

  for (int i = 0; i < N; ++i) {
	int e;
	cin >> e;
	cout << sv[e] << "\n";
  }
  delete[] sv;
}
