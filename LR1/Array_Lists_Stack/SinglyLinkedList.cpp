#include "SinglyLinkedList.h"

// Добавление в начало
void FaddFront(FList*& nd, string value) {
    FList* newNode = new FList;    // создаем новый узел
    newNode->key = value;
    newNode->next = nd;        // новый указывает на старый "первый"
    nd = newNode;              // теперь он — первый
}

// Добавление в конец
void FaddBack(FList*& nd, string value) {
    FList* newNode = new FList;
    newNode->key = value;
    newNode->next = nullptr;

    if (!nd) {
        nd = newNode;
        return;
    }

    FList* temp = nd;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

// --- Добавление после узла ---
bool FaddAfter(FList* nd, string value) {
    if (!nd) return false;

    FList* newNode = new FList{ value, nd->next };
    nd->next = newNode;
    return true;
}

// --- Добавление перед узлом ---
bool FaddBefore(FList*& head, FList* nd, string value) {
    if (!head || !nd) return false;

    // если добавляем перед головой
    if (head == nd) {
        FaddFront(head, value);
        return true;
    }

    FList* temp = head;
    while (temp->next && temp->next != nd)
        temp = temp->next;

    if (!temp->next) return false; // nd не найден

    FList* newNode = new FList{ value, nd };
    temp->next = newNode;
    return true;
}

// Удаление первого элемента
bool FreFront(FList*& nd) {
    if (!nd) return false; // список пуст

    FList* tempDel = nd;
    nd = nd->next;
    delete tempDel;
    return true;
}

// Удаление последнего элемента
bool FreBack(FList*& nd) {
    if (!nd) return false; // пустой список

    if (!nd->next) {
        delete nd;
        nd = nullptr;
        return true;
    }

    FList* temp = nd;
    while (temp->next->next)
        temp = temp->next;

    delete temp->next;
    temp->next = nullptr;
    return true;
}

// --- Удаление после узла ---
bool FreAfter(FList* nd) {
    if (!nd || !nd->next) return false;

    FList* temp = nd->next;
    nd->next = temp->next;
    delete temp;
    return true;
}

// --- Удаление перед узлом ---
bool FreBefore(FList*& head, FList* nd) {
    if (!head || !nd || head == nd) return false;

    // если нужно удалить сам head->next перед nd
    if (head->next == nd) {
        FList* temp = head;
        head = nd;
        delete temp;
        return true;
    }

    FList* temp = head;
    while (temp->next && temp->next->next != nd)
        temp = temp->next;

    if (!temp->next) return false; // nd не найдено

    FList* toDelete = temp->next;
    temp->next = nd;
    delete toDelete;
    return true;
}

// Удаление по значению
bool FreValue(FList*& nd, string value) {
    if (!nd) return false;

    if (nd->key == value) {
        FList* tempDel = nd;
        nd = nd->next;
        delete tempDel;
        return true;
    }

    FList* cur = nd;
    while (cur->next && cur->next->key != value)
        cur = cur->next;

    if (!cur->next) return false;

    FList* tempDel = cur->next;
    cur->next = cur->next->next;
    delete tempDel;
    return true;
}

// Поиск по значению
FList* Fsearch(FList* nd, string value) {
    FList* cur = nd;
    while (cur) {
        if (cur->key == value)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

// Вывод списка
void print(FList* nd) {
    FList* cur = nd;
    while (cur) {
        cout << cur->key << " ";
        cur = cur->next;
    }
    //cout << "nullptr";
}

// --- Рекурсивный вывод ---
void printRecursive(FList* head) {
    if (!head) {
        //cout << "nullptr\n";
        return;
    }
    cout << head->key << " ";
    printRecursive(head->next);
}

// Очистка памяти
void Fclear(FList*& nd) {
    while (nd) {
        FList* temp = nd;
        nd = nd->next;
        delete temp;
    }
}