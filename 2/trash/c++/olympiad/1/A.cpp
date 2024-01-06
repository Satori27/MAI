#include <iostream>
#include <set>
#include <vector>
using namespace std;
using graph = vector<vector<int>>;

vector<int> cnt;
vector<char> visited;

void dfs(int u, int p, const graph &g, int &counter)
{
    if (visited[u])
    {
        return;
    }
    visited[u] = true;
    cnt[u] = counter;
    ++counter;
    for (int v : g[u])
    {
        if (v != p)
        {
            dfs(v, u, g, counter);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
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
    cnt.resize(n, -1);
    visited.resize(n, 0);
    int counter = 0;
    dfs(k, k, g, counter);
    for (int el : cnt)
    {
        cout << el << ' ';
    }
    cout << endl;
}