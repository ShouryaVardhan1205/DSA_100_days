#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at end
struct Node* insertEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL)
        return newNode;

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    return head;
}

// Get length of list
int getLength(struct Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Find intersection node
struct Node* findIntersection(struct Node* head1, struct Node* head2) {
    int len1 = getLength(head1);
    int len2 = getLength(head2);

    int diff = abs(len1 - len2);

    struct Node* longer = head1;
    struct Node* shorter = head2;

    if (len2 > len1) {
        longer = head2;
        shorter = head1;
    }

    // Move pointer of longer list by diff
    for (int i = 0; i < diff; i++)
        longer = longer->next;

    // Traverse together
    while (longer != NULL && shorter != NULL) {
        if (longer == shorter)
            return longer;

        longer = longer->next;
        shorter = shorter->next;
    }

    return NULL;
}

// Function to connect second list to first list at matching value
void createIntersection(struct Node* head1, struct Node* head2) {
    struct Node* temp2 = head2;

    while (temp2->next != NULL)
        temp2 = temp2->next;

    struct Node* temp1 = head1;

    while (temp1 != NULL) {
        if (temp1->data == head2->data) {
            temp2->next = temp1;
            return;
        }
        temp1 = temp1->next;
    }
}

int main() {
    int n, m, value;

    struct Node* head1 = NULL;
    struct Node* head2 = NULL;

    // First list
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        head1 = insertEnd(head1, value);
    }

    // Second list
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &value);
        head2 = insertEnd(head2, value);
    }

    // Create artificial intersection based on first common value
    struct Node* temp1 = head1;
    struct Node* temp2 = head2;
    while (temp2 != NULL) {
        temp1 = head1;
        while (temp1 != NULL) {
            if (temp1->data == temp2->data) {
                // Attach remaining part
                struct Node* t = head2;
                while (t->next != temp2)
                    t = t->next;
                t->next = temp1;
                break;
            }
            temp1 = temp1->next;
        }
        if (temp1 != NULL)
            break;
        temp2 = temp2->next;
    }

    struct Node* intersection = findIntersection(head1, head2);

    if (intersection != NULL)
        printf("%d\n", intersection->data);
    else
        printf("No Intersection\n");

    return 0;
}