package doublylist

import "fmt"

// LList — узел двусвязного списка
type LList struct {
	Data string
	Next *LList
	Pred *LList
}

// Создание нового узла
func createNodeD(value string) *LList {
	return &LList{
		Data: value,
		Next: nil,
		Pred: nil,
	}
}

// Добавление в начало (head)
func LaddFront(head **LList, tail **LList, value string) {
	node := createNodeD(value)
	if *head == nil {
		*head = node
		*tail = node
	} else {
		node.Next = *head
		(*head).Pred = node
		*head = node
	}
}

// Добавление в конец (tail)
func LaddBack(head **LList, tail **LList, value string) {
	node := createNodeD(value)
	if *tail == nil {
		*head = node
		*tail = node
	} else {
		(*tail).Next = node
		node.Pred = *tail
		*tail = node
	}
}

// Добавление после узла с указанным значением
func LaddAfter(head **LList, tail **LList, afterValue, newValue string) {
	current := *head
	for current != nil && current.Data != afterValue {
		current = current.Next
	}
	if current == nil {
		fmt.Println("Элемент", afterValue, "не найден.")
		return
	}

	node := createNodeD(newValue)
	node.Pred = current
	node.Next = current.Next

	if current.Next != nil {
		current.Next.Pred = node
	} else {
		*tail = node // вставка после хвоста
	}
	current.Next = node
}

// Добавление перед узлом с указанным значением
func LaddBefore(head **LList, tail **LList, beforeValue, newValue string) {
	current := *head
	for current != nil && current.Data != beforeValue {
		current = current.Next
	}
	if current == nil {
		fmt.Println("Элемент", beforeValue, "не найден.")
		return
	}

	node := createNodeD(newValue)
	node.Next = current
	node.Pred = current.Pred

	if current.Pred != nil {
		current.Pred.Next = node
	} else {
		*head = node // вставка перед головой
	}
	current.Pred = node
}

// Удаление из начала
func LreFront(head **LList, tail **LList) {
	if *head == nil {
		fmt.Println("Список пуст")
		return
	}
	temp := *head
	*head = (*head).Next
	if *head != nil {
		(*head).Pred = nil
	} else {
		*tail = nil
	}
	_ = temp // GC сам освободит
}

// Удаление из конца
func LreBack(head **LList, tail **LList) {
	if *tail == nil {
		fmt.Println("Список пуст")
		return
	}
	temp := *tail
	*tail = (*tail).Pred
	if *tail != nil {
		(*tail).Next = nil
	} else {
		*head = nil
	}
	_ = temp
}

// Удаление элемента после заданного значения
func LreAfter(head **LList, tail **LList, afterValue string) {
	cur := *head
	for cur != nil && cur.Data != afterValue {
		cur = cur.Next
	}
	if cur == nil || cur.Next == nil {
		fmt.Println("Невозможно удалить элемент после", afterValue)
		return
	}
	toDel := cur.Next
	cur.Next = toDel.Next
	if toDel.Next != nil {
		toDel.Next.Pred = cur
	} else {
		*tail = cur
	}
	_ = toDel
}

// Удаление элемента перед заданным значением
func LreBefore(head **LList, tail **LList, beforeValue string) {
	cur := *head
	for cur != nil && cur.Data != beforeValue {
		cur = cur.Next
	}
	if cur == nil || cur.Pred == nil {
		fmt.Println("Невозможно удалить элемент перед", beforeValue)
		return
	}
	toDel := cur.Pred
	if toDel.Pred != nil {
		toDel.Pred.Next = cur
	} else {
		*head = cur
	}
	cur.Pred = toDel.Pred
	_ = toDel
}

// Удаление по значению
func LreValue(head **LList, tail **LList, value string) {
	if *head == nil {
		fmt.Println("Список пуст")
		return
	}
	current := *head
	for current != nil {
		if current.Data == value {
			if current == *head {
				LreFront(head, tail)
			} else if current == *tail {
				LreBack(head, tail)
			} else {
				current.Pred.Next = current.Next
				current.Next.Pred = current.Pred
			}
			fmt.Println("Удален элемент со значением", value)
			return
		}
		current = current.Next
	}
	fmt.Println("Элемент", value, "не найден")
}

// Поиск по значению — возвращает индекс
func Lsearch(head *LList, value string) int {
	index := 0
	current := head
	for current != nil {
		if current.Data == value {
			return index
		}
		current = current.Next
		index++
	}
	return -1
}

// Вывод списка от начала к концу
func PrintForward(head *LList) {
	fmt.Print("Список (прямой): ")
	current := head
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Next
	}
	fmt.Println()
}

// Вывод списка от конца к началу
func PrintBackward(tail *LList) {
	fmt.Print("Список (обратный): ")
	current := tail
	for current != nil {
		fmt.Print(current.Data, " ")
		current = current.Pred
	}
	fmt.Println()
}

// Очистка списка
func Lclear(head **LList) {
	for *head != nil {
		*head = (*head).Next
	}
}
