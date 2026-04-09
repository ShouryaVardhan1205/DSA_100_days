#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int V;
    struct Node* adj[MAX];
};

// Create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Initialize graph
void initGraph(struct Graph* g, int V) {
    g->V = V;
    for (int i = 0; i < V; i++) {
        g->adj[i] = NULL;
    }
}

// Add directed edge u -> v
void addEdge(struct Graph* g, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = g->adj[u];
    g->adj[u] = newNode;
}

// Kahn's Algorithm
void topologicalSort(struct Graph* g) {
    int indegree[MAX] = {0};

    // Step 1: Calculate in-degrees
    for (int i = 0; i < g->V; i++) {
        struct Node* temp = g->adj[i];
        while (temp) {
            indegree[temp->vertex]++;
            temp = temp->next;
        }
    }

    // Step 2: Create queue
    int queue[MAX], front = 0, rear = 0;

    // Step 3: Add all vertices with indegree 0
    for (int i = 0; i < g->V; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int count = 0;

    printf("Topological Order: ");

    // Step 4: Process queue
    while (front < rear) {
        int u = queue[front++];
        printf("%d ", u);

        struct Node* temp = g->adj[u];
        while (temp) {
            indegree[temp->vertex]--;
            if (indegree[temp->vertex] == 0) {
                queue[rear++] = temp->vertex;
            }
            temp = temp->next;
        }
        count++;
    }

    // Step 5: Check for cycle
    if (count != g->V) {
        printf("\nCycle detected! Topological sort not possible.\n");
    }
}

// Driver code
int main() {
    struct Graph g;
    int V = 6;

    initGraph(&g, V);

    addEdge(&g, 5, 2);
    addEdge(&g, 5, 0);
    addEdge(&g, 4, 0);
    addEdge(&g, 4, 1);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 1);

    topologicalSort(&g);

    return 0;
}