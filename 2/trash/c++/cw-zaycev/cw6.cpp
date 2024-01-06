#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Student {
  string name, s, o;
  string count, cp;
  string ssd;
  string type_video;
  string video;
  string type; // 0-sas, 1-sata
  string os;
};

int main() {
  ifstream file;
  file.open("in.txt", ios::in);
  ifstream input("in.txt");
  string line;
  vector<Student> a;
  while (getline(input, line)) {
	Student st;
	stringstream ss(line);
	ss >> st.name >> st.s >> st.o >> st.count >> st.cp >> st.ssd >>
		st.type_video >> st.video >> st.type >> st.os;
	a.push_back(st);
  }
  string el[3] = {"Samsung", "Apple", "Huawei"};
  for (Student elem : a) {
	for (int i = 0; i < 3; ++i) {
	  if (elem.ssd == el[i]) {
		cout << elem.name << ' ' << elem.s << elem.o << endl;
	  }
	}
  }
  file.close();
}