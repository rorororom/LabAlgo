#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dekartovo_tree.h"

int GoodRand() {
    return rand() % 1000000007;
}

void update_size(pnode t) {
    if (t)
        t->size = 1 + (t->l ? t->l->size : 0) + (t->r ? t->r->size : 0);
}

void split(pnode t, int key, pnode *l, pnode *r) {
    if (!t)
        *l = *r = NULL;
    else if (key < t->key)
        split(t->l, key, l, &t->l), *r = t;
    else
        split(t->r, key, &t->r, r), *l = t;
    update_size(t);
}

void insert(pnode *t, pnode it) {
    if (!*t)
        *t = it;
    else if (it->prior > (*t)->prior)
        split(*t, it->key, &it->l, &it->r), *t = it;
    else
        insert(it->key < (*t)->key ? &(*t)->l : &(*t)->r, it);
    update_size(*t);
}

void merge(pnode *t, pnode l, pnode r) {
    if (!l || !r)
        *t = l ? l : r;
    else if (l->prior > r->prior)
        merge(&l->r, l->r, r), *t = l;
    else
        merge(&r->l, l, r->l), *t = r;
    update_size(*t);
}

void erase(pnode *t, int key) {
    if (!*t)
        return;
    if ((*t)->key == key) {
        pnode temp = *t;
        merge(t, (*t)->l, (*t)->r);
        free(temp);
    } else {
        erase(key < (*t)->key ? &(*t)->l : &(*t)->r, key);
    }
    update_size(*t);
}

pnode unite(pnode l, pnode r) {
    if (!l || !r)
        return l ? l : r;
    if (l->prior < r->prior) {
        pnode temp = l;
        l = r;
        r = temp;
    }
    pnode lt, rt;
    split(r, l->key, &lt, &rt);
    l->l = unite(l->l, lt);
    l->r = unite(l->r, rt);
    update_size(l);
    return l;
}

bool exists(pnode t, int key) {
    if (!t)
        return false;
    if (key == t->key)
        return true;
    else if (key < t->key)
        return exists(t->l, key);
    else
        return exists(t->r, key);
}


// int main() {
//     pnode root = NULL;
//
//     char operation[10];
//     int x;
//     while (scanf("%s", operation) > 0) {
//         scanf("%d", &x);
//         if (strcmp(operation, "insert") == 0) {
//             if (!exists(root, x)) {
//                 pnode newnode = (pnode)malloc(sizeof(struct node));
//                 newnode->key = x;
//                 newnode->prior = GoodRand();
//                 newnode->size = 1;
//                 newnode->l = newnode->r = NULL;
//                 insert(&root, newnode);
//             }
//         } else if (strcmp(operation, "delete") == 0) {
//             if (exists(root, x)) {
//                 erase(&root, x);
//             }
//         } else if (strcmp(operation, "exists") == 0) {
//             printf("%s\n", exists(root, x) ? "true" : "false");
//         }
//     }
//
//     return 0;
// }
