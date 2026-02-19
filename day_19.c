#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    qsort(arr, n, sizeof(int), compare);

    int left = 0;
    int right = n - 1;
    int min_sum = arr[0] + arr[n - 1];
    int res1 = arr[left], res2 = arr[right];

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (abs(sum) < abs(min_sum)) {
            min_sum = sum;
            res1 = arr[left];
            res2 = arr[right];
        }

        if (sum < 0) {
            left++;
        } else {
            right--;
        }
    }

    printf("%d %d", res1, res2);
    return 0;
}
