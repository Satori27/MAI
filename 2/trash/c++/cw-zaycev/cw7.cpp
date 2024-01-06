#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void cout_vec(vector<int> v) {
  for (int el : v) {
	cout << el << ' ';
  }
  cout << endl;
}

void cout_matr(vector<int> data, vector<int> ind, vector<int> indptr) {
  int ind_cout = 0;
  int ind_data = 0;
  for (size_t i = 1; i < indptr.size()+1; ++i) {
	int j = 0;
	int k = 0;
	while (j < indptr[i] - indptr[i - 1]) {
	  if (ind[ind_cout] != k) {
		cout << 0 << " ";
	  } else {
		cout << data[ind_data] << ' ';
		++ind_cout;
		++ind_data;
		++j;
	  }
	  ++k;
	}
	cout << endl;
  }
}

int main() {
  ifstream file;
  file.open("in7.txt", ios::in);
  ifstream input("in7.txt");
  string line;
  int a;
  vector<int> data;
  vector<int> ind;
  vector<int> indptr;
    	int sum = 1;
  indptr.push_back(sum);

  for (int i = 0; getline(input, line); ++i) {
	stringstream ss(line);

	for (int j = 0; ss >> a; ++j) {
	  if (a != 0) {
		++sum;
		data.push_back(a);
		ind.push_back(j);
	  }
	}
	indptr.push_back(sum);
  }
  cout_vec(data);
  cout_vec(ind);
  cout_vec(indptr);
  cout_matr(data, ind, indptr);
}