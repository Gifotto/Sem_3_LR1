#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Queue {
    string* data;
    int size;
    int capacity;
    int front;
    int back;
};

// Инициализация очереди с заданной вместимостью
void initQueue(Queue& q, int capacity = 100);

// Проверка, пуста ли очередь
bool isEmpty(const Queue& q);

// Добавление элемента в очередь
void Qpush(Queue& q, const string& value);

// Удаление элемента из очереди
string Qpop(Queue& q, string& value);

// Просмотр первого элемента
string peek(const Queue& q);

// Получение длины очереди
int length(const Queue& q);

// Печать очереди
void print(const Queue& q);

// Очистка очереди
void Qclear(Queue& q);

// Сохранение очереди в файл
void saveQueue(const Queue& q, const string& filename);

// Загрузка очереди из файла
void loadQueue(Queue& q, const string& filename);

// Очистка памяти очереди
void freeQueue(Queue& q);
