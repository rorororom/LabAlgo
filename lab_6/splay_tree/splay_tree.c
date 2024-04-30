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

    if (root->key > key) {
        if (root->left == NULL) return root;
        if (root->left->key > key) {
            root->left->left = Splay(root->left->left, key);
            root = RightRotate(root);
        }
        else if (root->left->key < key)  {
            root->left->right = Splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = LeftRotate(root->left);
        }
        return (root->left == NULL)? root: RightRotate(root);
    }
    else {
        if (root->right == NULL) return root;
        if (root->right->key > key) {
            root->right->left = Splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = RightRotate(root->right);
        }
        else if (root->right->key < key) {
            root->right->right = Splay(root->right->right, key);
            root = LeftRotate(root);
        }
        return (root->right == NULL)? root: LeftRotate(root);
    }
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
        return root; // Ключ не найден, возвращаем текущий корень

    // Если у корня нет левого поддерева, просто возвращаем правое поддерево
    if (root->left == NULL) {
        struct node* newRoot = root->right;
        free(root);
        return newRoot;
    }

    // Если у корня нет правого поддерева, просто возвращаем левое поддерево
    if (root->right == NULL) {
        struct node* newRoot = root->left;
        free(root);
        return newRoot;
    }

    // Если у корня есть и левое, и правое поддерево
    // Находим максимальный элемент в левом поддереве и делаем его новым корнем
    struct node* maxLeft = root->left;
    while (maxLeft->right != NULL)
        maxLeft = maxLeft->right;

    // Устанавливаем максимальный элемент в левом поддереве в качестве корня
    root->left = Splay(root->left, maxLeft->key);

    // Присоединяем правое поддерево к новому корню
    root->left->right = root->right;

    // Освобождаем старый корень и возвращаем новый
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
    if (root == NULL)
        return;

    Free(root->left);
    Free(root->right);
    free(root);
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
        fclose(dotFile); // Закрываем файл после записи
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

// #define MAX_LENGTH 1000
//
// int main() {
//     int N = 0;
//     scanf("%d", &N);
//
//     int input;
//
//     struct node* root = NULL;
//
//     for (int i = 0; i < N; i++) {
//         scanf("%d", &input);
//
//         root = Insert(root, input);
//     }
//
//     scanf("%d", &N);
//
//     for (int i = 0; i < N; i++) {
//         scanf("%d", &input);
//
//         Search(&root, input);
//         printf("%d\n", root->key);
//     }
//
//     Free(root);
//
//     return 0;
// }

