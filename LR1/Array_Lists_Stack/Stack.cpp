#include "Stack.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// --- Добавление элемента в cтек ---
void Spush(Stack*& top, const string& value, int& size, int maxSize) {
    if (isFull(size, maxSize)) {
        cout << "Стек переполнен! Добавление невозможно.\n";
        return;
    }

    Stack* newStack = new Stack;
    newStack->val = value;
    newStack->next = top;
    top = newStack;
    size++;
}

// --- Удаление элемента из стека ---
string Spop(Stack*& top, int& size) {
    if (isEmpty(top)) {
        cout << "Стек пуст! Удаление невозможно.\n";
        return "";
    }

    string value = top->val;
    Stack* temp = top;
    top = top->next;
    delete temp;
    size--;
    return value;
}

// --- Чтение верхнего элемента ---
string peek(Stack* top) {
    if (isEmpty(top)) {
        cout << "Стек пуст!\n";
        return "";
    }
    return top->val;
}

// --- Проверка на пустоту ---
bool isEmpty(Stack* top) {
    return top == nullptr;
}

// --- Проверка на заполненность ---
bool isFull(int size, int maxSize) {
    return size >= maxSize;
}

// --- Вывод содержимого стека ---
void print(Stack* top) {
    cout << "Стек: ";
    Stack* current = top;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;
}

// --- Очистка стека ---
void Sclear(Stack*& top, int& size) {
    while (!isEmpty(top)) {
        Spop(top, size);
    }
}

/*
// Сохранение стека в файл
void saveStack(const Stack& s, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }
    file << s.size << std::endl; // сохраняем количество элементов
    for (int i = 0; i < s.size; i++) {
        file << s.data[i] << std::endl; // каждый элемент на новой строке
    }
    file.close();
}

// Загрузка стека из файла
void loadStack(Stack& s, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Ошибка открытия файла для чтения!" << std::endl;
        return;
    }

    // Очищаем текущий стек
    delete[] s.data;
    s.data = nullptr;
    s.size = 0;
    s.capacity = 0;

    int n;
    file >> n;
    file.ignore(); // пропускаем символ конца строки
    s.capacity = n;
    s.data = new std::string[s.capacity];

    std::string value;
    for (int i = 0; i < n; i++) {
        getline(file, value);
        s.data[s.size++] = value; // добавляем в стек
    }

    file.close();
}
*/