#include "Queue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Инициализация очереди с заданной вместимостью
void initQueue(Queue& q, int capacity) {
    //if ()
    q.data = new string[capacity];
    q.size = 0;
    q.capacity = capacity;
    q.front = 0;
    q.back = 0;
}

// Проверка, пуста ли очередь
bool isEmpty(const Queue& q) {
    return q.size == 0;
}

// Добавление элемента в очередь
void Qpush(Queue& q, const string& value) {
    if (q.size >= q.capacity) {
        cout << "Ошибка: очередь переполнена!" << endl;
        return;
    }
    q.data[q.back] = value;
    q.back = (q.back + 1) % q.capacity;
    q.size++;
}

// Удаление элемента из очереди
string Qpop(Queue& q, string& value) {
    if (isEmpty(q)) {
        cout << "Ошибка: очередь пуста!" << endl;
    }
    value = q.data[q.front];
    q.front = (q.front + 1) % q.capacity;
    q.size--;
    return value;
}

// Просмотр первого элемента
string peek(const Queue& q) {
    if (isEmpty(q)) {
        return "Очередь пуста!";
    }
    return q.data[q.front];
}

// Получение длины очереди
int length(const Queue& q) {
    return q.size;
}

// Печать очереди
void print(const Queue& q) {
    if (isEmpty(q)) {
        cout << "Очередь пуста!" << endl;
        return;
    }
    cout << "Очередь: ";
    for (int i = 0, idx = q.front; i < q.size; i++) {
        cout << q.data[idx] << " ";
        idx = (idx + 1) % q.capacity;
    }
    cout << endl;
}

// Очистка очереди
void Qclear(Queue& q) {
    q.size = 0;
    q.front = 0;
    q.back = 0;
}

// Сохранение очереди в файл
void saveQueue(const Queue& q, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    file << q.size << endl;
    for (int i = 0, idx = q.front; i < q.size; i++) {
        file << q.data[idx] << endl;
        idx = (idx + 1) % q.capacity;
    }
    file.close();
}

// Загрузка очереди из файла
void loadQueue(Queue& q, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return;
    }
    Qclear(q);
    int n;
    file >> n;
    file.ignore(); // пропуск символа конца строки
    string value;
    for (int i = 0; i < n; i++) {
        getline(file, value);
        Qpush(q, value);
    }
    file.close();
}

// Очистка памяти очереди
void freeQueue(Queue& q) {
    delete[] q.data;
    q.data = nullptr;
    q.size = 0;
    q.capacity = 0;
    q.front = 0;
    q.back = 0;
}
