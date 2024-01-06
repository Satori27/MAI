// неориентированный неразрывный
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = int64_t;
const ll MAXN = 1e4;

vector<vector<int>> g(MAXN);
int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
bool used[MAXN], blossom[MAXN];

void mark_path(int v, int b, int children) {
  while (base[v] != b) {
	blossom[base[v]] = blossom[base[match[v]]] = true;
	p[v] = children;
	children = match[v];
	v = p[match[v]];
  }
}

int lca(int a, int b) {
  bool used[MAXN] = {0};
  // поднимаемся от вершины a до корня, помечая все чётные вершины
  for (;;) {
	a = base[a];
	used[a] = true;
	if (match[a] == -1)
	  break; // дошли до корня
	a = p[match[a]];
  }
  // поднимаемся от вершины b, пока не найдём помеченную вершину
  for (;;) {
	b = base[b];
	if (used[b])
	  return b;
	b = p[match[b]];
  }
}

int find_path(int root, int k) {
  memset(used, 0, sizeof used);
  memset(p, -1, sizeof p);
  for (int i = 0; i < k; ++i)
	base[i] = i;

  used[root] = true;
  int qh = 0, qt = 0;
  q[qt++] = root;
  while (qh < qt) {
	int v = q[qh++];
	for (size_t i = 0; i < g[v].size(); ++i) {
	  int to = g[v][i];
	  if (base[v] == base[to] || match[v] == to)
		continue;
	  if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
		int curbase = lca(v, to);
		memset(blossom, 0, sizeof blossom);
		mark_path(v, curbase, to);
		mark_path(to, curbase, v);
		for (int i = 0; i < k; ++i)
		  if (blossom[base[i]]) {
			base[i] = curbase;
			if (!used[i]) {
			  used[i] = true;
			  q[qt++] = i;
			}
		  }
	  } else if (p[to] == -1) {
		p[to] = v;
		if (match[to] == -1)
		  return to;
		to = match[to];
		used[to] = true;
		q[qt++] = to;
	  }
	}
  }
  return -1;
}

int main() {
  int k;
  cout << "Введите количество ребер, а потом ребра графа" << endl;
  cin >> k;
  for (int i = 0; i < k; ++i) {
	int a, b;
	cin >> a >> b;
	g[a].push_back(b);
	g[b].push_back(a);
  }
  memset(match, -1, sizeof match);
  for (int i = 0; i < k + 1; ++i) {
	if (match[i] == -1) {
	  int v = find_path(i, k + 1);
	  while (v != -1) {
		int pv = p[v], ppv = match[pv];
		match[v] = pv, match[pv] = v;
		v = ppv;
		// cout << v;
	  }
	}
	// cout << match[i];
  }
    cout<< "\nМаксимальное паросочетание"<< endl;
  set<int> st;
  for (int i = 0; i < k + 1; ++i) {
	if (match[i] == -1) {
	  continue;
	} else {
	  if (!st.count(i)) {
		cout << i << ' ' << match[i] << endl;
		st.insert(match[i]);
	  }
	}
  }

  // <><><><><><><><><><><><><><><><><><><><><><>

  // ofstream out("graph.dot");
  // if (!out.is_open())
  // {
  //     cerr << "Error: Unable to create graph file!" << endl;
  //     exit(1);
  // }

  // out << "digraph G {" << endl;
  // out << "    A <> B;" << endl;
  // out << "    B <> C;" << endl;
  // out << "    C <> D;" << endl;
  // out << "    D <> A;" << endl;
  // out << "}" << endl;

  // out.close();

  // int systemCh = system("dot -Tpng graph.dot -o graph.png");
  // if (systemCh == -1)
  // {
  //     cout << "Fail" << endl;
  // }

  // -------------------------------------------------------------------

  //     ofstream dotFile;
  // dotFile.open("graph.dot");
  // dotFile << "graph G {" << endl;
  // dotFile << "  edge [color=black]" << endl;
  // dotFile << "  node [shape=circle]" << endl;
  // dotFile << "  1--2 [color=red]" << endl;
  // dotFile << "  1--3 [color=green]" << endl;
  // dotFile << "  2--4 [color=blue]" << endl;
  // dotFile << "}" << endl;
  // dotFile.close();

  // int systemCh = system("dot -Tpng graph.dot -o graph.png");
  // int systemCh1 = system("open graph.png");
  // if (systemCh == -1)
  // {
  //     cout << "Fail" << endl;
  // }    if (systemCh1 == -1)
  // {
  //     cout << "Fail" << endl;
  // }

  // -----------------------------------------------------------------

  // while (!st.empty())
  // {
  //     cout << st.();
  // }
}