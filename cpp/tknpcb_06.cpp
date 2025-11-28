#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    while (Q--) {
        int x;
        cin >> x;
        auto lower = lower_bound(A.begin(), A.end(), x);
        auto upper = upper_bound(A.begin(), A.end(), x);
        cout << upper - lower << "\n";
    }

    return 0;
}
