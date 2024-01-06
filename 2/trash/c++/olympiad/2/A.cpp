#include <iostream>
#include <vector>
using namespace std;

using ll = int64_t;
ll INF = 1e18;

struct wedge
{
    int u, v;
    ll w;
};

using wgraph = vector<vector<wedge>>;

int main()
{
    int n, m, start;
    cin >> n >> m >> start;
    --start;
    // wgraph g(n);
    vector<wedge> edges;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        edges.push_back({u, v, w});
        edges.push_back({v, u, w});
    }
    bool flag = true;
    vector<ll> dp(n, INF);
    dp[start] = 0;
    for (int i = 0; i < n; ++i)
    {
        flag = false;
        for (wedge elem : edges)
        {
            int u = elem.u;
            int v = elem.v;
            ll w = elem.w;
            if (dp[v] > dp[u] + w)
            {
                dp[v] = dp[u] + w;
                flag = true;
            }
        }
        if (!flag)
        {
            break;
        }
    }
    // int e = edges.size() - 1;
    // dp[e] = dp[e - 1] + edges[e - 1].w;
    if (flag)
    {
        cout << "Negative cycle\n";
    }
    else
    {
        for (ll el : dp)
        {
            if (el == 1e18)
            {
                cout << -1 << ' ';
                continue;
            }
            {
                cout << el << ' ';
            }
        }
        cout << endl;
    }
}