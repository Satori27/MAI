#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = int64_t;

ll to_rim(string a) {
  a += "qq";
  ll num = 0;
  size_t i = 0;
  while (i < a.size()) {
	if (a[i] == 'M') {
	  num += 1000;
	  ++i;
	}
	if (a[i] == 'D') {
	  num += 500;
	  ++i;
	}
	if (a[i] == 'C') {
	  if (a[i + 1] == 'D') {
		num += 400;
		i += 2;
	  } else if (a[i + 1] == 'M') {
		num += 900;
		i += 2;
	  } else {
		num += 100;
        ++i;
	  }
	}
	if (a[i] == 'L') {
	  num += 50;
	  ++i;
	}
	if (a[i] == 'X') {

	  if (a[i + 1] == 'L') {
		num += 40;
		i += 2;
	  } else if (a[i + 1] == 'C') {
		num += 90;
		i += 2;
	  } else {
		num += 10;
        ++i;
	  }
	}
	if (a[i] == 'V') {
	  num += 5;
      ++i;
	}
	if (a[i] == 'I') {
	  if (a[i + 1] == 'X') {
		num += 9;
		i += 2;
	  } else if (a[i + 1] == 'V') {
		num += 4;
		i += 2;
	  } else {
		num += 1;
        ++i;
	  }
	}
    if(a[i]=='q'){
        return num;
    }
  }
  return num;
}

int main() {
  string a, b;
  cin >> a>>b;
  ll num1=to_rim(a);
  ll num2=to_rim(b);
//   cout<<num1<<" "<<num2<<endl;
    if(num1<num2){
        cout<<-1<<"\n";
    }
    if(num2==num1){
        cout<<0<<"\n";
    }
    if(num1>num2){
        cout<<1<<"\n";
    }
}