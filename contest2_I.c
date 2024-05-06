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

    struct node* header = NewNode();
    struct node* leftMax = header;
    struct node* rightMin = header;
    struct node* leftTail = header;
    struct node* rightTail = header;

    while (1) {
        int cmp = СustomStrcmp(root->data, key);

        if (cmp == 0)
            break;

        if (cmp > 0) {
            if (root->left == NULL)
                break;

            if (СustomStrcmp(root->left->data, key) > 0) {
                root = RightRotate(root);
                if (root->left == NULL)
                    break;
            }

            rightTail->left = root;
            rightTail = root;
            root = root->left;
        } else {
            if (root->right == NULL)
                break;

            if (СustomStrcmp(root->right->data, key) < 0) {
                root = LeftRotate(root);
                if (root->right == NULL)
                    break;
            }

            leftTail->right = root;
            leftTail = root;
            root = root->right;
        }
    }

    leftTail->right = root->left;
    rightTail->left = root->right;
    root->left = header->right;
    root->right = header->left;
    free(header);

    return root;
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
    while (root != NULL) {
        struct node* temp = root;

        if (root->left != NULL) {
            root = root->left;
            temp->left = NULL;
        } else {
            root = root->right;
            temp->right = NULL;
        }

        free(temp->name);
        free(temp->data);
        free(temp);
    }
}

#define MAX_LENGTH 1000

int main() {
    FILE* input  = stdin;
    FILE* output = stdout;

    int N = 0;
    int res = fscanf(input, "%d", &N);
    if (res != 1) {
        fprintf(output, "не считалось\n");
        return 1;
    }

    char* callSign = (char*)calloc(MAX_LENGTH, sizeof(char));
    char* name     = (char*)calloc(MAX_LENGTH, sizeof(char));

    struct node* root = NULL;

    for (size_t i = 0; i < N; i++) {
        res = fscanf(input, "%999s %999s", callSign, name);  // 999 ---> без учета '\0'
        if (res != 2) {
            fprintf(output, "не считалось\n");
            return 1;
        }

        root = Insert(root, callSign, name, 0);
        root = Insert(root, name, callSign, 1);
    }

    res = fscanf(input, "%d", &N);
    if (res != 1) {
        fprintf(output, "не считалось\n");
        return 1;
    }

    for (size_t i = 0; i < N; i++) {
        fscanf(input, "%999s", callSign);

        Search(&root, callSign);
        fprintf(output, "%s\n", root->name);
    }

    Free(root);

    return 0;
}
