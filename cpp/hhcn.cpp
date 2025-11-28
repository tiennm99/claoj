#include <bits/stdc++.h>
using namespace std;

int main() {
    long long a, b, c;
    cin >> a >> b >> c;
    long long x = sqrt(a * b / c);
    long long y = sqrt(b * c / a);
    long long z = sqrt(c * a / b);

    cout << 4 * (x + y + z);
    return 0;
}
