#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    map<string, int> count;
    for (int i = 0; i < 2 * N - 1; ++i) {
        string s;
        cin >> s;
        count[s]++;
    }

    for (auto &p: count) {
        if (p.second % 2 == 1) {
            cout << p.first << "\n";
            break;
        }
    }

    return 0;
}
