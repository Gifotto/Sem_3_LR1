#include "DynamicArray.h"
#include <fstream>
#include <sstream>

const int MIN_SIZE = 4;

// Конструктор
void Minit(DynamicArray& darr, int init_size) {
    darr.max_size = max(init_size, MIN_SIZE);
    darr.arr = new string[darr.max_size];
    darr.size = 0;
}

// Изменение размера
void MreSize(DynamicArray& darr, int new_max_size) {
    string* newdarr = new string[new_max_size];
    for (int i = 0; i < darr.size; i++) {
        newdarr[i] = darr.arr[i];
    }
    delete[] darr.arr;
    darr.arr = newdarr;
    darr.max_size = new_max_size;
}

// Добавление элемента в конец
void Mpush_back(DynamicArray& darr, string value) {
    if (darr.size == darr.max_size)
        MreSize(darr, darr.max_size * 2);
    darr.arr[darr.size++] = value;
}

// Вставка по индексу
void Mpush_index(DynamicArray& darr, int index, string value) {
    if (index < 0 || index > darr.size)
        return;
    if (darr.size == darr.max_size)
        MreSize(darr, darr.max_size * 2);
    for (int i = darr.size; i > index; i--) {
        darr.arr[i] = darr.arr[i - 1];
    }
    darr.arr[index] = value;
    darr.size++;
}

// Получение элемента
string Mget(DynamicArray& darr, int index) {
    if (index < 0 || index >= darr.size)
        throw out_of_range("Индекс вне диапазона");
    return darr.arr[index];
}

// Установка значения
void Mset(DynamicArray& darr, int index, string value) {
    if (index < 0 || index >= darr.size)
        return;
    darr.arr[index] = value;
}

// Удаление элемента
void Mremove(DynamicArray& darr, int index) {
    if (index < 0 || index >= darr.size)
        return;
    for (int i = index; i < darr.size - 1; i++) {
        darr.arr[i] = darr.arr[i + 1];
    }
    darr.size--;
}

// Получение длины
int Mlength(DynamicArray& darr) {
    return darr.size;
}

// Печать массива
void print(const DynamicArray& darr) {
    for (int i = 0; i < darr.size; i++) {
        cout << darr.arr[i] << " ";
    }
    cout << endl;
}

// Удаление массива
void delArr(DynamicArray& darr) {
    delete[] darr.arr;
    darr.arr = nullptr;
    darr.size = 0;
    darr.max_size = 0;
}

// Сохранение динамического массива в файл
void saveDArr(const DynamicArray& darr, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    file << darr.size << endl;  // сохраняем количество элементов
    for (int i = 0; i < darr.size; i++) {
        file << darr.arr[i] << endl;  // каждое значение на новой строке
    }
    file.close();
}

// Загрузка динамического массива из файла
void loadDArr(DynamicArray& darr, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return;
    }

    // Очищаем текущий массив
    delArr(darr);

    int n;
    file >> n;
    file.ignore();  // пропускаем символ конца строки после числа
    Minit(darr, n); // создаём массив нужного размера

    string value;
    for (int i = 0; i < n; i++) {
        getline(file, value);
        Mpush_back(darr, value);
    }
    file.close();
}
