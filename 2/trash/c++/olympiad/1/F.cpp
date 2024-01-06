#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using pii = pair<int, int>;

vector<int> dx = {1, -1, 0, 0};
vector<int> dy = {0, 0, 1, -1};

using grid = vector<string>;

bool check(int x, int n)
{
    return (0 <= x and x < n);
}

bool check2d(int x, int y, int n, int m)
{
    return (check(x, n) and check(y, m));
}

void bfs(int x, int y, const grid &g, vector<vector<int>> &dst)
{
    int n = g.size();
    int m = g[0].size();
    dst[x][y] = 0;
    queue<pii> q;
    q.push({x, y});
    while (!q.empty())
    {
        pii el = q.front();
        q.pop();
        x = el.first;
        y = el.second;
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (check2d(nx, ny, n, m) and g[nx][ny] == '.' and dst[nx][ny] == -1)
            {
                dst[nx][ny] = dst[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    grid g(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> g[i];
    }
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    vector<vector<int>> dst(n, vector<int>(m, -1));
    bfs(x, y, g, dst);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << dst[i][j] << ' ';
        }
        cout << endl;
    }
}