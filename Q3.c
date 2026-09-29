#include <stdio.h>
#include <string.h>
#define N 1001

char X[N], Y[N], S[N];
int L[N][N];

int main() {
    printf("Enter X (no spaces): "); scanf("%1000s", X);
    printf("Enter Y (no spaces): "); scanf("%1000s", Y);
    int m = strlen(X), n = strlen(Y);

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i-1] == Y[j-1]) L[i][j] = L[i-1][j-1] + 1;
            else L[i][j] = L[i-1][j] > L[i][j-1] ? L[i-1][j] : L[i][j-1];

    int k = L[m][n], i = m, j = n;       /* trace back */
    S[k] = '\0';
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) { S[--k] = X[i-1]; i--; j--; }
        else if (L[i-1][j] >= L[i][j-1]) i--;
        else j--;
    }
    printf("LCS length = %d\nLCS = %s\n", L[m][n], S);
    return 0;
}