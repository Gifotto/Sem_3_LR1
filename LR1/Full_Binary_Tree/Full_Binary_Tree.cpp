#include <iostream>
#include <fstream>
#include <sstream>
#include "Full_Binary_Tree.h"

Node* createNode(int value) {
    Node* node = new Node;
    node->data = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

//поиск
bool findValue(Node* root, int value) {
    if (!root) return false;
    if (root->data == value) return true;
    return findValue(root->left, value) || findValue(root->right, value);
}

// рекурсивная функция для вставки пары узлов
bool inFullTreeRec(Node*& root, Node* newNode1, Node* newNode2) {
    if (!root) return false;

    // если у узла нет детей — сюда можно вставить
    if (!root->left && !root->right) {
        root->left = newNode1;
        root->right = newNode2;
        return true;
    }

    string vib;
    cout << "LEFT or RIGHT";
    cin >> vib;
    if (vib == "LEFT") {
        // пробуем вставить в левое поддерево
        if (root->left && inFullTreeRec(root->left, newNode1, newNode2))
            return true;
    }

    else {
        // пробуем вставить в правое поддерево
        if (root->right && inFullTreeRec(root->right, newNode1, newNode2))
            return true;
    }

    return false;
}

void inFullTree(Node*& root, int value1, int value2) {
    Node* newNode1 = createNode(value1);
    Node* newNode2 = createNode(value2);

    if (!root) {
        // если дерева нет — создаём корень и добавляем детей
        root = createNode(-1); // можно поменять на нужное значение корня
        root->left = newNode1;
        root->right = newNode2;
        return;
    }

    inFullTreeRec(root, newNode1, newNode2);
}

// функция для вычисления высоты дерева
int height(Node* root) {
    if (!root) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return max(lh, rh) + 1;
}

// Обходы дерева
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// обход дерева в ширину
// вывод всех узлов на заданном уровне
void printLevel(Node* root, int level) {
    if (!root) return;
    if (level == 1)
        cout << root->data << " ";
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void levelOrder(Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++)
        printLevel(root, i);
}

// Вывод дерева "красиво" с отступами
void printTree(Node* root, int space, int indent) {
    if (!root) return;

    // Сначала выводим правое поддерево
    printTree(root->right, space + indent, indent);

    // Печатаем текущий узел с отступом
    for (int i = 0; i < space; i++) cout << " ";
    cout << root->data << "\n";

    // Затем левое поддерево
    printTree(root->left, space + indent, indent);
}

// Проверка полноты дерева (Full Binary Tree)
bool isFullTree(Node* root) {
    if (!root) return true;

    // Если оба потомка отсутствуют — узел корректен
    if (!root->left && !root->right)
        return true;

    // Если есть оба — проверяем дальше рекурсивно
    if (root->left && root->right)
        return isFullTree(root->left) && isFullTree(root->right);

    // Если только один потомок — дерево неполное
    return false;
}

// Очистка памяти
void clearTree(Node*& root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr;
}

// Сохранение дерева в файл (обход в прямом порядке)
void saveToFile(Node* root, ofstream& file) {
    if (!root) {
        file << "# "; // маркер пустого узла
        return;
    }
    file << root->data << " ";
    saveToFile(root->left, file);
    saveToFile(root->right, file);
}

// Загрузка дерева из файла
Node* loadFromFile(ifstream& file) {
    string val;
    if (!(file >> val)) return nullptr;
    if (val == "#") return nullptr;

    Node* node = createNode(stoi(val));
    node->left = loadFromFile(file);
    node->right = loadFromFile(file);
    return node;
}