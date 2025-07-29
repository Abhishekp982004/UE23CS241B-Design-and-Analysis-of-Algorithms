#include <stdio.h>
#include <stdlib.h>

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* result = (int*)calloc(temperaturesSize, sizeof(int));
    int* stack = (int*)malloc(temperaturesSize * sizeof(int)); // Stack to store indices
    int top = -1; // Stack pointer

    for (int i = 0; i < temperaturesSize; i++) {
        // Check if the current temperature is warmer than the one represented by the top of the stack
        while (top >= 0 && temperatures[i] > temperatures[stack[top]]) {
            int idx = stack[top--]; // Pop the stack
            result[idx] = i - idx;  // Calculate the number of days to wait
        }
        stack[++top] = i; // Push the current day's index onto the stack
    }

    // Free the stack memory
    free(stack);

    return result;
}

int main() {
    int N;
    scanf("%d", &N);

    int* temperatures = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &temperatures[i]);
    }

    int returnSize;
    int* answer = dailyTemperatures(temperatures, N, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d", answer[i]);
        if (i < returnSize - 1) printf(" ");
    }
    printf("\n");

    free(temperatures);
    free(answer);
    return 0;
}
