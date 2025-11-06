#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "DynamicArray.h"
#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h"
#include "Stack.h"


// ===== Меню для динамического массива =====
void processArray(DynamicArray& arr, const string& filename) {
    cout << "===== Меню работы с динамическим массивом =====\n"
        << "Команды:\n"
        << "  PUSH <val>       - добавить элемент в конец\n"
        << "  INSERT <i> <val> - вставить по индексу\n"
        << "  REMOVE <i>       - удалить по индексу\n"
        << "  GET <i>          - получить элемент по индексу\n"
        << "  SET <i> <val>    - изменить элемент по индексу\n"
        << "  LENGTH           - длина массива"
        << "  PRINT            - вывести массив\n"
        << "  CLEAR            - очистить массив\n"
        << "  EXIT             - выход в главное меню\n"
        << "==============================================\n";

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        stringstream ss(line);
        string cmd; ss >> cmd;

        if (cmd == "PUSH") {
            string v; ss >> v;
            Mpush_back(arr, v);
            saveDArr(arr, filename);
        }
        else if (cmd == "LENGTH") {
            Mlength(arr);
        }
        else if (cmd == "INSERT") {
            int i;
            string v; ss >> i >> v;
            Mpush_index(arr, i, v);
            saveDArr(arr, filename);
        }
        else if (cmd == "REMOVE") {
            int i; ss >> i;
            Mremove(arr, i);
            saveDArr(arr, filename);
        }
        else if (cmd == "GET") {
            int i; ss >> i;
            cout << "Элемент: " << Mget(arr, i) << endl;
        }
        else if (cmd == "SET") {
            int i;
            string v; ss >> i >> v;
            Mset(arr, i, v);
            saveDArr(arr, filename);
        }
        else if (cmd == "PRINT") {
            print(arr);
        }
        else if (cmd == "CLEAR") {
            delArr(arr);
            Minit(arr, 1);
            cout << "Массив очищен\n";
            saveDArr(arr, filename);
        }
        else if (cmd == "EXIT") break;
        else if (!cmd.empty()) cout << "Неизвестная команда\n";
    }
}

// ===== Меню для односвязного списка =====
void processFList(FList*& head, const string& filename) {
    cout << "===== Меню работы с односвязным списком =====\n"
        << "Команды:\n"
        << "  PUSHFRONT <val>  - добавить в начало\n"
        << "  PUSHBACK <val>   - добавить в конец\n"
        << "  PUSHAFTER <x> <val>  - добавить после значения x\n"
        << "  PUSHBEFORE <x> <val> - добавить перед значением x\n"
        << "  REFRONT           - удалить из начала\n"
        << "  REBACK             - удалить из конца\n"
        << "  REVAL  <val>      - удалить по заначению\n"
        << "  REAFTER            - удалить после значения x\n"
        << "  REBEFORE           - удалить перед значением x\n"
        << "  PRINT            - вывести список\n"
        << "  SEARCH           - поиск элемента\n"
        << "  CLEAR            - очистить список\n"
        << "  EXIT             - выход в главное меню\n"
        << "=============================================\n";

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        stringstream ss(line);
        string cmd; ss >> cmd;

        if (cmd == "PUSHFRONT") {
            string v; ss >> v;
            FaddFront(head, v);
        }
        else if (cmd == "PUSHBACK") {
            string v; ss >> v;
            FaddBack(head, v);
        }
        else if (cmd == "PUSHAFTER") {
            string target, val; ss >> target >> val;
            FList* node = Fsearch(head, target);
            if (!node) cout << "Элемент " << target << " не найден.\n";
            else FaddAfter(node, val);
        }
        else if (cmd == "PUSHBEFORE") {
            string target, val; ss >> target >> val;
            FList* node = Fsearch(head, target);
            if (!node) cout << "Элемент " << target << " не найден.\n";
            else FaddBefore(head, node, val);
        }
        else if (cmd == "REFRONT") {
            if (!FreFront(head)) cout << "Список пуст.\n";
        }
        else if (cmd == "REBACK") {
            if (!FreBack(head)) cout << "Список пуст.\n";
        }
        else if (cmd == "REVAL") {
            string val; ss >> val;
            if (!FreValue(head, val)) cout << "Список пуст.\n";
        }
        else if (cmd == "REAFTER") {
            string val; ss >> val;
            FList* node = Fsearch(head, val);
            if (!node) cout << "Элемент " << val << " не найден.\n";
            else if (!FreAfter(node)) cout << "После " << val << " нет элемента.\n";
        }
        else if (cmd == "REBEFORE") {
            string val; ss >> val;
            FList* node = Fsearch(head, val);
            if (!node) cout << "Элемент " << val << " не найден.\n";
            else if (!FreBefore(head, node)) cout << "Перед " << val << " нет элемента.\n";
        }
        else if (cmd == "PRINT") {
            print(head);
        }
        else if (cmd == "SEARCH") {
            string val; ss >> val;
            FList* node = Fsearch(head, val);
            if (node) cout << "Элемент найден: " << node->key << endl;
            else cout << "Элемент не найден.\n";
        }
        else if (cmd == "CLEAR") {
            Fclear(head);
            cout << "Список очищен\n";
        }
        else if (cmd == "EXIT") break;
        else if (!cmd.empty()) cout << "Неизвестная команда\n";
    }
}

// ===== Меню для двусвязного списка =====
void processLList(LList*& head, LList*& tail, const string& filename) {
    cout << "===== Меню работы с двусвязным списком =====\n"
        << "Команды:\n"
        << "  PUSHFRONT <val> - добавить в начало\n"
        << "  PUSHBACK <val>  - добавить в конец\n"
        << "  PUSHAFTER <x> <val>  - добавить после значения x\n"
        << "  PUSHBEFORE <x> <val> - добавить перед значением x\n"
        << "  PRINTF          - вывести вперёд\n"
        << "  PRINTB          - вывести назад\n"
        << "  REVAL   <val>     - удалить по заначению\n"
        << "  REFRONT           - удалить из начала\n"
        << "  REBACK             - удалить из конца\n"
        << "  REAFTER <x> <val>  - удалить после значения x\n"
        << "  REBEFORE <x> <val> - удалить перед значением x\n"
        << "  CLEAR           - очистить список\n"
        << "  SEARCH           - поиск элемента\n"
        << "  EXIT            - выход в главное меню\n"
        << "============================================\n";

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        stringstream ss(line);
        string cmd; ss >> cmd;

        if (cmd == "PUSHFRONT") {
            string v; ss >> v;
            LaddFront(head, tail, v);
        }
        else if (cmd == "PUSHBACK") {
            string v; ss >> v;
            LaddBack(head, tail, v);
        }
        else if (cmd == "PUSHAFTER") {
            string target, val; ss >> target >> val;
            LaddAfter(head, tail, target, val);
        }
        else if (cmd == "PUSHBEFORE") {
            string target, val; ss >> target >> val;
            LaddBefore(head, tail, target, val);
        }
        else if (cmd == "PRINTF") {
            printForward(head);
        }
        else if (cmd == "PRINTB") {
            printBackward(tail);
        }
        else if (cmd == "REVAL") {
            string val; ss >> val;
            LreValue(head, tail, val);
        }
        else if (cmd == "REFRONT") {
            LreFront(head, tail);
        }
        else if (cmd == "REBACK") {
            LreBack(head, tail);
        }
        else if (cmd == "REAFTER") {
            string target; ss >> target;
            LreAfter(head, tail, target);
        }
        else if (cmd == "REBEFORE") {
            string target; ss >> target;
            LreBefore(head, tail, target);
        }

        else if (cmd == "SEARCH") {
            string val; ss >> val;
            int idx = Lsearch(head, val);
            if (idx >= 0) cout << "Найден элемент на позиции " << idx << endl;
            else cout << "Элемент не найден\n";
        }

        else if (cmd == "CLEAR") {
            Lclear(head);
            tail = nullptr;
            cout << "Список очищен\n";
        }
        else if (cmd == "EXIT") break;
        else if (!cmd.empty()) cout << "Неизвестная команда\n";
    }
}

// ===== Меню для стека =====
void processStack(Stack*& top, int& size, int maxSize, const string& filename) {
    cout << "===== Меню работы со стеком =====\n"
        << "Команды:\n"
        << "  PUSH <val>  - добавить элемент\n"
        << "  POP         - удалить верхний элемент\n"
        << "  PEEK        - показать верхний элемент\n"
        << "  PRINT       - вывести стек\n"
        << "  CLEAR       - очистить стек\n"
        << "  EXIT        - выход в главное меню\n"
        << "==================================\n";

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        stringstream ss(line);
        string cmd; ss >> cmd;

        if (cmd == "PUSH") {
            string v; ss >> v;
            Spush(top, v, size, maxSize);
        }
        else if (cmd == "POP") {
            if (size > 0) cout << "Удалён: " << Spop(top, size) << endl;
            else cout << "Пусто\n";
        }
        else if (cmd == "PEEK") {
            if (size > 0) cout << "Верхний элемент: " << peek(top) << endl;
            else cout << "Пусто\n";
        }
        else if (cmd == "PRINT") {
            print(top);
        }
        else if (cmd == "CLEAR") {
            Sclear(top, size);
            cout << "Стек очищен\n";
        }
        else if (cmd == "EXIT") break;
        else if (!cmd.empty()) cout << "Неизвестная команда\n";
    }
}

// ===== Точка входа =====
int main() {
    setlocale(0, "");

    while (true) {
        cout << "\n===== Главное меню =====\n"
            << "1. Динамический массив\n"
            << "2. Односвязный список\n"
            << "3. Двусвязный список\n"
            << "4. Стэк\n"
            << "5. Выход\n"
            << "=========================\n"
            << "> ";

        int choice;
        cin >> choice;
        cin.ignore();

        //вообще я переделаю на switch
        if (choice == 1) {
            DynamicArray arr;
            Minit(arr);

            string filename = "arr.data";
            loadDArr(arr, filename);
            processArray(arr, filename);
            delArr(arr);
        }
        else if (choice == 2) {
            string filename = "FList.data";
            FList* head = nullptr;

            processFList(head, filename);
            Fclear(head);
        }
        else if (choice == 3) {
            string filename = "LList.data";
            LList* head = nullptr, * tail = nullptr;

            processLList(head, tail, filename);
            Lclear(head);
        }
        else if (choice == 4) {
            string filename = "Stack.data";
            Stack* top = nullptr;

            int size = 0, maxSize;
            cout << "Введите максимальный размер стека: ";
            cin >> maxSize; cin.ignore();

            processStack(top, size, maxSize, filename);
            Sclear(top, size);
        }
        else if (choice == 5) {
            cout << "Выход из программы.\n";
            break;
        }
        else {
            cout << "Неверный выбор.\n";
        }
    }

    return 0;
}