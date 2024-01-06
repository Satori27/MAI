#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using ll = int64_t;

struct wedge
{
    int u, v;
};

int INF = 1e4;

// bool operator<(wedge a, wedge b)
// {
//     return a.w < b.w;
// }

struct dsu
{
    vector<int> leader;
    vector<set<int>> size;
    int n;
    dsu(int other_n)
    {
        n = other_n;
        leader.resize(n);
        for (int i = 0; i < n; ++i)
        {
            leader[i] = i;
        }
        size.resize(n);
    }

    ~dsu() = default;

    int find(int u)
    {
        if (leader[u] == u)
        {
            return u;
        }
        leader[u] = find(leader[u]);
        return leader[u];
    }

    bool unite(int u, int v)
    {
        int lu = find(u);
        int lv = find(v);
        if (lu == lv)
        {
            int size_min = INF;
            int size_max = -INF;
            int sum = 0;
            for (int elem: size[lv])
            {
                if (size_min > elem+1)
                {
                    size_min = elem+1;
                }
                if (size_max < elem+1)
                {
                    size_max = elem+1;
                }
                sum += elem+1;
            }
            cout << sum << ' ' << size_min << ' ' << size_max << endl;
            return false;
        }
        if (size[lu].size() > size[lv].size())
        {
            swap(lu, lv);
        }
        leader[lu] = lv;
        for (int elem : size[lu])
        {
            size[lv].insert(elem);
        }

        int size_min = INF;
        int size_max = -INF;
        int sum = 0;
        for (int elem: size[lv])
        {
            if (size_min > elem+1)
            {
                size_min = elem+1;
            }
            if (size_max < elem+1)
            {
                size_max = elem+1;
            }
            sum += elem+1;
        }
        cout << sum << ' ' << size_min << ' ' << size_max << endl;

        return true;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<wedge> edges;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        edges.push_back({u, v});
    }
    // sort(edges.begin(), edges.end());
    dsu d(n);
    // int w_total = 0;
    for (wedge elem : edges)
    {
        int u = elem.u;
        int v = elem.v;
        if (!d.unite(u, v))
        {
            continue;
        }
        // int w = elem.w;
        // w_total += w;
    }
    // cout << w_total << endl;
}
