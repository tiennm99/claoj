#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll calc(ll a, char op, ll b) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    return a * b;
}

vector<pair<ll, string> > getAll(vector<ll> &nums, vector<char> &ops) {
    int sz = nums.size();
    vector<pair<ll, string> > result;
    auto ts = [](ll x) { return to_string(x); };
    set<ll> seen;

    if (sz == 2) {
        ll v = calc(nums[0], ops[0], nums[1]);
        result.push_back({v, ts(nums[0]) + ops[0] + ts(nums[1])});
    } else if (sz == 3) {
        ll a = nums[0], b = nums[1], c = nums[2];
        char o1 = ops[0], o2 = ops[1];
        ll v1 = calc(a, o1, calc(b, o2, c));
        ll v2 = calc(calc(a, o1, b), o2, c);
        string s1 = ts(a) + o1 + "(" + ts(b) + o2 + ts(c) + ")";
        string s2 = "(" + ts(a) + o1 + ts(b) + ")" + o2 + ts(c);
        result.push_back({v1, s1});
        seen.insert(v1);
        if (!seen.count(v2)) {
            seen.insert(v2);
            result.push_back({v2, s2});
        }
    } else {
        ll a = nums[0], b = nums[1], c = nums[2], d = nums[3];
        char o1 = ops[0], o2 = ops[1], o3 = ops[2];
        vector<pair<ll, string> > all = {
            {calc(a, o1, calc(b, o2, calc(c, o3, d))), ts(a) + o1 + "(" + ts(b) + o2 + "(" + ts(c) + o3 + ts(d) + "))"},
            {calc(a, o1, calc(calc(b, o2, c), o3, d)), ts(a) + o1 + "((" + ts(b) + o2 + ts(c) + ")" + o3 + ts(d) + ")"},
            {
                calc(calc(a, o1, b), o2, calc(c, o3, d)),
                "(" + ts(a) + o1 + ts(b) + ")" + o2 + "(" + ts(c) + o3 + ts(d) + ")"
            },
            {calc(calc(a, o1, calc(b, o2, c)), o3, d), "(" + ts(a) + o1 + "(" + ts(b) + o2 + ts(c) + "))" + o3 + ts(d)},
            {calc(calc(calc(a, o1, b), o2, c), o3, d), "((" + ts(a) + o1 + ts(b) + ")" + o2 + ts(c) + ")" + o3 + ts(d)}
        };
        for (auto &p: all) {
            if (!seen.count(p.first)) {
                seen.insert(p.first);
                result.push_back(p);
            }
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<pair<ll, string> > > exprs(n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vector<ll> nums;
        vector<char> ops;
        ll num = 0;
        for (char c: s) {
            if (isdigit(c)) num = num * 10 + (c - '0');
            else {
                nums.push_back(num);
                num = 0;
                ops.push_back(c);
            }
        }
        nums.push_back(num);
        exprs[i] = getAll(nums, ops);
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return exprs[a].size() < exprs[b].size(); });

    vector<string> result(n);
    set<ll> used;

    function<bool(int)> solve = [&](int idx) -> bool {
        if (idx == n) return true;
        int i = order[idx];
        for (auto &p: exprs[i]) {
            if (!used.count(p.first)) {
                used.insert(p.first);
                result[i] = p.second;
                if (solve(idx + 1)) return true;
                used.erase(p.first);
            }
        }
        return false;
    };

    if (solve(0)) {
        for (auto &s: result) cout << s << "\n";
    } else {
        cout << "NO SOLUTION\n";
    }

    return 0;
}
