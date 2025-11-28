#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;

string to_str(i128 x) {
    if (x == 0) return "0";
    string s;
    bool neg = false;
    if (x < 0) {
        neg = true;
        x = -x;
    }
    while (x > 0) {
        s += '0' + (x % 10);
        x /= 10;
    }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    return s;
}

vector<pair<i128, string> > get_all(int l, int r, const vector<i128> &nums, const vector<string> &num_strs,
                                    const vector<char> &ops) {
    if (l == r) {
        return {{nums[l], num_strs[l]}};
    }
    vector<pair<i128, string> > res;
    for (int m = l; m < r; m++) {
        auto lefts = get_all(l, m, nums, num_strs, ops);
        auto rights = get_all(m + 1, r, nums, num_strs, ops);
        for (auto &le: lefts) {
            for (auto &ri: rights) {
                i128 v;
                char op = ops[m];
                if (op == '+') v = le.first + ri.first;
                else if (op == '-') v = le.first - ri.first;
                else v = le.first * ri.first;
                string left_str = le.second;
                if (m > l) left_str = "(" + left_str + ")";
                string right_str = ri.second;
                if (r > m + 1) right_str = "(" + right_str + ")";
                string s = left_str + op + right_str;
                res.push_back({v, s});
            }
        }
    }
    return res;
}

vector<int> matchL, matchR;
vector<bool> vis;

bool dfs(int u, const vector<vector<int> > &g) {
    for (int v: g[u]) {
        if (vis[v]) continue;
        vis[v] = true;
        if (matchR[v] == -1 || dfs(matchR[v], g)) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<map<i128, string> > all_poss(n);
    vector<string> expressions(n);
    for (int i = 0; i < n; i++) {
        cin >> expressions[i];
    }

    for (int i = 0; i < n; i++) {
        string s = expressions[i];
        vector<string> num_strs;
        vector<char> ops;
        string cur = "";
        for (char c: s) {
            if (isdigit(c)) {
                cur += c;
            } else {
                if (!cur.empty()) {
                    num_strs.push_back(cur);
                }
                ops.push_back(c);
                cur = "";
            }
        }
        if (!cur.empty()) {
            num_strs.push_back(cur);
        }
        int k = num_strs.size();
        vector<i128> nums(k);
        for (int j = 0; j < k; j++) {
            i128 val = 0;
            for (char d: num_strs[j]) {
                val = val * 10 + (d - '0');
            }
            nums[j] = val;
        }
        auto res = get_all(0, k - 1, nums, num_strs, ops);
        for (auto &p: res) {
            all_poss[i][p.first] = p.second;
        }
    }

    set<i128> all_vals_set;
    for (auto &mp: all_poss) {
        for (auto &p: mp) {
            all_vals_set.insert(p.first);
        }
    }
    vector<i128> id_to_val(all_vals_set.begin(), all_vals_set.end());
    int m = id_to_val.size();
    map<i128, int> val_id;
    for (int j = 0; j < m; j++) {
        val_id[id_to_val[j]] = j;
    }

    vector<vector<int> > g(n);
    for (int i = 0; i < n; i++) {
        for (auto &p: all_poss[i]) {
            g[i].push_back(val_id[p.first]);
        }
    }

    matchL.assign(n, -1);
    matchR.assign(m, -1);
    int cnt = 0;
    for (int u = 0; u < n; u++) {
        vis.assign(m, false);
        if (dfs(u, g)) cnt++;
    }

    if (cnt == n) {
        for (int i = 0; i < n; i++) {
            i128 val = id_to_val[matchL[i]];
            string s = all_poss[i][val];
            cout << s << endl;
        }
    } else {
        cout << "NO SOLUTION" << endl;
    }

    return 0;
}
