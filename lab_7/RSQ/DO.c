#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void build(int* tree, int* arr, int node, int start, int end) {
    assert(tree);
    assert(arr);

    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(tree, arr, 2 * node, start, mid);
        build(tree, arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void update(int* tree, int* arr, int node, int start, int end, int index, int value) {
    assert(tree);
    assert(arr);

    if (start == end) {
        arr[index] = value;
        tree[node] = value;
    } else {
        int mid = (start + end) / 2;
        if (start <= index && index <= mid) {
            update(tree, arr, 2 * node, start, mid, index, value);
        } else {
            update(tree, arr, 2 * node + 1, mid + 1, end, index, value);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}


long long query(int* tree, int node, int start, int end, int l, int r) {
    assert(tree);
    if (r < start || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int sum_left = query(tree, 2 * node, start, mid, l, r);
    int sum_right = query(tree, 2 * node + 1, mid + 1, end, l, r);
    return sum_left + sum_right;
}
