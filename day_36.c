#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    
    scanf("%d", &n);
    
    int *queue = (int *)malloc(n * sizeof(int));
    
    int front = 0, rear = -1;

    // Enqueue n elements
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        rear = (rear + 1) % n;
        queue[rear] = x;
    }

    // Number of dequeue operations
    scanf("%d", &m);

    // Perform dequeue
    for(int i = 0; i < m; i++) {
        front = (front + 1) % n;
    }

    // Display queue elements from front to rear
    int count = n - m;
    int i = front;
    for(int j = 0; j < count; j++) {
        printf("%d ", queue[i]);
        i = (i + 1) % n;
    }

    free(queue);
    return 0;
}