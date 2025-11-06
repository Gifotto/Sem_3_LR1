#pragma once
#include <string>
using namespace std;

// --- Узел стека ---
struct Stack {
    string val;     // значение элемента
    Stack* next;    // указатель на следующий элемент
};

// --- Добавление элемента в стек ---
void Spush(Stack*& top, const string& value, int& size, int maxSize);

// --- Удаление элемента из стека ---
string Spop(Stack*& top, int& size);

// --- Чтение верхнего элемента ---
string peek(Stack* top);

// --- Проверка на пустоту ---
bool isEmpty(Stack* top);

// --- Проверка на заполненность ---
bool isFull(int size, int maxSize);

// --- Вывод содержимого стека ---
void print(Stack* top);

// --- Очистка стека ---
void Sclear(Stack*& top, int& size);

/*
// Сохранение стека в файл
void saveStack(const Stack& st, const string& filename);

// Загрузка стека из файла
void loadStack(Stack& st, const string& filename);
*/