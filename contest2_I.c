#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    char* data;
    char* name;
    struct node* left;
    struct node* right;
};

char* strdup_with_check(const char* str) {
    assert(str != NULL);

    char* new_str = strdup(str);
    assert(new_str != NULL);

    return new_str;
}

void* calloc_with_check(size_t num, size_t size) {
    void* ptr = calloc(num, size);
    assert(ptr != NULL);

    return ptr;
}

struct node* NewNode() {
    struct node* new_node = (struct node*)calloc_with_check(1, sizeof(struct node));
    new_node->left = new_node->right = NULL;
    return new_node;
}

struct node* New(char *data, char* name, int flag) {
    assert(data != NULL);
    assert(name != NULL);

    struct node* node = NewNode();

    node->data = strdup_with_check(data);
    node->name = strdup_with_check(name);

    return node;
}


struct node* RightRotate(struct node *n) {
    assert(n);

    struct node *nn = n->left;
    n->left = nn->right;
    nn->right = n;
    return nn;
}

struct node* LeftRotate(struct node *n) {
    assert(n);

    struct node *nn = n->right;
    n->right = nn->left;
    nn->left = n;
    return nn;
}

int СustomStrcmp(const char* str1, const char* str2) {
    assert(str1);
    assert(str2);

    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }

    return (unsigned char) *str1 - (unsigned char) *str2;
}

struct node* Splay(struct node* root, char* key) {
    assert(key);

    if (root == NULL || СustomStrcmp(root->data, key) == 0)
        return root;

    if (СustomStrcmp(root->data, key) > 0) {
        if (root->left == NULL) return root;

        if (СustomStrcmp(root->left->data, key) > 0) {
            root->left->left = Splay(root->left->left, key);

            root = RightRotate(root);
        }
        else if (СustomStrcmp(root->left->data, key) < 0)  {
            root->left->right = Splay(root->left->right, key);

            if (root->left->right != NULL)
                root->left = LeftRotate(root->left);
        }

        return (root->left == NULL)? root: RightRotate(root);
    }
    else {
        if (root->right == NULL) return root;

        if (СustomStrcmp(root->right->data, key) > 0) {
            root->right->left = Splay(root->right->left, key);

            if (root->right->left != NULL)
                root->right = RightRotate(root->right);
        }
        else if (СustomStrcmp(root->right->data, key) < 0) {
            root->right->right = Splay(root->right->right, key);
            root = LeftRotate(root);
        }

        return (root->right == NULL)? root: LeftRotate(root);
    }
}

struct node* InsertRight(struct node* root, struct node* newNode) {
    assert(root);
    assert(newNode);

    newNode->right = root;
    newNode->left = root->left;
    root->left = NULL;
    return newNode;
}

struct node* InsertLeft(struct node* root, struct node* newNode) {
    assert(root);
    assert(newNode);

    newNode->left = root;
    newNode->right = root->right;
    root->right = NULL;
    return newNode;
}

struct node* Insert(struct node* root, char* key, char* name, int flag) {
    assert(key);
    assert(name);

    if (root == NULL)
        return New(key, name, flag);

    root = Splay(root, key);

    if (СustomStrcmp(root->data, key) == 0)
        return root;

    struct node* newNode = New(key, name, flag);

    if (СustomStrcmp(root->data, key) < 0) {
        return InsertLeft(root, newNode);
    } else {
        return InsertRight(root, newNode);
    }
}

void Search(struct node** root, char *key) {
    assert(root);
    assert(key);

    if (*root == NULL)
        return;

    *root = Splay(*root, key);
}

void Free(struct node* root) {
    if (root == NULL)
        return;

    Free(root->left);
    Free(root->right);

    free(root->name);
    free(root->data);
    free(root);
}

#define MAX_LENGTH 1000

int main() {
    FILE* input  = stdin;
    FILE* output = stdout;

    int N = 0;
    int res = fscanf(stdin, "%d", &N);
    if (res != 1) {
        fprintf(stdout, "не считалось\n");
        return 1;
    }

    char input1[MAX_LENGTH];
    char input2[MAX_LENGTH];

    struct node* root = NULL;

    for (int i = 0; i < N; i++) {
        res = fscanf(stdin, "%s %s", input1, input1);
        if (res != 2) {
            fprintf(stdout, "не считалось\n");
            return 1;
        }

        root = Insert(root, input1, input2, 0);
        root = Insert(root, input2, input1, 1);
    }

    res = sscanf(stdin, "%d", &N);
    if (res != 1) {
        fprintf(stdout, "не считалось\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fscanf(stdin, "%s", input1);

        Search(&root, input1);
        fprintf(stdout, "%s\n", root->name);
    }

    Free(root);

    return 0;
}
