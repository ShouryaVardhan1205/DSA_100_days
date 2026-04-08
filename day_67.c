#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adj[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top = -1;
int V;

// Function to push into stack
void push(int v) {
    stack[++top] = v;
}

// DFS function
void dfs(int v) {
    visited[v] = 1;

    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visited[i]) {
            dfs(i);
        }
    }

    // Push after visiting all neighbors
    push(v);
}

// Topological Sort function
void topologicalSort() {
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    printf("Topological Ordering: ");
    while (top != -1) {
        printf("%d ", stack[top--]);
    }
}

// Main function
int main() {
    int E, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1; // Directed edge
    }

    topologicalSort();

    return 0;
}