#include <iostream>
#include <set>
#include <queue>
#include <vector>
using namespace std;

using graph = vector<set<int>>;

vector<int> bfs(int u, graph &g)
{
    int n = g.size();
    vector<int> d(n, -1);
    d[u] = 0;
    queue<int> q;
    q.push(u);
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (int v : g[u])
        {
            if (d[v] == -1)
            {
                d[v] = 1 + d[u];
                q.push(v);
            }
        }
    }
    return d;
}

bool dfs(int u, const graph &g, vector<int> &mt, vector<int> visited)
{
    if (visited[u])
    {
        return false;
    }
    visited[u] = true;
    for (int v : g[u])
    {
        if (mt[v] == -1)
        {
            mt[v] = u;
            return true;
        }
        bool tmp = dfs(mt[v], g, mt, visited);
        if (tmp)
        {
            mt[v] = u;
            cout << mt[v] << endl;
            return true;
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    graph g(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        // if(u==v){continue;}
        --u;
        --v;
        g[u].insert(v);
        g[v].insert(u);
    }
    vector<int> d;
    d = bfs(0, g);
    int ans = 0;
    vector<int> mt(n, -1);
    for (int i = 0; i < n; ++i)
    {
        if (d[i] & 1 || g[i].size() == 0)
        {
            continue;
        }
        vector<int> visited(n, false);
        ans = ans + dfs(i, g, mt, visited);
    }
    for (size_t u = 0; u < g.size(); ++u)
    {
        for (int v : g[u])
        {
            if (d[u] == d[v] && d[v] != -1 && d[u] != -1)
            {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    cout << ans << endl;
    for (int i = 0; i < n; ++i)
    {
        // if (mt[i] == -1)
        // {
        //     continue;
        // }
        cout << mt[i] + 1 << " " << i + 1 << endl;
    }
}
