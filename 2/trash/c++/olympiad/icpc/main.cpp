#include <bits/stdc++.h>

using namespace std;

void search(vector< vector<int> >& graph, vector<int>& type, vector< vector<int> >& end, int i, int prev, int u) {
    // cout << "Я от " << end[i][0] + 1 << " " << prev + 1 << " " << u + 1 << endl;
    if (graph[u].size() == 2 && type[u] == 2) {
        end[i].push_back(u);
        for (int v : graph[u]) {
            if (v == prev) continue;
            search(graph, type, end, i, u, v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> type(n);
    for (int i = 0; i < n; ++i)
        cin >> type[i];

    vector< vector<int> > graph(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector< vector<int> > end;

    // Ищем конечные береговые станции
    for (int i = 0; i < n; ++i) {
        if (type[i] == 2 && graph[i].size() == 1) {
            end.push_back({i});
        }
    }

    // cout << "Конечные: ";
    // for (int i = 0; i < end.size(); ++i)
    //     cout << end[i][0] + 1 << " ";
    // cout << endl;

    // Ищем цепочку конечных береговых
    for (int i = 0; i < end.size(); ++i) {
        int u = graph[ end[i][0] ][0];
        search(graph, type, end, i, end[i][0], u);
    }

    // Ищем, какую из цепочек нам лучше взять
    int sum_ = 0,
    max_1 = 0,
    max_2 = 0;
    for (int i = 0; i < end.size(); ++i) {
        sum_ += end[i].size();

        int tmp = end[i].size();
        if (tmp > max_1)
            max_1 = tmp;
        else if (tmp > max_2)
            max_2 = tmp;
    }

    // cout << "Сумма: " << sum_ << endl;
    // cout << "Максимальные: " << max_1 << " " << max_2 << endl;

    cout << n - sum_ + max_1 + max_2 << endl;
}