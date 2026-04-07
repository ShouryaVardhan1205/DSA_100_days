#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// DFS function to detect cycle
bool dfs(int node, int** graph, int* graphSize, bool* visited, bool* recStack) {
    
    visited[node] = true;
    recStack[node] = true;

    for (int i = 0; i < graphSize[node]; i++) {
        int neighbor = graph[node][i];

        // If not visited, recurse
        if (!visited[neighbor]) {
            if (dfs(neighbor, graph, graphSize, visited, recStack))
                return true;
        }
        // If neighbor is in recursion stack → cycle
        else if (recStack[neighbor]) {
            return true;
        }
    }

    // Remove node from recursion stack
    recStack[node] = false;
    return false;
}

// Function to check cycle in graph
bool hasCycle(int V, int** graph, int* graphSize) {
    bool* visited = (bool*)calloc(V, sizeof(bool));
    bool* recStack = (bool*)calloc(V, sizeof(bool));

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, graph, graphSize, visited, recStack)) {
                free(visited);
                free(recStack);
                return true;
            }
        }
    }

    free(visited);
    free(recStack);
    return false;
}

// Driver code
int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    // Allocate graph
    int** graph = (int**)malloc(V * sizeof(int*));
    int* graphSize = (int*)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int)); // max edges
    }

    // Input edges (directed)
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][graphSize[u]++] = v;
    }

    if (hasCycle(V, graph, graphSize))
        printf("YES\n");
    else
        printf("NO\n");

    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    free(graphSize);

    return 0;
}