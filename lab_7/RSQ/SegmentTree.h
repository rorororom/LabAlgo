#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

void build     (int* tree, int* arr, int node, int start, int end);
void update    (int* tree, int* arr, int node, int start, int end, int index, int value);
long long query(int* tree, int node, int start, int end, int l, int r);

#endif
