package stack

import (
	"fmt"
)

// Stack — элемент стека
type Stack struct {
	Val  string
	Next *Stack
}

// --- Добавление элемента в стек ---
func Spush(top **Stack, value string, size *int, maxSize int) {
	if isFull(*size, maxSize) {
		fmt.Println("Стек переполнен! Добавление невозможно.")
		return
	}

	newNode := &Stack{Val: value, Next: *top}
	*top = newNode
	*size++
}

// --- Удаление элемента из стека ---
func Spop(top **Stack, size *int) string {
	if isEmpty(*top) {
		fmt.Println("Стек пуст! Удаление невозможно.")
		return ""
	}

	value := (*top).Val
	*top = (*top).Next
	*size--
	return value
}

// --- Чтение верхнего элемента ---
func Peek(top *Stack) string {
	if isEmpty(top) {
		fmt.Println("Стек пуст!")
		return ""
	}
	return top.Val
}

// --- Проверка на пустоту ---
func isEmpty(top *Stack) bool {
	return top == nil
}

// --- Проверка на заполненность ---
func isFull(size, maxSize int) bool {
	return size >= maxSize
}

// --- Вывод содержимого стека ---
func Print(top *Stack) {
	fmt.Print("Стек: ")
	current := top
	for current != nil {
		fmt.Print(current.Val, " ")
		current = current.Next
	}
	fmt.Println()
}

// --- Очистка стека ---
func Sclear(top **Stack, size *int) {
	for !isEmpty(*top) {
		Spop(top, size)
	}
}
