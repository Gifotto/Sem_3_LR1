#pragma once
#include <iostream>
using namespace std;

// ”зел двусв€зного списка
struct LList {
    string data;
    LList* next;
    LList* pred;
};

// —оздание нового узла
LList* createNodeD(string value);

// --- ƒобавление ---
void LaddFront(LList*& head, LList*& tail, string value);             // добавление в начало
void LaddBack(LList*& head, LList*& tail, string value);              // добавление в конец
void LaddAfter(LList*& head, LList*& tail, string afterValue, string newValue);  // добавление после указанного значени€
void LaddBefore(LList*& head, LList*& tail, string beforeValue, string newValue); // добавление перед указанным значением

// --- ”даление ---
void LreFront(LList*& head, LList*& tail);                         // удаление из начала
void LreBack(LList*& head, LList*& tail);                          // удаление из конца
void LreAfter(LList*& head, LList*& tail, string afterValue);     // удаление после заданного значени€
void LreBefore(LList*& head, LList*& tail, string beforeValue);   // удаление перед заданным значением
void LreValue(LList*& head, LList*& tail, string value);              // удаление по значению

// --- ѕоиск ---
int Lsearch(LList* head, string value);                              // поиск по значению, возвращает индекс

// --- „тение / вывод ---
void printForward(LList* head);                                  // пр€мой обход
void printBackward(LList* tail);                                 // обратный обход

// --- ќчистка пам€ти ---
void Lclear(LList*& head);
