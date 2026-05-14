#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<string> ans;
    string cur;
    vector<bool> used(n, false);
    sort(s.begin(), s.end());
    auto dfs = [&](auto &&self, string &cur)
    {
        if (cur.size() == s.size())
        {
            ans.push_back(cur);
            return;
        }
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && s[i] == s[i - 1] && !used[i - 1])
                continue;
            if (used[i])
                continue;
            used[i] = true;

            cur.push_back(s[i]);
            self(self, cur);

            cur.pop_back();
            used[i] = false;
        }
    };
    auto dfs2 = [&](auto &&self, int idx, string &s) -> void
    {
        if (idx == n)
        {
            ans.push_back(s);
            return;
        }
        unordered_set<char> st;
        for (int i = idx; i < n; i++)
        {
            if (st.count(s[i]))
                continue;
            st.insert(s[i]);
            swap(s[i], s[idx]);
            self(self, idx + 1, s);
            swap(s[i], s[idx]);
        }
    };
    // dfs(dfs, cur);
    dfs2(dfs2, 0, s);
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto &s : ans)
    {
        cout << s << endl;
    }
}