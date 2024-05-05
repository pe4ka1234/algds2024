#include <gtest/gtest.h>
#include "FileName2.c"  

// Вспомогательная функция для обхода дерева
void traverseTree(Node* node, std::vector<int>& keys) {
    if (!node) {
        return;
    }
    traverseTree(node->left, keys);  // Обход слева
    keys.push_back(node->key);       // Добавление ключа узла
    traverseTree(node->right, keys); // Обход справа
}

//Тест для функции add
TEST(SplayTreeTest, AddFunctionTest) {
    // Создаем дерево
    SplayTree* tree = createTree();

    // Добавляем несколько элементов
    add(tree, 10);
    add(tree, 5);
    add(tree, 15);
    EXPECT_EQ(15, tree->root->key);
    EXPECT_EQ(10, tree->root->left->key);
    EXPECT_EQ(5,  tree->root->left->left->key);
    // Освобождаем память дерева
    freeTree(tree);
}

// Тест для функции myremove
TEST(SplayTreeTest, RemoveFunctionTest) {
    // Создаем дерево
    SplayTree* tree = createTree();
    // Добавляем ключи 10 и 5
    add(tree, 10);
    add(tree, 5);
    add(tree, 15);

    // Удаляем ключ 10 и убеждаемся, что он удален
    myremove(tree, 10);
    EXPECT_EQ(5, tree->root->key);
    EXPECT_EQ(15, tree->root->right->key);
    EXPECT_EQ(NULL, tree->root->left);
    // Освобождаем память
    freeTree(tree);
}

// Тест для функции find
TEST(SplayTreeTest, FindFunctionTest) {
    // Создаем дерево
    SplayTree* tree = createTree();

    // Добавляем несколько элементов
    add(tree, 10);
    add(tree, 5);
    add(tree, 15);

    // Проверяем существование элементов
    ASSERT_TRUE(find(tree, 10) != NULL);
    ASSERT_TRUE(find(tree, 5) != NULL);
    ASSERT_TRUE(find(tree, 15) != NULL);

    // Проверяем, что элементы, которых нет, возвращают NULL
    ASSERT_TRUE(find(tree, 20) == NULL);
    ASSERT_TRUE(find(tree, 0) == NULL);

    // Освобождаем память
    freeTree(tree);
}


TEST(SplayTreeTest, LeftRotateFunctionTest) {
    // Создаем дерево
    SplayTree* tree = createTree();
    Node* root = createNode(10);
    Node* rightChild = createNode(15);
    root->right = rightChild;
    rightChild->parent = root;
    tree->root = root;

    // Выполняем левый поворот
    leftRotate(tree, root);

    // Проверяем, что дерево было правильно перестроено
    EXPECT_EQ(tree->root, rightChild);  // Новый корень должен быть rightChild
    EXPECT_EQ(rightChild->left, root);  // Корень должен стать левым потомком rightChild
    EXPECT_EQ(root->parent, rightChild);  // Новый родитель root должен быть rightChild

    // Освобождаем память дерева
    freeTree(tree);
}


TEST(SplayTreeTest, RightRotateFunctionTest) {
    // Создаем дерево
    SplayTree* tree = createTree();
    Node* root = createNode(10);
    Node* leftChild = createNode(5);
    root->left = leftChild;
    leftChild->parent = root;
    tree->root = root;

    // Выполняем правый поворот
    rightRotate(tree, root);

    // Проверяем, что дерево было правильно перестроено
    EXPECT_EQ(tree->root, leftChild);  // Новый корень должен быть leftChild
    EXPECT_EQ(leftChild->right, root);  // Корень должен стать правым потомком leftChild
    EXPECT_EQ(root->parent, leftChild);  // Новый родитель root должен быть leftChild

    // Освобождаем память дерева
    freeTree(tree);
}


TEST(SplayTreeTest, SplayFunctionTest) {
    // Создаем дерево
    SplayTree* tree = createTree();
    add(tree, 10);
    add(tree, 5);
    add(tree, 15);
    add(tree, 2);
    add(tree, 7);

    // Получаем узел с ключом 7
    Node* node7 = find(tree, 7);

    // Выполняем скашивание узла к корню
    splay(tree, node7);

    // Проверяем, что узел с ключом 7 стал корнем дерева
    EXPECT_EQ(tree->root, node7);

    // Освобождаем память дерева
    freeTree(tree);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
