#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = int64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  map<string, string> mp;
  string s;
  //   bool some = false;
  set<string> st;
  while (cin >> s) {
	if (s == "register") {
	  string k, e;
	  cin >> k >> e;
	  if (mp.find(k) != mp.end()) {
		cout << "login already in use"
			 << "\n";

	  } else {
		mp.insert({k, e});
		cout << "account created" << '\n';
	  }
	}

	if (s == "login") {
	  string k, e;
	  cin >> k >> e;
	  //   cout << e << " " << mp[k]<< " ";
	  if (mp.find(k) == mp.end()) {
		cout << "wrong account info"
			 << "\n";
	  } else if (mp.find(k) != mp.end() && st.find(k) == st.end()) {
		if (mp.find(k)->second == e) {
		  cout << "logged in"
			   << "\n";
		  st.insert(k);
		} else {
		  cout << "wrong account info"
			   << "\n";
		//   cout << "101" << mp.find(k)->first << mp[k] << " ";
		}
	  }

	  else if (st.find(k) != st.end()&& mp.find(k) != mp.end()) {
		if(mp.find(k)->second==e)
		cout << "already logged in»"
			 << "\n";
	  }

	  else if (mp.find(k) == mp.end()) {
		if (mp.find(k)->second != e) {
		  cout << "wrong account info"
			   << "\n";
		//   cout << "101" << mp.find(k)->first << mp[k] << " ";
		}
	  } else {
		cout << 1 << "\n";
	  }
	}

	if (s == "logout") {
	  string k;
	  cin >> k;
	  auto it = st.find(k);
	  if (it != st.end() && mp.find(k) != mp.end()) {
		cout << "logged out"
			 << "\n";
		st.erase(it);
	  } else {
		cout << "incorrect operation"
			 << "\n";
	  }
	  //   else {
	  // 	// some = false;
	  // 	cout << "logged out"
	  // 		 << "\n";
	  // 	st.erase(it);
	  //   }
	}
	string s;
  }
}