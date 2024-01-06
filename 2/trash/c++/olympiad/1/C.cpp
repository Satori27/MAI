#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
using graph = vector<vector<int>>;

vector<char> visited;

bool dfs(int u, int f, const graph &g, vector<int> &path)
{
    if (visited[u])
    {
        return false;
    }

    visited[u] = true;
    path.push_back(u);
    if (u == f)
    {
        return true;
    }
    for (int v : g[u])
    {
        bool tmp = dfs(v, f, g, path);
        if (tmp)
        {
            return true;
        }
    }
    path.pop_back();
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k, f;
    cin >> n >> m >> k >> f;
    graph g(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    --k;
    --f;
    visited.resize(n, 0);
    vector<int> path;
    bool ans = dfs(k, f, g, path);

    if (!ans)
    {
        cout << "-1\n";
    }
    else
    {
        for (int elem : path)
        {
            cout << elem + 1 << " ";
        }
        cout << endl;
    }
}
