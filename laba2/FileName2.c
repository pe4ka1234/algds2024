#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;


typedef struct {
    Node* root;
} SplayTree;


// Создание нового узла
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Память не выделена.");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// Инициализация дерева
SplayTree* createTree() {
    SplayTree* tree = (SplayTree*)malloc(sizeof(SplayTree));
    if (!tree) {
        printf("Память не выделена.");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    return tree;
}

// Освобождение узла
void freeNode(Node* node) {
    if (node) {
        freeNode(node->left);
        freeNode(node->right);
        free(node);
    }
}

// Освобождение дерева
void freeTree(SplayTree* tree) {
    freeNode(tree->root);
    free(tree);
}

// Операция поворота влево
void leftRotate(SplayTree* tree, Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
        tree->root = y;
    }
    else
    {
        if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}


// Операция поворота вправо
void rightRotate(SplayTree* tree, Node* x)
{
    Node* y = x->left;
    x->left = y->right;
    if (y->right)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent)
    {
        tree->root = y;
    }
    else
    {
        if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
    }
    y->right = x;
    x->parent = y;
}



void splay(SplayTree* tree, Node* x)
{
    while (x->parent) {
        Node* p = x->parent;  //отец
        Node* gp = p->parent; //дед
        if (!gp)
        {
            // Zig 
            if (x == p->left)
            {
                rightRotate(tree, p);
            }
            else
            {
                leftRotate(tree, p);
            }
        }
        else if (x == p->left && p == gp->left) {
            // Zig-zig 
            rightRotate(tree, gp);
            rightRotate(tree, p);
        }
        else
        {
            if (x == p->right && p == gp->right)
            {
                // Zig-zig 
                leftRotate(tree, gp);
                leftRotate(tree, p);
            }
            else
            {
                if (x == p->right && p == gp->left)
                {
                    // Zig-zag 
                    leftRotate(tree, p);
                    rightRotate(tree, gp);
                }
                else
                {
                    if (x == p->left && p == gp->right)
                    {
                        // Zig-zag 
                        rightRotate(tree, p);
                        leftRotate(tree, gp);
                    }
                }
            }
        }
    }
}


// Добавление элемента в дерево
void add(SplayTree* tree, int key) {
    Node* newNode = createNode(key);
    if (!tree->root) {
        tree->root = newNode;
    }
    else
    {
        Node* current = tree->root;
        Node* parent = NULL;
        while (current)
        {
            parent = current;
            if (key < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        newNode->parent = parent;
        if (key < parent->key)
        {
            parent->left = newNode;
        }
        else
        {
            parent->right = newNode;
        }
        splay(tree, newNode);
    }
}



Node* find(SplayTree* tree, int key)
{
    Node* current = tree->root;
    while (current)
    {
        if (key == current->key)
        {
            splay(tree, current);
            return current;
        }
        else
        {
            if (key < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
    }
    return NULL;
}


void myremove(SplayTree* tree, int key) {
    Node* node = find(tree, key);
    if (node) {
        splay(tree, node);
        Node* leftTree = node->left;
        Node* rightTree = node->right;
        free(node);
        if (leftTree) {
            leftTree->parent = NULL;
        }
        if (rightTree) {
            rightTree->parent = NULL;
        }
        if (!leftTree) {
            tree->root = rightTree;
        }
        else {
            Node* maxNode = leftTree;
            while (maxNode->right) {
                maxNode = maxNode->right;
            }
            splay(tree, maxNode);
            tree->root = maxNode;
            tree->root->right = rightTree;
            if (rightTree) {
                rightTree->parent = tree->root;
            }
        }
    }
}