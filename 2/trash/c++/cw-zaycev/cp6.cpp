#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = int64_t;

mt19937 rng(1);
struct comp {
  ll RAM;
  string CP;
  ll memory;
};

bool cmp(pair<ll, string> a, pair<ll, string> b) { return a.second < b.second; }
bool cmp1(pair<ll, ll> a, pair<ll, ll> b) { return a.first < b.first; }
bool cmp2(pair<ll, comp> a, pair<ll, comp> b) { return a.first < b.first; }
bool operator<(pair<ll, string> a, pair<ll, string> b) {
  return a.second < b.second;
}
bool operator>(pair<ll, string> a, pair<ll, string> b) {
  return a.second > b.second;
}
bool operator==(pair<ll, string> a, pair<ll, string> b) {
  return a.second == b.second;
}
ll bin_ser_user(string s, vector<pair<ll, string>> user) {
  // vector<pair<ll, string>>* p;
  for (pair<ll, string> a : user) {
	if (a.second == s) {

	  return a.first;
	}
  }
  return 0;
}

void bin_ser_comp(ll a, vector<pair<ll, comp>> num) {
  if (a == 0) {
	cout << "Error\n";
  }
  ll l = 0;
  ll r = num.size() - 1;
  while (l <= r - 1) {
	ll m = (l + r) / 2;
	if (a == num[m].first) {
	  cout << num[m].second.RAM << " " << num[m].second.CP
		   << " "<< num[m].second.memory << endl;
	  return;
	} else if (a > num[m].first) {
	  l = m;
	} else if (a < num[m].first) {
	  r = m;
	}
  }
  cout << "Error\n";
}

ll bin_ser_num(ll a, vector<pair<ll, ll>> num) {
  if (a == 0) {
	return 0;
  }
  ll l = 0;
  ll r = num.size() - 1;
  while (l <= r - 1) {
	ll m = (l + r) / 2;
	if (a == num[m].first) {
	  return num[m].second;
	} else if (a > num[m].first) {
	  l = m;
	} else if (a < num[m].first) {
	  r = m;
	}
  }
  return 0;
}

void ans(string s, vector<pair<ll, ll>> num, vector<pair<ll, string>> user,
		 vector<pair<ll, comp>> comp_db) {
  bin_ser_comp(bin_ser_num(bin_ser_user(s, user), num), comp_db);
}

int main() {
  ifstream file;
  file.open("in.txt", ios::in);
  ifstream input("in.txt");
  string line;
  vector<pair<ll, string>> user;
  vector<pair<ll, comp>> comp_db;
  vector<pair<ll, ll>> num;
  while (getline(input, line)) {
	comp cp;
	string name;
	stringstream ss(line);
	ss >> name >> cp.RAM >> cp.CP >> cp.memory;
	ll i = rng();
	user.push_back({i, name});
	ll j = rng();
	comp_db.push_back({j, cp});
	num.push_back({i, j});
  }
  sort(user.begin(), user.end(), cmp);
  sort(num.begin(), num.end(), cmp1);
  sort(comp_db.begin(), comp_db.end(), cmp2);
  string s;
  cin >> s;
  if (s == "SELECT") {
	string e;
	cin >> e;
	ans(e, num, user, comp_db);
  } else {
	cout << "Error\n";
  }
}