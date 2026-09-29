#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n, V;
    printf("Number of coins n and amount V: ");
    scanf("%d %d", &n, &V);
    int *c = malloc(n * sizeof(int)), *dp = malloc((V + 1) * sizeof(int));
    printf("Enter %d coin values: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);

    dp[0] = 0;
    for (int v = 1; v <= V; v++) {
        dp[v] = INT_MAX;
        for (int i = 0; i < n; i++)
            if (c[i] <= v && dp[v - c[i]] != INT_MAX && dp[v - c[i]] + 1 < dp[v])
                dp[v] = dp[v - c[i]] + 1;
    }
    printf("Minimum coins = %d\n", dp[V] == INT_MAX ? -1 : dp[V]);
    return 0;
}