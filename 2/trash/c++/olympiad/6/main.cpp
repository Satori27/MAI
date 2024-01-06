#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> z_func(const string &s)
{
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i < r)
        {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < n and s[z[i]] == s[i + z[i]])
        {
            ++z[i];
        }
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int main()
{
    string s;
    int64_t ans =0; 
    cin >> s;
    vector<int> z = z_func(s);
    for (size_t i = 0; i < z.size(); ++i)
    {
        for (size_t j = 0; j < z.size(); ++j)
        {
            if(z[i] != z[j]){
                ++ans;
            }
        }
        --ans;
    }
    cout << ans-1<< endl;
}