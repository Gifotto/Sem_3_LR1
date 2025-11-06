#include "DoublyLinkedList.h"
#include <fstream>
#include <sstream>

// Создание нового узла
LList* createNodeD(string value) {
    LList* newNodeD = new LList;
    newNodeD->data = value;
    newNodeD->next = nullptr;
    newNodeD->pred = nullptr;
    return newNodeD;
}

// Добавление в начало (head)
void LaddFront(LList*& head, LList*& tail, string value) {
    LList* NodeD = createNodeD(value);
    if (!head) {
        head = tail = NodeD;
    }
    else {
        NodeD->next = head;
        head->pred = NodeD;
        head = NodeD;
    }
}

// Добавление в конец (tail)
void LaddBack(LList*& head, LList*& tail, string value) {
    LList* NodeD = createNodeD(value);
    if (!tail) {
        head = tail = NodeD;
    }
    else {
        tail->next = NodeD;
        NodeD->pred = tail;
        tail = NodeD;
    }
}

// Добавление после узла с указанным значением
void LaddAfter(LList*& head, LList*& tail, string afterValue, string newValue) {
    LList* current = head;
    while (current && current->data != afterValue)
        current = current->next;

    if (!current) {
        cout << "Элемент " << afterValue << " не найден.\n";
        return;
    }

    LList* NodeD = createNodeD(newValue);
    NodeD->pred = current;
    NodeD->next = current->next;

    if (current->next)
        current->next->pred = NodeD;
    else
        tail = NodeD; // вставка после хвоста

    current->next = NodeD;
}

// Добавление перед узлом с указанным значением
void LaddBefore(LList*& head, LList*& tail, string beforeValue, string newValue) {
    LList* current = head;
    while (current && current->data != beforeValue)
        current = current->next;

    if (!current) {
        cout << "Элемент " << beforeValue << " не найден.\n";
        return;
    }

    LList* NodeD = createNodeD(newValue);
    NodeD->next = current;
    NodeD->pred = current->pred;

    if (current->pred)
        current->pred->next = NodeD;
    else
        head = NodeD; // вставка перед головой

    current->pred = NodeD;
}

// Удаление из начала
void LreFront(LList*& head, LList*& tail) {
    if (head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    LList* temp = head;
    head = head->next;
    if (head != nullptr)
        head->pred = nullptr;
    else
        tail = nullptr; // список стал пуст
    delete temp;
}

// Удаление из конца
void LreBack(LList*& head, LList*& tail) {
    if (tail == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    LList* temp = tail;
    tail = tail->pred;
    if (tail != nullptr)
        tail->next = nullptr;
    else
        head = nullptr; // список стал пуст
    delete temp;
}

// Удаление элемента после заданного значения
void LreAfter(LList*& head, LList*& tail, string afterValue) {
    LList* cur = head;
    while (cur && cur->data != afterValue)
        cur = cur->next;

    if (!cur || !cur->next) {
        cout << "Невозможно удалить элемент после " << afterValue << endl;
        return;
    }

    LList* toDel = cur->next;
    cur->next = toDel->next;

    if (toDel->next)
        toDel->next->pred = cur;
    else
        tail = cur;

    delete toDel;
}

// Удаление элемента перед заданным значением
void LreBefore(LList*& head, LList*& tail, string beforeValue) {
    LList* cur = head;
    while (cur && cur->data != beforeValue)
        cur = cur->next;

    if (!cur || !cur->pred) {
        cout << "Невозможно удалить элемент перед " << beforeValue << endl;
        return;
    }

    LList* toDel = cur->pred;
    if (toDel->pred)
        toDel->pred->next = cur;
    else
        head = cur;

    cur->pred = toDel->pred;
    delete toDel;
}

// Удаление по значению
void LreValue(LList*& nd, LList*& tail, string value) {
    if (nd == nullptr) {
        cout << "Список пуст\n";
        return;
    }

    LList* current = nd;
    while (current != nullptr) {
        if (current->data == value) {
            if (current == nd)
                LreFront(nd, tail);
            else if (current == tail)
                LreBack(nd, tail);
            else {
                current->pred->next = current->next;
                current->next->pred = current->pred;
                delete current;
            }
            cout << "Удален элемент со значением " << value << endl;
            return;
        }
        current = current->next;
    }
    cout << "Элемент " << value << " не найден\n";
}

// Поиск по значению — возвращает индекс (или -1, если не найден)
int Lsearch(LList* nd, string value) {
    int index = 0;
    LList* current = nd;
    while (current != nullptr) {
        if (current->data == value)
            return index;
        current = current->next;
        index++;
    }
    return -1; // не найден
}

// Вывод списка от начала к концу
void printForward(LList* nd) {
    cout << "Список (прямой): ";
    LList* current = nd;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Вывод списка от конца к началу
void printBackward(LList* tail) {
    cout << "Список (обратный): ";
    LList* current = tail;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->pred;
    }
    cout << endl;
}

// Очистка памяти
void Lclear(LList*& nd) {
    LList* current = nd;
    while (current != nullptr) {
        LList* next = current->next;
        delete current;
        current = next;
    }
    nd = nullptr;
}