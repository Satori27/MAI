    #include <iostream>
    #include <queue>
    #include <vector>
    using namespace std;
     
    using graph = vector<vector<int>>;
     
    // vector<int> bfs(int u, graph &g)
    // {
    //     int n = g.size();
    //     vector<int> d(n, -1);
    //     d[u] = 0;
    //     queue<int> q;
    //     q.push(u);
    //     while (!q.empty())
    //     {
    //         u = q.front();
    //         q.pop();
    //         for (int v : g[u])
    //         {
    //             if (d[v] == -1)
    //             {
    //                 d[v] = 1 + d[u];
    //                 q.push(v);
    //             }
    //         }
    //     }
    //     return d;
    // }
     
    bool dfs(int u, const graph &g, vector<int> &mt, vector<int> visited)
    {
        if (visited[u])
        {
            return false;
        }
        visited[u] = true;
        for (int v : g[u])
        {
            if (mt[v] == -1 || dfs(mt[v], g, mt, visited))
            {
                mt[v] = u;
                return true;
            }
            //     bool tmp = dfs(mt[v], g, mt, visited);
            //     if (tmp)
            //     {
            //         mt[v] = u;
            //         return true;
            //     }
        }
        return false;
    }
     
    int main()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        int n, m;
        cin >> n >> m;
        ++n;
        graph g(n);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            g[u].push_back(v);
            // g[v].push_back(u);
        }
        // vector<int> d = bfs(0, g);
        int ans = 0;
        vector<int> mt(n, -1);
        vector<int> visited;
        for (int i = 0; i < n; ++i)
        {
            visited.assign(n, false);
            // if (d[i] & 1)
            // {main2.cpp
            //     continue;
            // }
            if (dfs(i, g, mt, visited))
            {
                ans += 1;
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; ++i)
        {
            if (mt[i] == -1)
            {
                continue;
            }
            cout << i + 1 << " " << mt[i] + 1 << endl;
        }
    }