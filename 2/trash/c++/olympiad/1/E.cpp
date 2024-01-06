#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using graph = vector<vector<int>>;
vector<int> cycle;
vector<int> path;

bool dfs(int u, long long prew, const graph &g, vector<int> &color, vector<int> &path, vector<int> &cycle)
{
    if (color[u] == 2)
    {
        return false;
    }
    path.push_back(u);
    color[u] = 1;
    for (int v : g[u])
    {
        if (prew != v)
        {
            if (color[v] == 1)
            {
                cycle.push_back(v);
                int ind = path.size() - 1;
                while (path[ind] != v)
                {
                    cycle.push_back(path[ind]);
                    --ind;
                }

                return true;
            }
            bool res = dfs(v, u, g, color, path, cycle);
            if (res)
            {
                return true;
            }
        }
    }
    color[u] = 2;
    path.pop_back();
    return false;
}

int main()
{
    int n;
    cin >> n;
    graph g(n);
    for (int i = 0; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> color(n, 0);
    vector<int> cycle;
    vector<int> path;
    bool hc = dfs(0, 0, g, color, path, cycle);
    sort(cycle.begin(), cycle.end());
    if (hc)
    {
        for (int elem : cycle)
        {
            cout << elem + 1 << ' ';
        }
        cout << endl;
    }
}