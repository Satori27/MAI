#ifndef zaycev
#define zaycev

#include <iostream>
using namespace std;

struct list {
  int n;
  list *prev;
  list *next;
  list(int _n) : n(_n) {
	next = NULL;
	prev = NULL;
  }
};
void add_el(list *&head, int n);
void print_list(list *head);
void print_rev(list *head);
void sort_n(list *&head);

#endif

