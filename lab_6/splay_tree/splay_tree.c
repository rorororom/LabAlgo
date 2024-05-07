#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

struct node {
    int key;
    struct node* left;
    struct node* right;
};

void* calloc_with_check(size_t num, size_t size) {
    void* ptr = calloc(num, size);
    assert(ptr != NULL);
    return ptr;
}

struct node* NewNode(int key) {
    struct node* new_node = (struct node*)calloc_with_check(1, sizeof(struct node));
    new_node->left = new_node->right = NULL;
    new_node->key = key;
    return new_node;
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

struct node* Splay(struct node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    struct node* header = NewNode(key);
    struct node* leftMax = header;
    struct node* rightMin = header;
    struct node* leftTail = header;
    struct node* rightTail = header;

    while (1) {
        if (root->key == key)
            break;

        if (root->key > key) {
            if (root->left == NULL)
                break;

            if (root->left->key > key) {
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

            if (root->right->key < key) {
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
    newNode->right = root;
    newNode->left = root->left;
    root->left = NULL;
    return newNode;
}

struct node* InsertLeft(struct node* root, struct node* newNode) {
    newNode->left = root;
    newNode->right = root->right;
    root->right = NULL;
    return newNode;
}

struct node* Insert(struct node* root, int key) {
    if (root == NULL)
        return NewNode(key);

    root = Splay(root, key);

    if (root->key == key)
        return root;

    struct node* newNode = NewNode(key);

    if (root->key < key) {
        return InsertLeft(root, newNode);
    } else {
        return InsertRight(root, newNode);
    }
}

struct node* Delete(struct node* root, int key) {
    if (root == NULL)
        return NULL;

    root = Splay(root, key);

    if (root->key != key)
        return root;

    if (root->left == NULL) {
        struct node* newRoot = root->right;
        free(root);
        return newRoot;
    }

    if (root->right == NULL) {
        struct node* newRoot = root->left;
        free(root);
        return newRoot;
    }

    struct node* maxLeft = root->left;
    while (maxLeft->right != NULL)
        maxLeft = maxLeft->right;

    root->left = Splay(root->left, maxLeft->key);

    root->left->right = root->right;

    struct node* newRoot = root->left;
    free(root);
    return newRoot;
}


void Search(struct node** root, int key) {
    assert(root);

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
        free(temp);
    }
}
void GenerateGraphImage();
void GenerateImage(struct node* heap);
static void PrintNodeDump(FILE* dotFile, struct node* root, const char* fillColor);
const int MAX_LEN = 256;

void GenerateGraphImage()
{
    char command[MAX_LEN] = "";
    sprintf(command, "dot -Tpng /Users/aleksandr/Desktop/TIM3/LabAlgo/lab_6/testing/treap.dot -o /Users/aleksandr/Desktop/TIM3/LabAlgo/lab_6/testing/file.png");
    system(command);
}
void PrintTree(FILE* dotFile, struct node* root);

void GenerateImage(struct node* root)
{
    FILE* dotFile = fopen("treap.dot", "w");

    if (dotFile)
    {
        fprintf(dotFile, "digraph treap {\n");
        fprintf(dotFile, "\tnode [shape=circle, style=filled, color=\"#4169e1\", fillcolor=\"#afeeee\", fontsize=12];\n");

        PrintTree(dotFile, root);

        fprintf(dotFile, "}\n");
        fclose(dotFile);
    }
    else
    {
        fprintf(stderr, "Ошибка при открытии файла treap.dot\n");
    }
}


void PrintTree(FILE* dotFile, struct node* root)
{
    if (root)
    {
        fprintf(dotFile, "\t%d[label=\"%d \"];\n", root->key, root->key);

        if (root->left)
        {
            fprintf(dotFile, "\t%d -> %d [color=\"#228b22\"];\n", root->key, root->left->key);
            PrintTree(dotFile, root->left);
        }

        if (root->right)
        {
            fprintf(dotFile, "\t%d -> %d [color=\"#8b0000\"];\n", root->key, root->right->key);
            PrintTree(dotFile, root->right);
        }
    }
}
