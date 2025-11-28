#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c;
    cin >> a >> b >> c;

    cout << 4 * (a * b + b * c + c * a) / sqrt(a * b * c);
    return 0;
}
