// Ford - Bellman  O(n*m)
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

// ------------------------------------------------------------------------------------------------------------------------------------
// djikstra_slow O(n^2+m)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = int64_t;
ll INF = 1e18;

struct wedge
{
    int u, v;
    ll w;
};

using wgraph = vector<vector<wedge>>;

void djikstra_slow(wgraph &g, const int u, vector<ll> &d, vector<int> &prev)
{
    int n = g.size();
    d[u] = 0;
    prev[u] = u;
    vector<char> visited(n, false);
    for (int i = 0; i < n; ++i)
    {
        int min_id = -1;
        ll val = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visited[j] and d[j] < val)
            {
                min_id = j;
                val = d[j];
            }
        }
        int u = min_id;
        visited[u] = true;
        for (wedge el : g[u])
        {
            int v = el.v;
            ll w = el.w;
            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                prev[v] = u;
            }
        }
    }
}

int main()
{
    int n, m, start, finish;
    cin >> n >> m >> start >> finish;
    --start;
    --finish;
    wgraph g(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        g[u].push_back({u, v, w});
    }
    vector<ll> d(n, INF);
    vector<int> prev(n, -1);
    djikstra_slow(g, start, d, prev);
    vector<int> path;
    int u=finish;
    while(prev[u]!=u){
        path.push_back(u);
        u = prev[u];
    }
    path.push_back(u);
    reverse(path.begin(), path.end());
    for(int el: path){
        cout << el+1 << ' ';
    }
    // for(int elem: d){cout << elem << ' ';}
    cout << endl;
}

// -----------------------------------------------------------------------------------------------------
// djikstra_fast  O(n+mlogm)
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
            {   pq.erase({d[v], v});
                d[v] = d[u] + w;
                prev[v] = u;
                pq.insert({d[v], v});
            }
        }
    }
}

int main()
{
    int n, m, start, finish;
    cin >> n >> m >> start >> finish;
    --start;
    --finish;
    wgraph g(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u;
        --v;
        g[u].push_back({u, v, w});
    }
    vector<ll> d(n, INF);
    vector<int> prev(n, -1);
    djikstra_fast(g, start, d, prev);
    vector<int> path;
    int u = finish;
    while (prev[u] != u)
    {
        path.push_back(u);
        u = prev[u];
    }
    path.push_back(u);
    reverse(path.begin(), path.end());
    for (int el : path)
    {
        cout << el + 1 << ' ';
    }
    // for(int elem: d){cout << elem << ' ';}
    cout << endl;
}



// Floyd Warshell O(n^3)

#include <iostream>
#include <vector>
using ll=int64_t;
using namespace std;

const ll INF = 1e18;

using matrix = vector<vector<ll>>;

int main(){
    int n, m;
    cin>>n>>m;
    matrix g(n, vector<ll>(n, INF));
    for(int i=0;i<m;++i){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        --u;
        --v;
        g[u][v]=w;
    }
    matrix d(g);
    for(int i=0;i<n;++i){
        d[i][i]=0;
    }
    for(int k=0;k<n;++k){
        for(int u=0;u<n;++u){
            for(int v=0;v<n;++v){
                d[u][v]= min(d[u][v],d[u][k]+d[k][v]);
            }
        }
    }

    for(int u=0;u<n;++u){
            for(int v=0;v<n;++v){
                cout<<d[u][v]<<" ";
            }
            cout<<endl;
        }
}