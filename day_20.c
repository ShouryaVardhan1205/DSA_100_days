#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long prefix = 0;
    long long count = 0;

    // Using a simple large hash array (for prefix sum frequency)
    // Range handling using offset
    int size = 200001;
    long long *freq = (long long*)calloc(size, sizeof(long long));
    int offset = 100000;

    // Initial prefix sum = 0 occurs once
    freq[offset] = 1;

    for(int i = 0; i < n; i++) {
        prefix += arr[i];

        // If same prefix sum seen before, zero-sum subarray exists
        count += freq[prefix + offset];

        // Increase frequency of current prefix sum
        freq[prefix + offset]++;
    }

    printf("%lld\n", count);

    free(freq);
    return 0;
}