#include <stdio.h>
#include <stdlib.h>

int minCostClimbingStairs(int cost[], int n) {
    
    int *dp = (int *)malloc(n * sizeof(int));

  
    dp[0] = cost[0];
    dp[1] = cost[1];


    for (int i = 2; i < n; i++) {
        dp[i] = cost[i] + (dp[i-1] < dp[i-2] ? dp[i-1] : dp[i-2]);
    }

  
    int result = dp[n-1] < dp[n-2] ? dp[n-1] : dp[n-2];

   
    free(dp);

    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    int *cost = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &cost[i]);
    }
   
    int result = minCostClimbingStairs(cost, n);
    printf("%d\n", result);
    free(cost);
    return 0;
}
