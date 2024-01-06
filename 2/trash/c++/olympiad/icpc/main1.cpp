#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b;

    cout << "? 0" << endl;
    cin >> a >> b;

    if (b == "main") {
        int n;

        int l = 0, r = 4 * 9;
        int m;
        while (true) {
            m = (l + r) / 2;

            cout << "? 0" << endl;
            cin >> a >> b;

            if (b == "side")
                break;
        }
    }
}