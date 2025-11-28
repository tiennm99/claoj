#include <stdio.h>
#include <math.h>

int main() {
    long long a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);

    double numerator = 4.0 * (a * b + b * c + c * a);
    double denominator = sqrt((double) (a * b * c));

    printf("%.0f\n", numerator / denominator);
    return 0;
}
