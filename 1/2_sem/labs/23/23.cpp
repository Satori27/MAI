#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct tree {
  tree *left;
  tree *right;
  int n;
  tree *create_tree(int n = 0) {
	tree *new_tr = new tree;
	new_tr->n = n;
	new_tr->left = nullptr;
	new_tr->right = nullptr;
	return new_tr;
  }

  tree *add_elements(tree *head, vector<int> a) {
	tree *new_head = head;
	for (int elem : a) {
	  head = add_branch(head, create_tree(elem));
	}
	return new_head;
  }

  tree *add_branch(tree *head, tree *new_br) {
	tree *new_head = head;
	int new_n = new_br->n;
	tree *some = go_to_br(head, new_n);
	if (some->n > new_n) {
	  some->left = new_br;
	} else {
	  some->right = new_br;
	}
	return new_head;
  }

  tree *go_to_br(tree *head, int n) {

	if (head->n > n && head->left != nullptr) {
	  return go_to_br(head->left, n);
	} else if (head->n < n && head->right != nullptr) {
	  return go_to_br(head->right, n);
	} else {
	  return head;
	}
  }

  void print_void(tree *head) {
	if (head != nullptr) {
	  print_void(head->left);
	  cout << head->n << ' ';
	  print_void(head->right);
	}
  }
  bool check(tree *head) {
	bool a = true;
	if (head != nullptr) {

	  if (head->left == nullptr && head->right != nullptr) {
		a = false;
		return a;
	  } else if (head->left != nullptr && head->right == nullptr) {
		a = false;
		return a;
	  } else {
		a = true;
	  }
	  a = check(head->left) & check(head->right);
	  return a;
	} else {
	  return a;
	}
  }
};

int main() {
  tree A;
  tree *head = A.create_tree();
  vector<int> a = {-2, 3, 2}; // +=2
  A.add_elements(head, a);
  // A.print_void(head);
  cout << A.check(head) << endl;
}