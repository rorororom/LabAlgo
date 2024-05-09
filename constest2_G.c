#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int key;
    int prior;
    int size;
    struct node* left;
    struct node* right;
} node;

typedef struct node* Node;

#define CHECK_READ(res)               \
        if ((res) != 1) {             \
            printf("не считалось\n"); \
            return 1;                 \
        }

/**
 * @brief Генерация псевдослучайного числа.
 *
 * @return Сгенерированное случайное число.
 */
int GoodRand() {
    return rand() % 1000000007;
}

/**
 * @brief Обновление размера поддерева с корнем в узле.
 *
 * @param t Указатель на корень поддерева, для которого обновляется размер.
 * @return void
 */
void UpdateSize(Node node) {
    if (node) {
        node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
    }
}

/**
 * @brief Разделение дерева на два по ключу.
 *
 * @param t Указатель на корень исходного дерева.
 * @param key Ключ, по которому происходит разделение.
 * @param l Указатель на корень левого поддерева.
 * @param r Указатель на корень правого поддерева.
 * @return void
 */
void Split(Node node, int key, Node *left, Node *right) {
    if (!node) {
        *left = NULL;
        *right = NULL;
    }

    else if (key < node->key)
        Split(node->left, key, left, &node->left), *right = node;
    else
        Split(node->right, key, &node->right, right), *left = node;

    UpdateSize(node);
}

/**
 * @brief Вставка узла в дерево.
 *
 * @param t Указатель на указатель корня дерева.
 * @param it Указатель на новый узел для вставки.
 * @return void
 */
void Insert(Node* node, Node newNode) {
    if (!*node)
        *node = newNode;

    else if (newNode->prior > (*node)->prior)
        Split(*node, newNode->key, &newNode->left, &newNode->right), *node = newNode;
    else
        Insert(newNode->key < (*node)->key ? &(*node)->left : &(*node)->right, newNode);

    UpdateSize(*node);
}

/**
 * @brief Объединение двух деревьев.
 *
 * @param t Указатель на указатель корня результирующего дерева.
 * @param l Указатель на корень левого дерева.
 * @param r Указатель на корень правого дерева.
 * @return void
 */
void Merge(Node *node, Node left, Node right) {
    if (!left || !right) {
        *node = left ? left : right;
    } else if (left->prior > right->prior) {
        Merge(&left->right, left->right, right);
        *node = left;
    } else {
        Merge(&right->left, left, right->left);
        *node = right;
    }

    UpdateSize(*node);
}

/**
 * @brief Удаление узла с заданным ключом из дерева.
 *
 * @param t Указатель на указатель корня дерева.
 * @param key Ключ узла для удаления.
 * @return void
 */
void Erase(Node *node, int key) {
    if (!*node)
        return;

    if ((*node)->key == key) {
        Node temp = *node;
        Merge(node, (*node)->left, (*node)->right);
        free(temp);
    } else {
        Erase(key < (*node)->key ? &(*node)->left : &(*node)->right, key);
    }

    UpdateSize(*node);
}

/**
 * @brief Объединение двух деревьев.
 *
 * @param l Указатель на корень левого дерева.
 * @param r Указатель на корень правого дерева.
 * @return Указатель на корень результирующего дерева.
 */
Node Unite(Node left, Node right) {
    if (!left || !right)
        return left ? left : right;
    if (left->prior < right->prior) {
        Node temp = left;
        left = right;
        right = temp;
    }

    Node lt, rt;
    Split(right, left->key, &lt, &rt);
    left->left = Unite(left->left, lt);
    left->right = Unite(left->right, rt);

    UpdateSize(left);
    return left;
}

/**
 * @brief Проверка наличия узла с заданным ключом в дереве.
 *
 * @param t Указатель на корень дерева.
 * @param key Ключ узла для поиска.
 * @return true, если узел найден, иначе false.
 */
bool Exists(Node node, int key) {
    if (!node)
        return false;
    if (key == node->key)
        return true;
    else if (key < node->key)
        return Exists(node->left, key);
    else
        return Exists(node->right, key);
}

/**
 * @brief Поиск следующего по порядку узла относительно заданного ключа.
 *
 * @param t Указатель на корень дерева.
 * @param key Ключ, относительно которого производится поиск.
 * @return Значение ключа найденного узла или -1, если узел не найден.
 */
int Next(Node node, int key) {
    if (!node)
        return -1;
    if (key < node->key) {
        int result = Next(node->left, key);
        return result == -1 ? node->key : result;
    } else
        return Next(node->right, key);
}

/**
 * @brief Поиск предыдущего по порядку узла относительно заданного ключа.
 *
 * @param t Указатель на корень дерева.
 * @param key Ключ, относительно которого производится поиск.
 * @return Значение ключа найденного узла или -1, если узел не найден.
 */
int Prev(Node node, int key) {
    if (!node)
        return -1;
    if (key > node->key) {
        int result = Prev(node->right, key);
        return result == -1 ? node->key : result;
    } else
        return Prev(node->left, key);
}

/**
 * @brief Поиск k-го по порядку узла в дереве.
 *
 * @param root Указатель на корень дерева.
 * @param k Порядковый номер узла, который необходимо найти.
 * @return Указатель на найденный узел или NULL, если узел не найден.
 */
Node Kth(Node root, int k) {
    if (!root)
        return NULL;
    int leftSize = root->left ? root->left->size : 0;
    if (k == leftSize)
        return root;
    else if (k < leftSize)
        return Kth(root->left, k);
    else
        return Kth(root->right, k - leftSize - 1);
}

/**
 * @brief Вставка узла в дерево, если узел с указанным ключом еще не существует.
 *
 * @param root Указатель на указатель корня дерева.
 * @param key Ключ нового узла для вставки.
 * @return void
 */
void InsertIfNotExists(Node *root, int key) {
    if (!Exists(*root, key)) {
        Node newItem = (Node)malloc(sizeof(struct node));
        newItem->key = key;
        newItem->prior = GoodRand();
        newItem->size = 1;
        newItem->left = newItem->right = NULL;
        Insert(root, newItem);
    }
}

int main() {
    Node root = NULL;

    FILE* input = stdin;
    FILE* output = stdout;

    char operation[10];
    int x;

    while (fscanf(input, "%s", operation) > 0) {
        int res = fscanf(input, "%d", &x);
        CHECK_READ(res);

        if (strcmp(operation, "insert") == 0) {
            InsertIfNotExists(&root, x);

        } else if (strcmp(operation, "delete") == 0) {
            if (Exists(root, x)) {
                Erase(&root, x);
            }
        } else if (strcmp(operation, "exists") == 0) {
            fprintf(output, "%s\n", Exists(root, x) ? "true" : "false");

        } else if (strcmp(operation, "next") == 0) {
            int val_next = Next(root, x);

            if (val_next == -1)
                fprintf(output, "none\n");
            else
                fprintf(output, "%d\n", val_next);

        } else if (strcmp(operation, "prev") == 0) {
            int val_prev = Prev(root, x);

            if (val_prev == -1)
                fprintf(output, "none\n");
            else
                fprintf(output, "%d\n", val_prev);

        } else if (strcmp(operation, "kth") == 0) {
            Node kthNode = Kth(root, x);

            if (kthNode != NULL) {
                fprintf(output, "%d\n", kthNode->key);
            } else {
                fprintf(output, "none\n");
            }
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}

