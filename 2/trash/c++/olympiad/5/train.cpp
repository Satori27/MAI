// Kuhn паросочетания в двудольном графе, выводит пары
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using graph = vector<vector<int>>;

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
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> d = bfs(0, g);
    int ans = 0;
    vector<int> mt(n, -1);
    for (int i = 0; i < n; ++i)
    {
        if (d[i] & 1)
        {
            continue;
        }
        vector<int> visited(n, false);
        ans += dfs(i, g, mt, visited);
    }
    for (int i = 0; i < n; ++i)
    {
        if (mt[i] == -1)
        {
            continue;
        }
        cout << i + 1 << " " << mt[i] + 1 << endl;
    }
}

---------------------------------------------------------------------------


// Dinic O(m*sqrt(n))
#include <iostream>
#include <vector>
#include <queue>
using ll = int64_t;
const ll INF = 1e18;
using namespace std;

struct network
{
    struct edge
    {
        int u, v;
        ll f, c;
        edge(int _u, int _v, ll _c) : u(_u), v(_v), f(0), c(_c) {}
    };
    int n;
    vector<edge> edges;
    vector<vector<int>> g;
    vector<int> d;
    vector<size_t> ptr;
    network(int _n) : n(_n), g(n) {}

    void add_edge(int u, int v, ll c)
    {
        g[u].push_back(edges.size());
        edges.push_back(edge(u, v, c));
        g[v].push_back(edges.size());
        edges.push_back(edge(v, u, 0));
    }
    friend ostream &operator<<(ostream &out, const network &g)
    {
        int m = g.edges.size();
        for (int i = 0; i < m; i += 2)
        {
            edge elem = g.edges[i];
            cout << elem.u + 1 << ' ' << elem.v + 1 << ' ' << elem.f << "/" << elem.c << endl;
        }
        return out;
    }

    void bfs(int u, ll b)
    {
        d.assign(n, -1);
        queue<int> q;
        q.push(u);
        d[u] = 0;
        while (!q.empty())
        {
            u = q.front();
            q.pop();
            for (int ind : g[u])
            {
                ll c = edges[ind].c;
                ll f = edges[ind].f;
                if (c - f < b)
                {
                    continue;
                }
                int v = edges[ind].v;
                if (d[v] == -1)
                {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    ll dfs(int u, int finish, ll b, ll fp)
    {
        if (u == finish)
        {
            return fp;
        }
        for (; ptr[u] < g.size(); ++ptr[u])
        {
            int ind = g[u][ptr[u]];
            ll c = edges[ind].c;
            ll f = edges[ind].f;
            if (c - f < b)
            {
                continue;
            }
            int v = edges[ind].v;
            if (d[v] != d[u] + 1)
            {
                continue;
            }
            ll tmp = dfs(v, finish, b, min(c - f, fp));
            if (tmp > 0)
            {
                edges[ind].f += tmp;
                edges[ind ^ 1].f = tmp;
                return tmp;
            }
        }
        return 0;
    }

    ll dinic(int start, int finish, ll b)
    {
        ll res = 0;
        while (1)
        {
            bfs(start, b);
            if (d[finish] == -1)
            {
                break;
            }
            ptr.assign(n, 0);
            while (1)
            {
                ll f = dfs(start, finish, b, INF);
                if (f > 0)
                {
                    res += f;
                }
                else
                {
                    break;
                }
            }
        }
        return res;
    }

    ll max_flow(int start, int finish)
    {
        d.clear();
        d.resize(n, -1);
        ptr.clear();
        ptr.resize(n, 0);
        ll res = 0;
        for (int pow = 30; pow >= 0; --pow)
        {
            res += dinic(start, finish, 1ll << pow);
        }
        return res;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    network g(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        --u, --v;
        g.add_edge(u, v, c);
    }
    int start = 1;
    int finish = 8;
    ll ans = g.max_flow(start - 1, finish - 1);
    cout << ans << endl;
    cout << g << endl;
}