package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

// ===== Обработка команд =====
func processCommand(queue *Queue, line string, filename string) {
	parts := strings.Fields(line)
	if len(parts) == 0 {
		return
	}
	cmd := strings.ToUpper(parts[0])

	switch cmd {
	case "PUSH":
		if len(parts) < 2 {
			fmt.Println("Введите значение после PUSH")
			return
		}
		Qpush(queue, parts[1])
		saveQueue(queue, filename)

	case "POP":
		Qpop(queue)
		saveQueue(queue, filename)

	case "PEEK":
		if !isEmpty(queue) {
			fmt.Println("Первый элемент:", peek(queue))
		} else {
			fmt.Println("Очередь пуста")
		}

	case "LENGTH":
		fmt.Println("Длина очереди:", length(queue))

	case "PRINT":
		printQueue(queue)

	case "CLEAR":
		Qclear(queue)
		saveQueue(queue, filename)
		fmt.Println("Очередь очищена")

	default:
		fmt.Println("Неизвестная команда:", cmd)
	}
}

// ===== Точка входа =====
func main() {
	queue := Queue{}
	initQueue(&queue, 100) // вместимость 100 элементов

	filename := "queue.data"
	loadQueue(&queue, filename)

	fmt.Println("===== Меню работы с очередью =====")
	fmt.Println("Команды:")
	fmt.Println("  PUSH <val>   - добавить элемент")
	fmt.Println("  POP          - удалить первый элемент")
	fmt.Println("  PEEK         - показать первый элемент")
	fmt.Println("  LENGTH       - длина очереди")
	fmt.Println("  PRINT        - вывести очередь")
	fmt.Println("  CLEAR        - очистить очередь")
	fmt.Println("  EXIT         - выход")
	fmt.Println("===================================")

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		if strings.ToUpper(line) == "EXIT" {
			break
		}
		processCommand(&queue, line, filename)
	}
}
