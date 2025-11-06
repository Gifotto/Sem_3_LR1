package singlylist

import "fmt"

// FList — элемент односвязного списка
type FList struct {
	Key  string
	Next *FList
}

// Добавление в начало
func FaddFront(head **FList, value string) {
	newNode := &FList{Key: value, Next: *head}
	*head = newNode
}

// Добавление в конец
func FaddBack(head **FList, value string) {
	newNode := &FList{Key: value, Next: nil}
	if *head == nil {
		*head = newNode
		return
	}
	temp := *head
	for temp.Next != nil {
		temp = temp.Next
	}
	temp.Next = newNode
}

// Добавление после узла
func FaddAfter(nd *FList, value string) bool {
	if nd == nil {
		return false
	}
	newNode := &FList{Key: value, Next: nd.Next}
	nd.Next = newNode
	return true
}

// Добавление перед узлом
func FaddBefore(head **FList, nd *FList, value string) bool {
	if *head == nil || nd == nil {
		return false
	}
	if *head == nd {
		FaddFront(head, value)
		return true
	}
	temp := *head
	for temp.Next != nil && temp.Next != nd {
		temp = temp.Next
	}
	if temp.Next == nil {
		return false
	}
	newNode := &FList{Key: value, Next: nd}
	temp.Next = newNode
	return true
}

// Удаление первого элемента
func FreFront(head **FList) bool {
	if *head == nil {
		return false
	}
	*head = (*head).Next
	return true
}

// Удаление последнего элемента
func FreBack(head **FList) bool {
	if *head == nil {
		return false
	}
	if (*head).Next == nil {
		*head = nil
		return true
	}
	temp := *head
	for temp.Next.Next != nil {
		temp = temp.Next
	}
	temp.Next = nil
	return true
}

// Удаление после узла
func FreAfter(nd *FList) bool {
	if nd == nil || nd.Next == nil {
		return false
	}
	nd.Next = nd.Next.Next
	return true
}

// Удаление перед узлом
func FreBefore(head **FList, nd *FList) bool {
	if *head == nil || nd == nil || *head == nd {
		return false
	}
	if (*head).Next == nd {
		*head = nd
		return true
	}
	temp := *head
	for temp.Next != nil && temp.Next.Next != nd {
		temp = temp.Next
	}
	if temp.Next == nil {
		return false
	}
	temp.Next = nd
	return true
}

// Удаление по значению
func FreValue(head **FList, value string) bool {
	if *head == nil {
		return false
	}
	if (*head).Key == value {
		*head = (*head).Next
		return true
	}
	cur := *head
	for cur.Next != nil && cur.Next.Key != value {
		cur = cur.Next
	}
	if cur.Next == nil {
		return false
	}
	cur.Next = cur.Next.Next
	return true
}

// Поиск по значению
func Fsearch(nd *FList, value string) *FList {
	cur := nd
	for cur != nil {
		if cur.Key == value {
			return cur
		}
		cur = cur.Next
	}
	return nil
}

// Вывод списка
func Print(nd *FList) {
	cur := nd
	for cur != nil {
		fmt.Print(cur.Key, " ")
		cur = cur.Next
	}
	fmt.Println()
}

// Рекурсивный вывод
func PrintRecursive(head *FList) {
	if head == nil {
		return
	}
	fmt.Print(head.Key, " ")
	PrintRecursive(head.Next)
}

// Очистка списка
func Fclear(head **FList) {
	for *head != nil {
		*head = (*head).Next
	}
}
