package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
  //"errors"
 
	// === Структуры данных ===
  "Array_Lists_Stack/structures/dynamicarray"
	"Array_Lists_Stack/structures/singlylist"
	"Array_Lists_Stack/structures/doublylist"
	"Array_Lists_Stack/structures/stack"
)

// ===== Меню для динамического массива =====
func processArray(arr *dynamicarray.DynamicArray, filename string) {
	fmt.Println("===== Меню работы с динамическим массивом =====")
	fmt.Println("Команды:")
	fmt.Println("  PUSH <val>       - добавить элемент в конец")
	fmt.Println("  INSERT <i> <val> - вставить по индексу")
	fmt.Println("  REMOVE <i>       - удалить по индексу")
	fmt.Println("  GET <i>          - получить элемент по индексу")
	fmt.Println("  SET <i> <val>    - изменить элемент по индексу")
	fmt.Println("  LENGTH           - длина массива")
	fmt.Println("  PRINT            - вывести массив")
	fmt.Println("  CLEAR            - очистить массив")
	fmt.Println("  EXIT             - выход в главное меню")
	fmt.Println("==============================================")

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		ss := strings.Fields(line)
		if len(ss) == 0 {
			continue
		}
		cmd := strings.ToUpper(ss[0])

		switch cmd {
		case "PUSH":
			if len(ss) >= 2 {
				dynamicarray.Mpush_back(arr, ss[1])
				dynamicarray.SaveDArr(arr, filename)
			}
		case "INSERT":
			if len(ss) >= 3 {
				i, _ := strconv.Atoi(ss[1])
				dynamicarray.Mpush_index(arr, i, ss[2])
				dynamicarray.SaveDArr(arr, filename)
			}
		case "REMOVE":
			if len(ss) >= 2 {
				i, _ := strconv.Atoi(ss[1])
				dynamicarray.Mremove(arr, i)
				dynamicarray.SaveDArr(arr, filename)
			}
		case "GET":
    if len(ss) >= 2 {
        i, _ := strconv.Atoi(ss[1])
        val, err := dynamicarray.Mget(arr, i)
        if err != nil {
            fmt.Println("Ошибка:", err)
        } else {
            fmt.Println("Элемент:", val)
        }
    }

		case "SET":
			if len(ss) >= 3 {
				i, _ := strconv.Atoi(ss[1])
				dynamicarray.Mset(arr, i, ss[2])
				dynamicarray.SaveDArr(arr, filename)
			}
		case "LENGTH":
			fmt.Println("Длина массива:", dynamicarray.Mlength(arr))
		case "PRINT":
			dynamicarray.Print(arr)
		case "CLEAR":
			dynamicarray.DelArr(arr)
			dynamicarray.Minit(arr, 4)
			fmt.Println("Массив очищен")
			dynamicarray.SaveDArr(arr, filename)
		case "EXIT":
			return
		default:
			fmt.Println("Неизвестная команда")
		}
	}
}

// ===== Меню для односвязного списка =====
func processFList(head **singlylist.FList, filename string) {
	fmt.Println("===== Меню работы с односвязным списком =====")
	fmt.Println("Команды:")
	fmt.Println("  PUSHFRONT <val>  - добавить в начало")
	fmt.Println("  PUSHBACK <val>   - добавить в конец")
	fmt.Println("  PUSHAFTER <x> <val>  - добавить после значения x")
	fmt.Println("  PUSHBEFORE <x> <val> - добавить перед значением x")
	fmt.Println("  REFRONT          - удалить из начала")
	fmt.Println("  REBACK           - удалить из конца")
	fmt.Println("  REVAL <val>      - удалить по значению")
	fmt.Println("  REAFTER <x>      - удалить после значения x")
	fmt.Println("  REBEFORE <x>     - удалить перед значением x")
	fmt.Println("  PRINT            - вывести список")
	fmt.Println("  SEARCH <val>     - поиск элемента")
	fmt.Println("  CLEAR            - очистить список")
	fmt.Println("  EXIT             - выход в главное меню")
	fmt.Println("=============================================")

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		ss := strings.Fields(line)
		if len(ss) == 0 {
			continue
		}
		cmd := strings.ToUpper(ss[0])
	
		switch cmd {
		case "PUSHFRONT":
			if len(ss) >= 2 {
				singlylist.FaddFront(head, ss[1])
			}
		case "PUSHBACK":
			if len(ss) >= 2 {
				singlylist.FaddBack(head, ss[1])
			}
		case "PUSHAFTER":
			if len(ss) >= 3 {
				target, val := ss[1], ss[2]
				node := singlylist.Fsearch(*head, target)
				if node == nil {
					fmt.Println("Элемент", target, "не найден.")
				} else {
					singlylist.FaddAfter(node, val)
				}
			}
		case "PUSHBEFORE":
			if len(ss) >= 3 {
				target, val := ss[1], ss[2]
				node := singlylist.Fsearch(*head, target)
				if node == nil {
					fmt.Println("Элемент", target, "не найден.")
				} else {
					singlylist.FaddBefore(head, node, val)
				}
			}
		case "REFRONT":
			if !singlylist.FreFront(head) {
				fmt.Println("Список пуст.")
			}
		case "REBACK":
			if !singlylist.FreBack(head) {
				fmt.Println("Список пуст.")
			}
		case "REVAL":
			if len(ss) >= 2 {
				if !singlylist.FreValue(head, ss[1]) {
					fmt.Println("Список пуст.")
				}
			}
		case "REAFTER":
			if len(ss) >= 2 {
				val := ss[1]
				node := singlylist.Fsearch(*head, val)
				if node == nil {
					fmt.Println("Элемент", val, "не найден.")
				} else if !singlylist.FreAfter(node) {
					fmt.Println("После", val, "нет элемента.")
				}
			}
		case "REBEFORE":
			if len(ss) >= 2 {
				val := ss[1]
				node := singlylist.Fsearch(*head, val)
				if node == nil {
					fmt.Println("Элемент", val, "не найден.")
				} else if !singlylist.FreBefore(head, node) {
					fmt.Println("Перед", val, "нет элемента.")
				}
			}
		case "PRINT":
			singlylist.Print(*head)
		case "SEARCH":
			if len(ss) >= 2 {
				node := singlylist.Fsearch(*head, ss[1])
				if node != nil {
					fmt.Println("Элемент найден:", node.Key)
				} else {
					fmt.Println("Элемент не найден.")
				}
			}
		case "CLEAR":
			singlylist.Fclear(head)
			fmt.Println("Список очищен")
		case "EXIT":
			return
		default:
			fmt.Println("Неизвестная команда")
		}
	}
}

// ===== Меню для двусвязного списка =====
func processLList(head **doublylist.LList, tail **doublylist.LList, filename string) {
	fmt.Println("===== Меню работы с двусвязным списком =====")
	fmt.Println("Команды:")
	fmt.Println("  PUSHFRONT <val> - добавить в начало")
	fmt.Println("  PUSHBACK <val>  - добавить в конец")
	fmt.Println("  PUSHAFTER <x> <val>  - добавить после значения x")
	fmt.Println("  PUSHBEFORE <x> <val> - добавить перед значением x")
	fmt.Println("  PRINTF          - вывести вперёд")
	fmt.Println("  PRINTB          - вывести назад")
	fmt.Println("  REVAL <val>     - удалить по значению")
	fmt.Println("  REFRONT         - удалить из начала")
	fmt.Println("  REBACK          - удалить из конца")
	fmt.Println("  REAFTER <x>     - удалить после значения x")
	fmt.Println("  REBEFORE <x>    - удалить перед значением x")
	fmt.Println("  CLEAR           - очистить список")
	fmt.Println("  SEARCH <val>    - поиск элемента")
	fmt.Println("  EXIT            - выход в главное меню")
	fmt.Println("============================================")

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		ss := strings.Fields(line)
		if len(ss) == 0 {
			continue
		}
		cmd := strings.ToUpper(ss[0])
	
		switch cmd {
		case "PUSHFRONT":
			if len(ss) >= 2 {
				doublylist.LaddFront(head, tail, ss[1])
			}
		case "PUSHBACK":
			if len(ss) >= 2 {
				doublylist.LaddBack(head, tail, ss[1])
			}
		case "PUSHAFTER":
			if len(ss) >= 3 {
				doublylist.LaddAfter(head, tail, ss[1], ss[2])
			}
		case "PUSHBEFORE":
			if len(ss) >= 3 {
				doublylist.LaddBefore(head, tail, ss[1], ss[2])
			}
		case "PRINTF":
			doublylist.PrintForward(*head)
		case "PRINTB":
			doublylist.PrintBackward(*tail)
		case "REVAL":
			if len(ss) >= 2 {
				doublylist.LreValue(head, tail, ss[1])
			}
		case "REFRONT":
			doublylist.LreFront(head, tail)
		case "REBACK":
			doublylist.LreBack(head, tail)
		case "REAFTER":
			if len(ss) >= 2 {
				doublylist.LreAfter(head, tail, ss[1])
			}
		case "REBEFORE":
			if len(ss) >= 2 {
				doublylist.LreBefore(head, tail, ss[1])
			}
		case "SEARCH":
			if len(ss) >= 2 {
				idx := doublylist.Lsearch(*head, ss[1])
				if idx >= 0 {
					fmt.Println("Найден элемент на позиции", idx)
				} else {
					fmt.Println("Элемент не найден")
				}
			}
		case "CLEAR":
			doublylist.Lclear(head)
			*tail = nil
			fmt.Println("Список очищен")
		case "EXIT":
			return
		default:
			fmt.Println("Неизвестная команда")
		}
	}
}

// ===== Меню для стека =====
func processStack(top **stack.Stack, size *int, maxSize int, filename string) {
	fmt.Println("===== Меню работы со стеком =====")
	fmt.Println("Команды:")
	fmt.Println("  PUSH <val>  - добавить элемент")
	fmt.Println("  POP         - удалить верхний элемент")
	fmt.Println("  PEEK        - показать верхний элемент")
	fmt.Println("  PRINT       - вывести стек")
	fmt.Println("  CLEAR       - очистить стек")
	fmt.Println("  EXIT        - выход в главное меню")
	fmt.Println("==================================")

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		ss := strings.Fields(line)
		if len(ss) == 0 {
			continue
		}
		cmd := strings.ToUpper(ss[0])
	
		switch cmd {
		case "PUSH":
			if len(ss) >= 2 {
				stack.Spush(top, ss[1], size, maxSize)
			}
		case "POP":
			if *size > 0 {
				val := stack.Spop(top, size)
				fmt.Println("Удалён:", val)
			} else {
				fmt.Println("Пусто")
			}
		case "PEEK":
			if *size > 0 {
				fmt.Println("Верхний элемент:", stack.Peek(*top))
			} else {
				fmt.Println("Пусто")
			}
		case "PRINT":
			stack.Print(*top)
		case "CLEAR":
			stack.Sclear(top, size)
			fmt.Println("Стек очищен")
		case "EXIT":
			return
		default:
			fmt.Println("Неизвестная команда")
		}
	}
}

// ===== Точка входа =====
func main() {
	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Println("\n===== Главное меню =====")
		fmt.Println("1. Динамический массив")
		fmt.Println("2. Односвязный список")
		fmt.Println("3. Двусвязный список")
		fmt.Println("4. Стек")
		fmt.Println("5. Выход")
		fmt.Print("=========================\n> ")

		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		choice, _ := strconv.Atoi(line)

		switch choice {
		case 1:
			var arr dynamicarray.DynamicArray
			dynamicarray.Minit(&arr, 2)            // инициализация
			filename := "arr.data"
			dynamicarray.LoadDArr(&arr, filename)  // загрузка
			processArray(&arr, filename)
			dynamicarray.DelArr(&arr)              // очистка памяти
		case 2:
			var head *singlylist.FList
			filename := "FList.data"
			processFList(&head, filename)
			singlylist.Fclear(&head)               // очистка списка
		case 3:
			var head, tail *doublylist.LList
			filename := "LList.data"
			processLList(&head, &tail, filename)
			doublylist.Lclear(&head)               // очистка списка
		case 4:
			fmt.Print("Введите максимальный размер стека: ")
			line, _ = reader.ReadString('\n')
			maxSize, _ := strconv.Atoi(strings.TrimSpace(line))
			var top *stack.Stack
			size := 0
			filename := "Stack.data"
			processStack(&top, &size, maxSize, filename)
			stack.Sclear(&top, &size)              // очистка стека
		case 5:
			fmt.Println("Выход из программы.")
			return
		default:
			fmt.Println("Неверный выбор.")
		}
	}
}
