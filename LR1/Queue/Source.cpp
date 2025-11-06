#include "Queue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// --- Обработка команд ---
void processCommand(Queue& queue, const string& line, const string& filename) {
    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "PUSH") {
        string val; ss >> val;
        if (val.empty()) {
            cout << "Введите значение после PUSH\n";
            return;
        }
        Qpush(queue, val);
        saveQueue(queue, filename);
        //cout << "Добавлено: " << val << endl;
        return;
    }

    if (cmd == "POP") {
        string val;
        Qpop(queue, val);
        saveQueue(queue, filename);
        return;
    }

    if (cmd == "PEEK") {
        if (!isEmpty(queue))
            cout << "Первый элемент: " << peek(queue) << endl;
        else
            cout << "Очередь пуста\n";
        return;
    }

    if (cmd == "LENGTH") {
        cout << "Длина очереди: " << length(queue) << endl;
        return;
    }

    if (cmd == "PRINT") {
        print(queue);
        return;
    }

    if (cmd == "CLEAR") {
        Qclear(queue);
        saveQueue(queue, filename);
        cout << "Очередь очищена\n";
        return;
    }

    cout << "Неизвестная команда: " << cmd << endl;
}

// --- Точка входа ---
int main() {
    setlocale(0, "");

    Queue queue;
    initQueue(queue);

    string filename = "queue.data";
    loadQueue(queue, filename);

    cout << "===== Меню работы с очередью =====\n"
        << "Команды:\n"
        << "  PUSH <val>   - добавить элемент\n"
        << "  POP          - удалить первый элемент\n"
        << "  PEEK         - показать (без удаления) первый элемент\n"
        << "  LENGTH       - длина очереди\n"
        << "  PRINT        - вывести очередь\n"
        << "  CLEAR        - очистить очередь\n"
        << "  EXIT         - выход\n"
        << "===================================\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (!line.empty()) processCommand(queue, line, filename);
    }

    Qclear(queue);
    return 0;
}