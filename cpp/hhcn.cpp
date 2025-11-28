#include <bits/stdc++.h>
using namespace std;

int main() {
    long long A, B, C;
    cin >> A >> B >> C;

    long long a = sqrt((long double)A * C / B);
    long long b = sqrt((long double)A * B / C);
    long long c = sqrt((long double)B * C / A);

    cout << 4 * (a + b + c);
    return 0;
}
