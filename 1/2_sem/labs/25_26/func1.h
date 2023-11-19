#include "func.h"


void swap_list(list *&one, list *&two) { swap(one->n, two->n); }

void sort_p(list *&head) {
  if (head->prev) {
	if (head->prev->n > head->n) {
	  swap(head->prev->n, head->n);
	}
	sort_p(head->prev);
  } else
	return;
}

void sort_n(list *&head) {
  //   if (head->prev == NULL) {
  // 	return;
  //   }
  if (head->next) {
	if (head->next->n < head->n) {
	  swap(head->next->n, head->n);
	}
	list *h = head;
	if (head->prev) {
	  sort_p(head->prev);
	}
	sort_n(h->next);
  } else {
	return;
  }
}

void add_el(list *&head, int n) {
  list *new_head = head;
  while (head->next) {
	head = head->next;
  }
  list *new_list = new list(n);
  head->next = new_list;
  new_list->prev = head;
  head = new_head;
}

void print_list(list *head) {
  while (head->next) {
	cout << head->n << " ";
	head = head->next;
  }
  cout << head->n << " ";
  cout << "\n";
}

void print_rev(list *head) {
  while (head->next) {
	head = head->next;
  }
  while (head->prev) {
	cout << head->n << " ";
	head = head->prev;
  }
  cout << head->n << ' ';
  cout << "\n";
}