#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll = int64_t;
const ll max__ll = 1e18;

map<ll, ll> factor(ll num1, ll num2, ll both, ll resa, ll resb) {
  map<ll, ll> factors;
  ll smallerNum = min(num1, num2);
  ll res = 1;
  for (int i = 2; i <= sqrt(smallerNum); i++) {
	while (num1 % i == 0 && num2 % i == 0) {
	  res *= i;
	  ++factors[i];
	  num1 /= i;
	  num2 /= i;
	}
  }
  if (res == both)
	return factors;
  // if(both/num1==resa || both/num2==resb){
  //     ++factors[num1]
  // }
  if (num1 > 1)
	++factors[num1];
  if (num2 > 1)
	++factors[num2];

  return factors;
}

map<ll, ll> factorize(ll x) {
  map<ll, ll> factors;

  for (ll i = 2; i <= sqrt(x); i++) {
	while (x % i == 0) {
	  factors[i]++;
	  x /= i;
	}
  }

  if (x != 1) {
	factors[x]++;
  }
  return factors;
}

ll gcd(ll a, ll b) {
  while (b) {
	a %= b;
	swap(a, b);
  }
  return a;
}

ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

ll findGCD(vector<ll> arr, ll n) {
  ll result = arr[0];
  for (ll i = 1; i < n; i++) {
	result = gcd(arr[i], result);

	if (result == 1) {
	  return 1;
	}
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll t, n;
  cin >> t >> n;
  vector<ll> a(n);
  vector<ll> b(n);
  for (int i = 0; i < t; ++i) {
	for (int j = 0; j < n; ++j) {
	  cin >> a[j];
	}
	for (int j = 0; j < n; ++j) {
	  cin >> b[j];
	}
	ll gcd_a = findGCD(a, n);
	ll gcd_b = findGCD(b, n);
	ll lcm_vec = lcm(gcd_a, gcd_b);
	ll resa = lcm_vec / gcd_a;
	ll resb = lcm_vec / gcd_b;
	map<ll, ll> r = factor(resa, resb, lcm_vec, resa, resb);
	cout << r.size() << "\n";
	// map<ll, ll> m_a = factorize(resa);
	// map<ll, ll> m_b = factorize(resb);
	// map<ll, ll>::iterator it;

	// for (it = m_a.begin(); it != m_a.end(); it++) {
	//   cout << it->first		 // string (key)
	// 			<< ':' << it->second // string's value
	// 			<< endl;
	// }
	// for (it = m_b.begin(); it != m_b.end(); it++) {
	//   cout << it->first		 // string (key)
	// 			<< ':' << it->second // string's value
	// 			<< endl;
	// }
  }
}