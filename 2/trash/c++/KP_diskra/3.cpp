#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int n;
  cin >> n;
  bool is_special_1 = true;
  bool is_special_2 = false;
  bool is_special_3 = true;
  bool is_special_4 = false;

  ofstream outfile("graph.dot");

  outfile << "graph MyGraph {" << endl;
  outfile << "node [shape=circle, style=filled]" << endl;

  // for (int i = 0; i < n; i++) {
  //   outfile << i << " ";
  // }
  // outfile << endl;

  for (int i = 0; i < n; i++) {
    int a;
    int b;
    cin >> a >> b;
    outfile << a << " -- " << b;
    outfile << " [color=black]";

    outfile << endl;
  }

  outfile << "}" << endl;

  outfile.close();

  system("dot -Tpng graph.dot -o graph.png");

  return 0;
}