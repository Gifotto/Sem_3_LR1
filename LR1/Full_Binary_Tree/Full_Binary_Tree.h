#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value);
bool findValue(Node* root, int value);

bool inFullTreeRec(Node*& root, Node* newNode1, Node* newNode2);
void inFullTree(Node*& root, int value1, int value2);

int height(Node* root);
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);
void printLevel(Node* root, int level);
void levelOrder(Node* root);
void printTree(Node* root, int space = 0, int indent = 4);

bool isFullTree(Node* root);
void clearTree(Node*& root);

void saveToFile(Node* root, ofstream& file);
Node* loadFromFile(ifstream& file);