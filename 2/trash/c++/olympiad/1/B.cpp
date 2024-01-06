#include <iostream>
#include <queue>
#include <set>
using namespace std;
using graph = vector<vector<int>>;

int main()
{
    int64_t n, m, k;
    cin >> n >> m >> k;
    --k;
    graph g(n);
    set<int> vec_u;
    for (int i = 0; i < m; ++i)
    {
        int64_t u, v;
        cin >> u >> v;
        --u;
        --v;
        vec_u.insert(u);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<int> q;
    vector<int> path(n, -1);
    q.push(k);
    path[k] = 0;
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        for (size_t i = 0; i < g[t].size(); ++i)
        {
            int h = g[t][i];
            if (path[h] == -1)
            {
                path[h] = path[t] + 1;
                q.push(h);
            }
        }
    }
    for (int i = 0; i < n; ++i)
        cout << path[i] << ' ';
    return 0;
}