// неориентированный граф
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = int64_t;
const ll MAXN = 1e4;

// bool operator==(pair<int, int> a, pair<int, int> b) {
//   return ((a.first == b.first && a.second == b.second) ||
//           (a.first == b.second && a.second == b.first));
// }

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
  int max_n = 0;
    cout << "Введите количество ребер, а потом ребра графа" << endl;
  cin >> k;
  vector<pair<int, int>> graph(MAXN + 1);
  for (int i = 0; i < k; ++i) {
    int min_n;
    int a, b;
    cin >> a >> b;
    min_n = max(a, b);
    graph[i] = {a, b};
    g[a].push_back(b);
    g[b].push_back(a);
    max_n = max(max_n, min_n);
  }
      cout<< "\nМаксимальное паросочетание"<< endl;
  k = max(k, max_n);
  memset(match, -1, sizeof match);
  for (int i = 0; i < k + 1; ++i) {
    if (match[i] == -1) {
      int v = find_path(i, k + 1);
      while (v != -1) {
        int pv = p[v], ppv = match[pv];
        match[v] = pv, match[pv] = v;
        v = ppv;
      }
    }
  }
  set<pair<int, int>> s;
  set<int> st;
  for (int i = 0; i < k + 1; ++i) {
    if (match[i] == -1) {
      continue;
    } else {
      if (!st.count(i)) {
        cout << i << ' ' << match[i] << endl;
        s.insert({i, match[i]});
        st.insert(match[i]);
      }
    }
  }
  ofstream outfile("graph.dot");

  outfile << "graph MyGraph {" << endl;
  outfile << "node [shape=circle, style=filled]" << endl;

  pair<int, int> zero = {0, 0};
  for (int i = 0; i < k; i++) {
    if (graph[i] == zero) {
      continue;
    }
    outfile << graph[i].first << " -- " << graph[i].second;

    if (s.count(graph[i])) {
      if (s.count(graph[i])) {
        outfile << " [color=red]";
        // cout << graph[i].first << ' ' << graph[i].second << endl;
      }
    } else {
      swap(graph[i].first, graph[i].second);
      if (s.count(graph[i])) {
        outfile << " [color=red]";
        // cout << graph[i].first << ' ' << graph[i].second << endl;
      } else
        outfile << " [color=black]";
    }
    outfile << endl;
  }
  outfile << "}" << endl;

  outfile.close();

  int systemCh = system("dot -Tpng graph.dot -o graph_pair.png");
  if (systemCh == -1) {
    cout << "Fail" << endl;
  }
}