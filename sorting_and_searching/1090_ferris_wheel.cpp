#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for (int &i : w)
        cin >> i;
    sort(w.begin(), w.end());
    int i = 0, j = n - 1;
    int ans = 0;
    while (i <= j)
    {
        if (w[i] + w[j] <= x)
        {
            i++;
            j--;
        }
        else
        {
            j--;
        }
        ans++;
    }
    cout << ans << endl;
}