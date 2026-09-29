#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef unsigned long long ull;

/* next Collatz value, or 0 if 3n+1 would overflow */
ull next(ull n) {
    if (n % 2 == 0) return n / 2;
    return n > (ULLONG_MAX - 1) / 3 ? 0 : 3 * n + 1;
}

int trajectory(ull n) {
    ull steps = 0, peak = n;
    printf("%llu", n);
    while (n != 1) {
        ull nx = next(n);
        if (!nx) { printf("\nOverflow: 3n+1 exceeds 64 bits\n"); return 0; }
        n = nx; steps++;
        if (n > peak) peak = n;
        printf(" -> %llu", n);
    }
    printf("\nSteps = %llu, peak = %llu\n", steps, peak);
    return 1;
}

int analyseInterval(ull a, ull b) {
    unsigned *cache = calloc(b + 1, sizeof(unsigned));   /* cache[1] = 0 */
    if (!cache) { printf("Out of memory\n"); return 0; }
    unsigned best = 0;
    ull bestN = a;
    double total = 0;
    for (ull i = 2; i <= b; i++) {
        ull cur = i;
        unsigned s = 0;
        while (cur >= i) {
            if (!(cur = next(cur))) { printf("Overflow at %llu\n", i); free(cache); return 0; }
            s++;
        }
        cache[i] = s + cache[cur];
        if (i >= a) {
            total += cache[i];
            if (cache[i] > best) { best = cache[i]; bestN = i; }
        }
    }
    printf("Longest trajectory in [%llu,%llu]: n = %llu with %u steps, average = %.3f\n",
           a, b, bestN, best, total / (b - a + 1));
    free(cache);
    return 1;
}

int main() {
    ull n, a, b;
    printf("Enter start n >= 1: ");
    if (scanf("%llu", &n) != 1 || n < 1) { printf("n must be >= 1\n"); return 1; }
    if (!trajectory(n)) return 1;

    printf("Enter interval a b (1 <= a <= b): ");
    if (scanf("%llu %llu", &a, &b) != 2 || a < 1 || b < a) { printf("Invalid interval\n"); return 1; }
    return !analyseInterval(a, b);
}