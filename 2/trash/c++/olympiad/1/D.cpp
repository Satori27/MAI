// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// using namespace std;

// using graph = vector<vector<int64_t>>;

// void bfs(int64_t s, const graph &g, vector<int64_t> &d, vector<int64_t> &p)
// {
//     queue<int64_t> q;
//     d[s] = 0;
//     p[s] = s;
//     q.push(s);
//     while (!q.empty())
//     {
//         int64_t u = q.front();
//         q.pop();
//         for (int64_t v : g[u])
//         {
//             if (d[v] == -1)
//             {
//                 d[v] = d[u] + 1;
//                 p[v] = u;
//                 q.push(v);
//             }
//         }
//     }
// }

// int64_t main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     int64_t n, m, s, f;
//     cin >> n >> m >> s >> f;
//     graph g(n);
//     for (int64_t i = 0; i < m; ++i)
//     {
//         int64_t u, v;
//         cin >> u >> v;
//         --u;
//         --v;
//         g[u].push_back(v);
//         g[v].push_back(u);
//     }
//     --s;
//     --f;

//     vector<int64_t> d(n, -1);
//     vector<int64_t> p(n, -1);
//     bfs(s, g, d, p);

//     vector<int64_t> path;
//     int64_t u;
//     u = f;

//     while (p[u] != u)
//     {
//         if (p[u] == -1)
//         {
//             cout << -1;
//             return 0;
//         }
//         path.push_back(u);
//         u = p[u];
//     }
//     path.push_back(u);
//     reverse(path.begin(), path.end());

//     for (int64_t el : path)
//     {
//         cout << el + 1 << ' ';
//     }
// }

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// using namespace std;

// using graph = vector<vector<int64_t>>;

// void bfs(int64_t s, const graph &g, vector<int64_t> &d, vector<int64_t> &p)
// {
//     queue<int64_t> q;
//     d[s] = 0;
//     p[s] = s;
//     q.push(s);
//     while (!q.empty())
//     {
//         int64_t u = q.front();
//         q.pop();
//         for (int64_t v : g[u])
//         {
//             if (d[v] == -1)
//             {
//                 d[v] = d[u] + 1;
//                 p[v] = u;
//                 q.push(v);
//             }
//         }
//     }
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     int64_t n, m, s, f;
//     cin >> n >> m >> s >> f;
//     graph g(n);
//     for (int64_t i = 0; i < m; ++i)
//     {
//         int64_t u, v;
//         cin >> u >> v;
//         --u;
//         --v;
//         g[u].push_back(v);
//         g[v].push_back(u);
//     }
//     --s;
//     --f;
//     for (size_t i = 0; i < g.size(); ++i)
//     {
//         sort(g[i].begin(), g[i].end());
//     }

//     vector<int64_t> d(n, -1);
//     vector<int64_t> p(n, -1);
//     bfs(s, g, d, p);

//     vector<int64_t> path;
//     int64_t u;
//     u = f;

//     while (p[u] != u)
//     {
//         if (p[u] == -1)
//         {
//             cout << -1;
//             return 0;
//         }
//         path.push_back(u);
//         u = p[u];
//     }
//     path.push_back(u);
//     reverse(path.begin(), path.end());

//     for (int64_t el : path)
//     {
//         cout << el + 1 << ' ';
//     }
//     cout << endl;
// }

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// using namespace std;

// using graph = vector<vector<int>>;

// void bfs(int s, const graph &g, vector<int> &d, vector<int> &p)
// {
//     queue<int> q;
//     d[s] = 0;
//     p[s] = s;
//     q.push(s);
//     while (!q.empty())
//     {
//         int u = q.front();
//         q.pop();
//         for (int v : g[u])
//         {
//             if (d[v] == -1)
//             {
//                 d[v] = d[u] + 1;
//                 p[v] = u;
//                 q.push(v);
//             }
//         }
//     }
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     int n, m, s, f;
//     cin >> n >> m >> s >> f;
//     graph g(n);
//     for (int i = 0; i < m; ++i)
//     {
//         int u, v;
//         cin >> u >> v;
//         --u;
//         --v;
//         g[u].push_back(v);
//         g[v].push_back(u);
//     }
//     --s;
//     --f;
//     for(size_t i = 0; i<g.size(); ++i){
//         sort(g[i].begin(), g[i].end());
//     }
//     vector<int> d(n, -1);
//     vector<int> p(n, -1);
//     bfs(s, g, d, p);

//     vector<int> path;
//     int u;
//     u = f;

//     while (p[u] != u)
//     {
//         if (p[u] == -1)
//         {
//             cout << -1;
//             return 0;
//         }
//         path.push_back(u);
//         u = p[u];
//     }
//     path.push_back(u);
//     reverse(path.begin(), path.end());

//     for (int el : path)
//     {
//         cout << el + 1 << ' ';
//     }
//     cout << endl;
// }