#include <iostream>
#include <fstream>
#include <sstream>
#include "Full_Binary_Tree.h"

using namespace std;

// --- Обработка одной команды ---
void processCommand(Node*& root, const string& line, const string& filename) {
    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "TROOT") {
        int val;
        if (!(ss >> val)) {
            cout << "Введите значение: TROOT <val>\n";
            return;
        }
        if (root) {
            cout << "Корень уже существует.\n";
            return;
        }
        root = createNode(val);
        cout << "Создан корень " << val << endl;
    }

    else if (cmd == "TINSERT") {
        int a, b;
        if (!(ss >> a >> b)) {
            cout << "Введите два значения: TINSERT <a> <b>\n";
            return;
        }
        inFullTree(root, a, b);
        cout << "Добавлены узлы " << a << " и " << b << endl;
    }

    else if (cmd == "NICEPRINT") {
        if (!root) cout << "Дерево пусто\n";
        else printTree(root);
    }

    else if (cmd == "PRINT") {
        string type;
        ss >> type;
        if (!root) {
            cout << "Дерево пусто\n";
            return;
        }
        if (type == "IN") inorder(root); // Центрированный обход или симметричный -- Левый → Корень → Правый
        else if (type == "PRE") preorder(root); // Прямой обход -- Корень → Левый → Правый
        else if (type == "POST") postorder(root); // Обратный обход -- Левый → Правый → Корень
        else if (type == "LEVEL") levelOrder(root); // в ширину
        else cout << "Неизвестный тип обхода. Используйте: IN, PRE, POST, LEVEL\n";
        cout << endl;
    }

    else if (cmd == "ISFULL") {
        cout << (isFullTree(root) ? "TRUE" : "FALSE") << endl;
    }

    else if (cmd == "SEARCH") {
        int val;
        if (!(ss >> val)) {
            cout << "Введите значение: SEARCH <val>\n";
            return;
        }
        cout << (findValue(root, val) ? "TRUE" : "FALSE") << endl;
    }

    else if (cmd == "CLEAR") {
        clearTree(root);
        cout << "Дерево очищено.\n";
    }

    else if (cmd == "EXIT") {
        cout << "Выход из программы.\n";
        exit(0);
    }

    else {
        cout << "Неизвестная команда: " << cmd << endl;
    }

    // --- Сохраняем после каждой операции ---
    ofstream fout(filename);
    if (fout.is_open()) {
        saveToFile(root, fout);
        fout.close();
    }
}

// --- Точка входа ---
int main() {
    setlocale(0, "");
    Node* root = nullptr;
    string filename = "tree.data";

    // Загрузка из файла
    ifstream fin(filename);
    if (fin.is_open()) {
        root = loadFromFile(fin);
        fin.close();
        cout << "Файл " << filename << " загружен.\n";
    }
    else {
        ofstream fout(filename);
        fout << "# ";
        fout.close();
        cout << "Создан новый файл " << filename << ".\n";
    }

    cout << "============= Меню ==============\n"
        << " TROOT <val>       - создать корень\n"
        << " TINSERT <a> <b>   - добавить пару узлов\n"
        << " NICEPRINT             - вывести дерево\n"
        << " PRINT <тип>   - обход дерева (IN, PRE, POST, LEVEL)\n"
        << " ISFULL            - проверить полноту\n"
        << " SEARCH <val>    - поиск значения\n"
        << " CLEAR             - очистить дерево\n"
        << " EXIT              - выход\n"
        << "=================================\n";

    string line;
    while (true) {
        cout << ">> ";
        getline(cin >> ws, line);
        processCommand(root, line, filename);
    }
}