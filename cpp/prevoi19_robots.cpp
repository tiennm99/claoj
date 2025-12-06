#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int U;
ll N;
vector<ll> cu, cv;
ll u0, v0, min_u, max_u, min_v, max_v;
int parity;

vector<int> tree, lazy;
vector<ll> vs;

void push(int v) {
    if (lazy[v]) {
        tree[2 * v] += lazy[v];
        lazy[2 * v] += lazy[v];
        tree[2 * v + 1] += lazy[v];
        lazy[2 * v + 1] += lazy[v];
        lazy[v] = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int delta) {
    if (l > r) return;
    if (l == tl && r == tr) {
        tree[v] += delta;
        lazy[v] += delta;
        return;
    }
    push(v);
    int tm = (tl + tr) / 2;
    update(2 * v, tl, tm, l, min(r, tm), delta);
    update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, delta);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

bool hasValidGap(int v, int tl, int tr, int l, int r, ll u_lo, ll u_hi) {
    if (l > r || tree[v] > 0) return false;
    if (tl == tr) {
        ll v_lo = vs[tl];
        ll v_hi = vs[tl + 1] - 1;
        if (u_hi > u_lo || v_hi > v_lo) return true;
        return ((u_lo + v_lo) % 2 + 2) % 2 == parity;
    }
    push(v);
    int tm = (tl + tr) / 2;
    if (hasValidGap(2 * v, tl, tm, l, min(r, tm), u_lo, u_hi)) return true;
    return hasValidGap(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, u_lo, u_hi);
}

bool check(ll D) {
    if (D == 0) return true;

    vs.clear();
    vs.push_back(min_v);
    vs.push_back(max_v + 1);

    for (int i = 0; i < U; i++) {
        ll vlo = max(min_v, cv[i] - D + 1);
        ll vhi = min(max_v, cv[i] + D - 1);
        if (vlo <= vhi) {
            vs.push_back(vlo);
            vs.push_back(vhi + 1);
        }
    }
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    int M = vs.size() - 1;
    if (M <= 0) return true;

    tree.assign(4 * M + 10, 0);
    lazy.assign(4 * M + 10, 0);

    auto getIdx = [&](ll v) { return lower_bound(vs.begin(), vs.end(), v) - vs.begin(); };

    vector<tuple<ll, int, int, int> > events;
    for (int i = 0; i < U; i++) {
        ll ulo = max(min_u, cu[i] - D + 1);
        ll uhi = min(max_u, cu[i] + D - 1);
        ll vlo = max(min_v, cv[i] - D + 1);
        ll vhi = min(max_v, cv[i] + D - 1);

        if (ulo <= uhi && vlo <= vhi) {
            int vl_idx = getIdx(vlo);
            int vh_idx = getIdx(vhi + 1) - 1;
            if (vl_idx <= vh_idx && vh_idx < M) {
                events.push_back({ulo, 0, vl_idx, vh_idx});
                events.push_back({uhi + 1, 1, vl_idx, vh_idx});
            }
        }
    }

    events.push_back({min_u, -1, 0, 0});
    events.push_back({max_u + 1, 2, 0, 0});
    sort(events.begin(), events.end());

    int v_start = getIdx(min_v);
    int v_end = getIdx(max_v + 1) - 1;
    if (v_start > v_end || v_end >= M) return true;

    ll prev_u = min_u;

    for (auto &[u, type, vl, vh]: events) {
        if (u > max_u + 1) break;

        if (prev_u <= max_u && prev_u < u) {
            ll u_hi = min(u - 1, max_u);
            if (hasValidGap(1, 0, M - 1, v_start, v_end, prev_u, u_hi)) return true;
        }

        if (type == 0) update(1, 0, M - 1, vl, vh, 1);
        else if (type == 1) update(1, 0, M - 1, vl, vh, -1);
        prev_u = u;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> U >> N;
    cu.resize(U);
    cv.resize(U);

    for (int i = 0; i < U; i++) {
        ll x, y;
        cin >> x >> y;
        cu[i] = x + y;
        cv[i] = x - y;
    }

    ll sx, sy;
    cin >> sx >> sy;
    u0 = sx + sy;
    v0 = sx - sy;
    min_u = u0 - N;
    max_u = u0 + N;
    min_v = v0 - N;
    max_v = v0 + N;
    parity = ((u0 + v0) % 2 + 2) % 2;

    ll left = 0, right = 4e9;
    while (left < right) {
        ll mid = left + (right - left + 1) / 2;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }
    cout << left << endl;
    return 0;
}
