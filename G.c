#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int key;
    int prior;
    int size;
    struct node* l;
    struct node* r;
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
void UpdateSize(Node t) {
    if (t) {
        t->size = 1 + (t->l ? t->l->size : 0) + (t->r ? t->r->size : 0);
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
void Split(Node t, int key, Node *l, Node *r) {
    if (!t) {
        *l = NULL;
        *r = NULL;
    }

    else if (key < t->key)
        Split(t->l, key, l, &t->l), *r = t;
    else
        Split(t->r, key, &t->r, r), *l = t;

    UpdateSize(t);
}

/**
 * @brief Вставка узла в дерево.
 *
 * @param t Указатель на указатель корня дерева.
 * @param it Указатель на новый узел для вставки.
 * @return void
 */
void Insert(Node *t, Node it) {
    if (!*t)
        *t = it;

    else if (it->prior > (*t)->prior)
        Split(*t, it->key, &it->l, &it->r), *t = it;
    else
        Insert(it->key < (*t)->key ? &(*t)->l : &(*t)->r, it);

    UpdateSize(*t);
}

/**
 * @brief Объединение двух деревьев.
 *
 * @param t Указатель на указатель корня результирующего дерева.
 * @param l Указатель на корень левого дерева.
 * @param r Указатель на корень правого дерева.
 * @return void
 */
void Merge(Node *t, Node l, Node r) {
    if (!l || !r) {
        *t = l ? l : r;
    } else if (l->prior > r->prior) {
        Merge(&l->r, l->r, r);
        *t = l;
    } else {
        Merge(&r->l, l, r->l);
        *t = r;
    }

    UpdateSize(*t);
}

/**
 * @brief Удаление узла с заданным ключом из дерева.
 *
 * @param t Указатель на указатель корня дерева.
 * @param key Ключ узла для удаления.
 * @return void
 */
void Erase(Node *t, int key) {
    if (!*t)
        return;

    if ((*t)->key == key) {
        Node temp = *t;
        Merge(t, (*t)->l, (*t)->r);
        free(temp);
    } else {
        Erase(key < (*t)->key ? &(*t)->l : &(*t)->r, key);
    }

    UpdateSize(*t);
}

/**
 * @brief Объединение двух деревьев.
 *
 * @param l Указатель на корень левого дерева.
 * @param r Указатель на корень правого дерева.
 * @return Указатель на корень результирующего дерева.
 */
Node Unite(Node l, Node r) {
    if (!l || !r)
        return l ? l : r;
    if (l->prior < r->prior) {
        Node temp = l;
        l = r;
        r = temp;
    }

    Node lt, rt;
    Split(r, l->key, &lt, &rt);
    l->l = Unite(l->l, lt);
    l->r = Unite(l->r, rt);

    UpdateSize(l);
    return l;
}

/**
 * @brief Проверка наличия узла с заданным ключом в дереве.
 *
 * @param t Указатель на корень дерева.
 * @param key Ключ узла для поиска.
 * @return true, если узел найден, иначе false.
 */
bool Exists(Node t, int key) {
    if (!t)
        return false;
    if (key == t->key)
        return true;
    else if (key < t->key)
        return Exists(t->l, key);
    else
        return Exists(t->r, key);
}

/**
 * @brief Поиск следующего по порядку узла относительно заданного ключа.
 *
 * @param t Указатель на корень дерева.
 * @param key Ключ, относительно которого производится поиск.
 * @return Значение ключа найденного узла или -1, если узел не найден.
 */
int Next(Node t, int key) {
    if (!t)
        return -1;
    if (key < t->key) {
        int result = Next(t->l, key);
        return result == -1 ? t->key : result;
    } else
        return Next(t->r, key);
}

/**
 * @brief Поиск предыдущего по порядку узла относительно заданного ключа.
 *
 * @param t Указатель на корень дерева.
 * @param key Ключ, относительно которого производится поиск.
 * @return Значение ключа найденного узла или -1, если узел не найден.
 */
int Prev(Node t, int key) {
    if (!t)
        return -1;
    if (key > t->key) {
        int result = Prev(t->r, key);
        return result == -1 ? t->key : result;
    } else
        return Prev(t->l, key);
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
    int leftSize = root->l ? root->l->size : 0;
    if (k == leftSize)
        return root;
    else if (k < leftSize)
        return Kth(root->l, k);
    else
        return Kth(root->r, k - leftSize - 1);
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
        newItem->l = newItem->r = NULL;
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

