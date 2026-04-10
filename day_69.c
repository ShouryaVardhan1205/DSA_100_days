#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Structure for adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Structure for graph
struct Graph {
    int V;
    struct Node* adj[MAX];
};

// Min Heap Node
struct MinHeapNode {
    int vertex;
    int dist;
};

// Min Heap
struct MinHeap {
    int size;
    struct MinHeapNode heap[MAX];
};

// Create new adjacency node
struct Node* createNode(int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

// Create graph
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;
    return graph;
}

// Add edge
void addEdge(struct Graph* graph, int u, int v, int w) {
    struct Node* newNode = createNode(v, w);
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;

    // For undirected graph, add reverse edge
    newNode = createNode(u, w);
    newNode->next = graph->adj[v];
    graph->adj[v] = newNode;
}

// Swap heap nodes
void swap(struct MinHeapNode* a, struct MinHeapNode* b) {
    struct MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify
void heapify(struct MinHeap* heap, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < heap->size && heap->heap[left].dist < heap->heap[smallest].dist)
        smallest = left;

    if (right < heap->size && heap->heap[right].dist < heap->heap[smallest].dist)
        smallest = right;

    if (smallest != i) {
        swap(&heap->heap[i], &heap->heap[smallest]);
        heapify(heap, smallest);
    }
}

// Extract min
struct MinHeapNode extractMin(struct MinHeap* heap) {
    struct MinHeapNode root = heap->heap[0];
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return root;
}

// Insert into heap
void insertHeap(struct MinHeap* heap, int v, int dist) {
    int i = heap->size++;
    heap->heap[i].vertex = v;
    heap->heap[i].dist = dist;

    while (i && heap->heap[(i - 1) / 2].dist > heap->heap[i].dist) {
        swap(&heap->heap[i], &heap->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Dijkstra Algorithm
void dijkstra(struct Graph* graph, int src) {
    int V = graph->V;
    int dist[MAX];

    struct MinHeap heap;
    heap.size = 0;

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }

    dist[src] = 0;
    insertHeap(&heap, src, 0);

    while (heap.size > 0) {
        struct MinHeapNode minNode = extractMin(&heap);
        int u = minNode.vertex;

        struct Node* temp = graph->adj[u];

        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                insertHeap(&heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print result
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

// Driver code
int main() {
    int V = 5;
    struct Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 0, 7);
    addEdge(graph, 3, 2, 6);
    addEdge(graph, 4, 1, 3);
    addEdge(graph, 4, 2, 9);
    addEdge(graph, 4, 3, 2);

    int src = 0;
    dijkstra(graph, src);

    return 0;
}