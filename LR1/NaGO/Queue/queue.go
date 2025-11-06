package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

// ===== Структура очереди =====
type Queue struct {
	data     []string
	size     int
	capacity int
	front    int
	back     int
}

// ===== Инициализация очереди =====
func initQueue(q *Queue, capacity int) {
	q.data = make([]string, capacity)
	q.size = 0
	q.capacity = capacity
	q.front = 0
	q.back = 0
}

// ===== Проверка, пуста ли очередь =====
func isEmpty(q *Queue) bool {
	return q.size == 0
}

// ===== Добавление элемента =====
func Qpush(q *Queue, value string) {
	if q.size >= q.capacity {
		fmt.Println("Ошибка: очередь переполнена!")
		return
	}
	q.data[q.back] = value
	q.back = (q.back + 1) % q.capacity
	q.size++
}

// ===== Удаление элемента =====
func Qpop(q *Queue) string {
	if isEmpty(q) {
		fmt.Println("Ошибка: очередь пуста!")
		return ""
	}
	value := q.data[q.front]
	q.front = (q.front + 1) % q.capacity
	q.size--
	return value
}

// ===== Просмотр первого элемента =====
func peek(q *Queue) string {
	if isEmpty(q) {
		return "Очередь пуста!"
	}
	return q.data[q.front]
}

// ===== Получение длины =====
func length(q *Queue) int {
	return q.size
}

// ===== Печать =====
func printQueue(q *Queue) {
	if isEmpty(q) {
		fmt.Println("Очередь пуста!")
		return
	}
	fmt.Print("Очередь: ")
	idx := q.front
	for i := 0; i < q.size; i++ {
		fmt.Print(q.data[idx], " ")
		idx = (idx + 1) % q.capacity
	}
	fmt.Println()
}

// ===== Очистка =====
func Qclear(q *Queue) {
	q.size = 0
	q.front = 0
	q.back = 0
}

// ===== Сохранение в файл =====
func saveQueue(q *Queue, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка открытия файла для записи!")
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintln(writer, q.size)
	idx := q.front
	for i := 0; i < q.size; i++ {
		fmt.Fprintln(writer, q.data[idx])
		idx = (idx + 1) % q.capacity
	}
	writer.Flush()
}

// ===== Загрузка из файла =====
func loadQueue(q *Queue, filename string) {
	file, err := os.Open(filename)
	if err != nil {
		// если файла нет — просто создаём пустую очередь
		return
	}
	defer file.Close()

	Qclear(q)
	scanner := bufio.NewScanner(file)

	if !scanner.Scan() {
		return
	}
	n, _ := strconv.Atoi(scanner.Text())

	for i := 0; i < n && scanner.Scan(); i++ {
		Qpush(q, scanner.Text())
	}
}
