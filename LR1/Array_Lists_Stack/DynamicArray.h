#pragma once
#include <iostream>

using namespace std;

struct DynamicArray {
    int size;
    int max_size;
    string* arr;
};

// Инициализация массива
void Minit(DynamicArray& darr, int init_size = 4);

// Изменение размера массива
void MreSize(DynamicArray& darr, int new_max_size);

// Добавление элемента в конец
void Mpush_back(DynamicArray& darr, string value);

// Вставка элемента по индексу
void Mpush_index(DynamicArray& darr, int index, string value);

// Получение элемента по индексу
string Mget(DynamicArray& darr, int index);

// Установка значения элемента
void Mset(DynamicArray& darr, int index, string value);

// Удаление элемента по индексу
void Mremove(DynamicArray& darr, int index);

// Получение текущего размера массива
int Mlength(DynamicArray& darr);

// Печать элементов массива
void print(const DynamicArray& darr);

// Удаление массива и освобождение памяти
void delArr(DynamicArray& darr);

// Сохранение динамического массива в файл
void saveDArr(const DynamicArray& darr, const string& filename);

// Загрузка динамического массива из файла
void loadDArr(DynamicArray& darr, const string& filename);