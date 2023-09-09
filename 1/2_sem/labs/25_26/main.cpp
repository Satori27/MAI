#include "func.h"


int main() {
  list *l = new list(1);
  add_el(l, 5);
  add_el(l, 8);
  add_el(l, 2);
  add_el(l, 0);
  add_el(l, 6);

  print_list(l);
  sort_n(l);
  print_list(l);
  print_list(l);
}
