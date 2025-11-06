#pragma once
#include <iostream>

using namespace std;

struct FList {
	string key;
	FList* next;
};

//Добавление элементов
void FaddFront(FList*& head, string value);           // в начало
void FaddBack(FList*& head, string value);            // в конец
bool FaddAfter(FList* node, string value);            // после узла
bool FaddBefore(FList*& head, FList* node, string value); // перед узлом

//Удаление элементов
bool FreFront(FList*& head);                       // первый элемент
bool FreBack(FList*& head);                        // последний элемент
bool FreAfter(FList* node);                        // после узла
bool FreBefore(FList*& head, FList* node);          // перед узлом
bool FreValue(FList*& head, string value);            // по значению

//Поиск и вывод
FList* Fsearch(FList* head, string value);             // поиск по значению
void print(FList* head);                      // итеративный вывод
void printRecursive(FList* head);                 // рекурсивный вывод

//Очистка списка
void Fclear(FList*& head);						// удалить все узлы