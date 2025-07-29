#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 15

void readInput(int *n, int latency[MAX][MAX]) {
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            scanf("%d", &latency[i][j]);
        }
    }
}

int calculateLatency(int n, int latency[MAX][MAX], int path[]) {
    int totalLatency = 0;
    for (int i = 0; i < n - 1; i++) {
        totalLatency += latency[path[i]][path[i + 1]];
    }
    totalLatency += latency[path[n - 1]][path[0]]; // Return to starting server
    return totalLatency;
}

void permute(int n, int latency[MAX][MAX], int path[], bool visited[], int pos, int *minLatency) {
    if (pos == n) {
        int currentLatency = calculateLatency(n, latency, path);
        if (currentLatency < *minLatency) {
            *minLatency = currentLatency;
        }
        return;
    }
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            path[pos] = i;
            permute(n, latency, path, visited, pos + 1, minLatency);
            visited[i] = false;
        }
    }
}

void generatePermutations(int n, int *minLatency, int latency[MAX][MAX]) {
    int path[MAX];
    bool visited[MAX] = {false};
    
    for (int i = 0; i < n; i++) {
        visited[i] = true;
        path[0] = i;
        permute(n, latency, path, visited, 1, minLatency);
        visited[i] = false;
    }
}

int main() {
    int n;
    int latency[MAX][MAX];
    int minLatency = INT_MAX;
    
    readInput(&n, latency);
    generatePermutations(n, &minLatency, latency);
    
    printf("%d\n", minLatency);
    return 0;
}
