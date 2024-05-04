#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void update(int* tree, int index, int value, int n) {
    assert(tree);

    while (index <= n) {
        tree[index] += value;
        index = index | (index + 1);
    }
}

long long query(int* tree, int index) {
    assert(tree);
    assert(index >= 0);

    long long sum = 0;
    while (index > 0) {
        sum += tree[index];
        index -= index & (-index);
    }
    return sum;
}

void init(int* tree, int n) {
    assert(tree);

    for (size_t i = 0; i <= n; i++) {
        tree[i] = 0;
    }
}

long long getSum(int* tree, int l, int r) {
    assert(tree);
    return query(tree, r) - query(tree, l - 1);
}
