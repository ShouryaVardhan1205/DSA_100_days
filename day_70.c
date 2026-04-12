#include <stdio.h>
#include <string.h>

#define EMPTY -1

int table[100];  // assuming max size

// Insert using quadratic probing
void insert(int key, int m) {
    int index, i = 0;

    while (i < m) {
        index = (key % m + i * i) % m;

        if (table[index] == EMPTY) {
            table[index] = key;
            return;
        }
        i++;
    }

    printf("Hash table is full, cannot insert %d\n", key);
}

// Search using quadratic probing
int search(int key, int m) {
    int index, i = 0;

    while (i < m) {
        index = (key % m + i * i) % m;

        if (table[index] == EMPTY)
            return 0;  // not found

        if (table[index] == key)
            return 1;  // found

        i++;
    }
    return 0;
}

int main() {
    int m, n;
    scanf("%d", &m);   // size of hash table
    scanf("%d", &n);   // number of operations

    // Initialize table
    for (int i = 0; i < m; i++)
        table[i] = EMPTY;

    char operation[10];
    int key;

    for (int i = 0; i < n; i++) {
        scanf("%s %d", operation, &key);

        if (strcmp(operation, "INSERT") == 0) {
            insert(key, m);
        } 
        else if (strcmp(operation, "SEARCH") == 0) {
            if (search(key, m))
                printf("FOUND\n");
            else
                printf("NOT FOUND\n");
        }
    }

    return 0;
}