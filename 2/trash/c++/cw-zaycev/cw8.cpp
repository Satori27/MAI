#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct List {
  string a;
  List *next;
};

void add_elements(List *&head, string data) {
  List *new_head_one = new List;
  new_head_one->next = NULL;
  new_head_one->a = data;
  if (head == NULL) {
	head = new_head_one;
	return;
  }
  List *new_head = head;
  while (new_head->next != NULL) {
	new_head = new_head->next;
  }
  new_head->next = new_head_one;
}

void cout_el(List *head, int k) {
  if (!head) {
	cout << "List is empty" << endl;
	return;
  }
  bool print = false;
  int i = 0;
  while (head != NULL) {
	if ((++i) % k == 0) {
	  cout << head->a << endl;
	  print = true;
	}
	head = head->next;
  }
  if (!print) {
	cout << "List is not so big" << endl;
  }
}

int main() {
  int k;
  cin >> k;
  List *head = NULL;
  add_elements(head, "sdad");
  add_elements(head, "dsa");
  add_elements(head, "ssa");
  add_elements(head, "esa");
  add_elements(head, "osa");
  add_elements(head, "lsa");
  //   add_elements(head, "dsa");
  //   add_elements(head, "dsa");
  //   add_elements(head, "dsa");
  //   add_elements(head, "dsafdfsf");
  //   add_elements(head, "dsafsa");
  cout_el(head, k);
  //   cout << head->a;
  //   head = head->next;
  //   cout << head->a;
  //   head = head->next;
  //   cout << head->a;
}