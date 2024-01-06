#include <iostream>
#include <vector>
using namespace std;
static const int MAX_D = 20;
// struct edge
// {
//     int u;
// };

using graph = vector<vector<int>>;

struct lca
{
    size_t n;
    int timer;
    vector<int> tin;
    vector<int> tout;
    vector<vector<int>> up;
    vector<int> d;
    // vector<vector<long long>> data;

    void dfs_timer(const graph &g, int u, int p)
    {
        tin[u] = ++timer;
        for (int v : g[u])
        {
            if (v != p)
            {
                dfs_timer(g, v, u);
                up[v][0] = u;
            }
        }
        tout[u] = ++timer;
    }

    lca(const graph &g, int root)
    {
        tin.resize(n);
        tout.resize(n);
        size_t n = g.size();
        up.resize(n, vector<int>(MAX_D));
        // d.resize(n);
        // data.resize();
        up[root][0] = root;
        dfs_timer(g, root, -1);
        for (int j = 1; j < MAX_D; ++j)
        {
            for (size_t i = 0; i < n; ++i)
            {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }
    bool is_upper(int x, int y)
    {
        return tin[x] < tin[y] and tout[y] < tout[x];
    }

    // int find(int u, int v)
    // {
    //     if (d[u] > d[v])
    //     {
    //         swap(u, v);
    //     }
    //     int delta = d[v] - d[u];
    //     for (int j = MAX_D - 1; j >= 0; --j)
    //     {
    //         if (delta & (1 << j))
    //             // w+=data[v][j];
    //             v = up[v][j];
    //     }
    //     if (u == v)
    //     {
    //         return u;
    //     }
    //     for (int j = MAX_D - 1; j >= 0; --j)
    //     {
    //         if (up[u][j] != up[v][j])
    //         {
    //             //     w+=data[u][j];
    //             //     w+=data[v][j];
    //             u = up[u][j];
    //             v = up[v][j];
    //         }
    //     }
    //     // return w+data[v][0]+data[u][0];
    //     return up[u][0];
    // }

    // int path_len(int u, int v)
    // {
    //     if (d[u] > d[v])
    //     {
    //         swap(u, v);
    //     }
    //     int delta = d[v] - d[u];
    //     int res = delta;
    //     for (int j = MAX_D - 1; j >= 0; --j)
    //     {
    //         if (delta & (1 << j))
    //             v = up[v][j];
    //     }
    //     if (u == v)
    //     {
    //         return res;
    //     }
    //     for (int j = MAX_D - 1; j >= 0; --j)
    //     {
    //         if (up[u][j] != up[v][j])
    //         {
    //             u = up[u][j];
    //             v = up[v][j];
    //             res += 2 * (1 << j);
    //         }
    //     }
    //     return res + 2;
    // }

    // void leaf(int p)
    // {
    //     up.push_back(vector<int>(MAX_D));
    //     up[n][0] = p;
    //     d.push_back(d[p] + 1);
    //     for (int j = 1; j < MAX_D; ++j)
    //     {
    //         up[n][j] = up[up[n][j - 1]][j - 1];
    //     }
    //     ++n;
    // }
};

int main()
{
    int N;
    cin >> N;
    for (int j = 0; j < N; ++j)
    {
        int n;
        cin >> n;
        graph g(n);
        for (int i = 0; i < n - 1; ++i)
        {
            int u;
            cin >> u;
            --u;
            // if(u==i){continue;}
            g[u].push_back(i);
            // g[i].push_back(u);
        }
        int root = 1;
        lca item(g, root - 1);
        int q;
        cin >> q;
        while (q--)
        {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            if (item.is_upper(u, v))
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
            // cout << item.find(u, v) + 1 << ' ';
        }
    }
}