#include <iostream>
#include <string>
using namespace std;

struct tree {
  char a;
  tree *left;
  tree *right;
  tree(char _a) : a(_a) {
	left = nullptr;
	right = nullptr;
  }
};

void print(tree *&dstr) {
  if (dstr->a == '*') {
	cout << dstr->left->a << dstr->a << '(' << dstr->right->left->a
		 << dstr->right->a << dstr->right->right->a << ')' << '\n';
  } else {
	cout << dstr->left->left->a << dstr->left->a << dstr->left->right->a
		 << dstr->a << dstr->right->left->a << dstr->right->a
		 << dstr->right->right->a << '\n';
  }
}

void perestroyka(tree *&dstr) {
  char a = dstr->left->a;
  swap(dstr->a, dstr->right->a);
  swap(dstr->right->left->a, dstr->left->a);
  char b = dstr->left->a;
  dstr->left->a = dstr->right->a;
  dstr->left->left = new tree(a);
  dstr->left->right = new tree(b);
}

void add(tree *&dstr, string &s) {

  if (s[0] != '(') {
	dstr->left = new tree(s[0]);
	if (s[2] == '(') {
	  dstr->right = new tree(s[4]);
	  dstr->right->left = new tree(s[3]);
	  dstr->right->right = new tree(s[5]);
	} else
	  cout << "Wrong!";
  }
}

int main() {
  string s;
  cin >> s;
  tree *dstr = new tree('*');
  add(dstr, s);
  // print(dstr);
  perestroyka(dstr);
  print(dstr);
}