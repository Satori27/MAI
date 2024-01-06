#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = int64_t;

struct wedge
{
    int u, v;
};

// bool operator<(wedge a, wedge b)
// {
//     return a.w < b.w;
// }

struct dsu
{
    vector<vector<int>> leader;
    vector<int> size;
    int n;
    dsu(int other_n)
    {
        n = other_n;
        leader.resize(n);
        for (int i = 0; i < n; ++i)
        {
            leader[i][0] = i;
        }
        size.resize(n, 1);
    }

    ~dsu() = default;

    vector<int> find(int u)
    {
        if (leader[u][0] == u)
        {
            return leader[u];
        }
        leader[u].push_back(find(leader[u][u]));
        return leader[u];
    }

    bool unite(int u, int v)
    {
        int lu = find(u);
        int lv = find(v);
        if (lu == lv)
        {
            return false;
        }
        if (size[lu] > size[lv])
        {
            swap(lu, lv);
        }
        leader[lu] = lv;
        size[lv] += size[lu];
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
        cin >> u >> v ;
        --u; --v;
        edges.push_back({u, v});
    }
    // sort(edges.begin(), edges.end());
    dsu d(n);
    // ll w_total = 0;
    for(wedge elem: edges){
        int u = elem.u;
        int v = elem.v;
        if(!d.unite(u,v)){
            continue;
        }
        // ll w = elem.w;
        // w_total += w;
    }
    // cout << w_total << endl;
}
