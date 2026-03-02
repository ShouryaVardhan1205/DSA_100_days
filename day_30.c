#include <stdio.h>
#include <stdlib.h>

struct node {
    int coeff;
    int exp;
    struct node* next;
};

// Function to create a new node
struct node* createNode(int c, int e) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->coeff = c;
    newNode->exp = e;
    newNode->next = NULL;
    return newNode;
}

// Insert at end
struct node* insertTerm(struct node* head, int c, int e) {
    struct node* newNode = createNode(c, e);

    if (head == NULL)
        return newNode;

    struct node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    return head;
}

// Display polynomial
void display(struct node* head) {
    struct node* temp = head;

    while (temp != NULL) {
        if (temp->exp == 0)
            printf("%d", temp->coeff);
        else if (temp->exp == 1)
            printf("%dx", temp->coeff);
        else
            printf("%dx^%d", temp->coeff, temp->exp);

        if (temp->next != NULL)
            printf(" + ");

        temp = temp->next;
    }
}

int main() {
    int n, coeff, exp;
    struct node* head = NULL;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        head = insertTerm(head, coeff, exp);
    }

    display(head);

    return 0;
}