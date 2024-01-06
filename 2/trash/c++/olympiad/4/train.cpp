// Наименьший общий предок, дерево
#include <iostream>
#include <vector>
using namespace std;

struct edge
{
    int u, v;
};

using graph = vector<vector<edge>>;

void dfs(int u, int p, const graph &g, vector<int> &d)
{
    for (edge elem : g[u])
    {
        int v = elem.v;
        if (v == p)
        {
            continue;
        }
        d[v] = 1 + d[u];
        dfs(v, u, g, d);
    }
}

int main()
{
    int n;
    cin >> n;
    graph g(n);
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back({u, v});
        g[v].push_back({v, u});
    }
    int u = 0;
    vector<int> d1(n);
    dfs(u, u, g, d1);
    int v = 0;
    for (int i = 0; i < n; ++i)
    {
        if (d1[i] > d1[v])
        {
            v = i;
        }
    }
    vector<int> d2(n);
    dfs(v, v, g, d2);
    for (int i = 0; i < n; ++i)
    {
        if (d2[i] > d2[u])
        {
            u = i;
        }
    }
    cout << d2[u] << " "
         << "u = " << u + 1 << " "
         << "v = " << v + 1<< endl;
}

// -------------------------------------------------------------------------------------------------------------------



#include <iostream>
#include <vector>
using namespace std;
const int MAX_D = 20;
struct edge
{
    int u, v;
};

using graph = vector<vector<edge>>;

struct lca
{
    vector<vector<int>> up;
    vector<int> d;
    // vector<vector<long long>> data;
    int n;

    void dfs(int u, int p, const graph &g)
    {
        for (edge elem : g[u])
        {
            int v = elem.v;
            if (v == p)
            {
                continue;
            }
            d[v] = 1 + d[u];
            up[v][0] = u;
            dfs(v, u, g);
        }
    }

    lca(const graph &g, int root)
    {
        int n = g.size();
        up.resize(n, vector<int>(MAX_D));
        d.resize(n);
        // data.resize();
        up[root][0] = root;
        dfs(root, root, g);
        for (int j = 1; j < MAX_D; ++j)
        {
            for (int u = 0; u < n; ++u)
            {
                up[u][j] = up[up[u][j - 1]][j - 1];
            }
        }
    }
    int find(int u, int v)
    {
        if (d[u] > d[v])
        {
            swap(u, v);
        }
        int delta = d[v] - d[u];
        for (int j = MAX_D - 1; j >= 0; --j)
        {
            if (delta & (1 << j))
                // w+=data[v][j];
                v = up[v][j];
        }
        if (u == v)
        {
            return u;
        }
        for (int j = MAX_D - 1; j >= 0; --j)
        {
            if (up[u][j] != up[v][j])
            {
                //     w+=data[u][j];
                //     w+=data[v][j];
                u = up[u][j];
                v = up[v][j];
            }
        }
        // return w+data[v][0]+data[u][0];
        return up[u][0];
    }

    int path_len(int u, int v)
    {
        if (d[u] > d[v])
        {
            swap(u, v);
        }
        int delta = d[v] - d[u];
        int res = delta;
        for (int j = MAX_D - 1; j >= 0; --j)
        {
            if (delta & (1 << j))
                v = up[v][j];
        }
        if (u == v)
        {
            return res;
        }
        for (int j = MAX_D - 1; j >= 0; --j)
        {
            if (up[u][j] != up[v][j])
            {
                u = up[u][j];
                v = up[v][j];
                res += 2 * (1 << j);
            }
        }
        return res + 2;
    }

    void leaf(int p)
    {
        up.push_back(vector<int>(MAX_D));
        up[n][0] = p;
        d.push_back(d[p] + 1);
        for(int j=1;j<MAX_D; ++j){
            up[n][j]= up[up[n][j-1]][j-1];
        }
        ++n;
    }
};

int main()
{
    int n;
    cin >> n;
    graph g(n);
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back({u, v});
        g[v].push_back({v, u});
    }
    int root = 4;
    lca item(g, root - 1);
    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        cout << item.find(u, v) + 1 << ' ';
    }
}


