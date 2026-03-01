#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

// Create new node
struct node* create_node(int value) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Rotate list right by k
struct node* rotate_right(struct node* head, int k) {
    if (head == NULL || head->next == NULL || k == 0)
        return head;

    struct node *temp = head;
    int n = 1;

    // Count nodes
    while (temp->next != NULL) {
        temp = temp->next;
        n++;
    }

    // Make circular
    temp->next = head;

    k = k % n;
    int steps = n - k;

    struct node *new_tail = head;

    // Move to (n-k)th node
    for (int i = 1; i < steps; i++) {
        new_tail = new_tail->next;
    }

    struct node *new_head = new_tail->next;

    // Break circular link
    new_tail->next = NULL;

    return new_head;
}

// Print list
void print_list(struct node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main() {
    int n, value, k;
    scanf("%d", &n);

    struct node *head = NULL, *tail = NULL;

    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        struct node* new_node = create_node(value);

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    scanf("%d", &k);

    head = rotate_right(head, k);

    print_list(head);

    return 0;
}