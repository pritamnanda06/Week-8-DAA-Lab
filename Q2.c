#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, V;
    printf("Number of coins n and amount V: ");
    scanf("%d %d", &n, &V);
    int *c = malloc(n * sizeof(int));
    printf("Enter %d distinct coin values: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);

    unsigned long long *dp = calloc(V + 1, sizeof(*dp));
    dp[0] = 1;
    for (int i = 0; i < n; i++)          /* coin outer => order ignored */
        for (int v = c[i]; v <= V; v++)
            dp[v] += dp[v - c[i]];
    printf("Number of combinations = %llu\n", dp[V]);
    return 0;
}