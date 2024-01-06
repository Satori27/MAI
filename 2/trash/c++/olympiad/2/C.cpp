#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

using ll = int64_t;
ll INF = 1e18;
using item = pair<ll, int>;

struct wedge
{
    int u, v;
    ll w;
};

using wgraph = vector<vector<wedge>>;

void djikstra_fast(wgraph &g, const int u, vector<ll> &d, vector<int> &prev)
{
    int n = g.size();
    d[u] = 0;
    prev[u] = u;
    set<item> pq;
    for (int i = 0; i < n; ++i)
    {
        pq.insert({d[i], i});
    }
    vector<char> visited(n, false);
    while (!pq.empty())
    {
        item el = *pq.begin();
        pq.erase(pq.begin());
        int u = el.second;
        visited[u] = true;
        for (wedge elem : g[u])
        {
            int v = elem.v;
            if (visited[v])
            {
                continue;
            }
            ll w = elem.w;
            if (d[u] + w < d[v])
            {
                pq.erase({d[v], v});
                d[v] = d[u] + w;
                prev[v] = u;
                pq.insert({d[v], v});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, start;
    cin >> n >> m >> start;
    --start;
    wgraph g(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        g[u].push_back({u, v, w});
        g[v].push_back({v, u, w});
    }
    vector<ll> d(n, INF);
    vector<int> prev(n, -1);
    djikstra_fast(g, start, d, prev);

    for (ll elem : d)
    {
        if (elem != INF)
        {
            cout << elem << ' ';
        }
        else
        {
            cout << -1 << ' ';
        }
    }
    cout << endl;
}