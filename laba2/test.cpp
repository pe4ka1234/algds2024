#include <gtest/gtest.h>
#include "FileName2.c"  

// ��������������� ������� ��� ������ ������
void traverseTree(Node* node, std::vector<int>& keys) {
    if (!node) {
        return;
    }
    traverseTree(node->left, keys);  // ����� �����
    keys.push_back(node->key);       // ���������� ����� ����
    traverseTree(node->right, keys); // ����� ������
}

//���� ��� ������� add
TEST(SplayTreeTest, AddFunctionTest) {
    // ������� ������
    SplayTree* tree = createTree();

    // ��������� ��������� ���������
    add(tree, 10);
    add(tree, 5);
    add(tree, 15);
    EXPECT_EQ(15, tree->root->key);
    EXPECT_EQ(10, tree->root->left->key);
    EXPECT_EQ(5,  tree->root->left->left->key);
    // ����������� ������ ������
    freeTree(tree);
}

// ���� ��� ������� myremove
TEST(SplayTreeTest, RemoveFunctionTest) {
    // ������� ������
    SplayTree* tree = createTree();
    // ��������� ����� 10 � 5
    add(tree, 10);
    add(tree, 5);
    add(tree, 15);

    // ������� ���� 10 � ����������, ��� �� ������
    myremove(tree, 10);
    EXPECT_EQ(5, tree->root->key);
    EXPECT_EQ(15, tree->root->right->key);
    EXPECT_EQ(NULL, tree->root->left);
    // ����������� ������
    freeTree(tree);
}

// ���� ��� ������� find
TEST(SplayTreeTest, FindFunctionTest) {
    // ������� ������
    SplayTree* tree = createTree();

    // ��������� ��������� ���������
    add(tree, 10);
    add(tree, 5);
    add(tree, 15);

    // ��������� ������������� ���������
    ASSERT_TRUE(find(tree, 10) != NULL);
    ASSERT_TRUE(find(tree, 5) != NULL);
    ASSERT_TRUE(find(tree, 15) != NULL);

    // ���������, ��� ��������, ������� ���, ���������� NULL
    ASSERT_TRUE(find(tree, 20) == NULL);
    ASSERT_TRUE(find(tree, 0) == NULL);

    // ����������� ������
    freeTree(tree);
}


TEST(SplayTreeTest, LeftRotateFunctionTest) {
    // ������� ������
    SplayTree* tree = createTree();
    Node* root = createNode(10);
    Node* rightChild = createNode(15);
    root->right = rightChild;
    rightChild->parent = root;
    tree->root = root;

    // ��������� ����� �������
    leftRotate(tree, root);

    // ���������, ��� ������ ���� ��������� �����������
    EXPECT_EQ(tree->root, rightChild);  // ����� ������ ������ ���� rightChild
    EXPECT_EQ(rightChild->left, root);  // ������ ������ ����� ����� �������� rightChild
    EXPECT_EQ(root->parent, rightChild);  // ����� �������� root ������ ���� rightChild

    // ����������� ������ ������
    freeTree(tree);
}


TEST(SplayTreeTest, RightRotateFunctionTest) {
    // ������� ������
    SplayTree* tree = createTree();
    Node* root = createNode(10);
    Node* leftChild = createNode(5);
    root->left = leftChild;
    leftChild->parent = root;
    tree->root = root;

    // ��������� ������ �������
    rightRotate(tree, root);

    // ���������, ��� ������ ���� ��������� �����������
    EXPECT_EQ(tree->root, leftChild);  // ����� ������ ������ ���� leftChild
    EXPECT_EQ(leftChild->right, root);  // ������ ������ ����� ������ �������� leftChild
    EXPECT_EQ(root->parent, leftChild);  // ����� �������� root ������ ���� leftChild

    // ����������� ������ ������
    freeTree(tree);
}


TEST(SplayTreeTest, SplayFunctionTest) {
    // ������� ������
    SplayTree* tree = createTree();
    add(tree, 10);
    add(tree, 5);
    add(tree, 15);
    add(tree, 2);
    add(tree, 7);

    // �������� ���� � ������ 7
    Node* node7 = find(tree, 7);

    // ��������� ���������� ���� � �����
    splay(tree, node7);

    // ���������, ��� ���� � ������ 7 ���� ������ ������
    EXPECT_EQ(tree->root, node7);

    // ����������� ������ ������
    freeTree(tree);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
