package tree

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// ------------------- Структуры -------------------
type Node struct {
	Data  int
	Left  *Node
	Right *Node
}

// ------------------- Создание узла -------------------
func CreateNode(value int) *Node {
	return &Node{Data: value}
}

// ------------------- Поиск значения -------------------
func FindValue(root *Node, value int) bool {
	if root == nil {
		return false
	}
	if root.Data == value {
		return true
	}
	return FindValue(root.Left, value) || FindValue(root.Right, value)
}

// ------------------- Вставка пары узлов -------------------
func inFullTreeRec(root **Node, newNode1, newNode2 *Node) bool {
	if *root == nil {
		return false
	}

	if (*root).Left == nil && (*root).Right == nil {
		(*root).Left = newNode1
		(*root).Right = newNode2
		return true
	}

	var vib string
	fmt.Print("LEFT or RIGHT: ")
	fmt.Scanln(&vib)
	if strings.ToUpper(vib) == "LEFT" {
		if (*root).Left != nil && inFullTreeRec(&(*root).Left, newNode1, newNode2) {
			return true
		}
	} else {
		if (*root).Right != nil && inFullTreeRec(&(*root).Right, newNode1, newNode2) {
			return true
		}
	}
	return false
}

func InsertPair(root **Node, value1, value2 int) {
	newNode1 := CreateNode(value1)
	newNode2 := CreateNode(value2)

	if *root == nil {
		*root = CreateNode(-1) // значение корня по умолчанию
		(*root).Left = newNode1
		(*root).Right = newNode2
		return
	}

	inFullTreeRec(root, newNode1, newNode2)
}

// ------------------- Высота дерева -------------------
func Height(root *Node) int {
	if root == nil {
		return 0
	}
	lh := Height(root.Left)
	rh := Height(root.Right)
	if lh > rh {
		return lh + 1
	}
	return rh + 1
}

// ------------------- Обходы -------------------
func Inorder(root *Node) {
	if root == nil {
		return
	}
	Inorder(root.Left)
	fmt.Print(root.Data, " ")
	Inorder(root.Right)
}

func Preorder(root *Node) {
	if root == nil {
		return
	}
	fmt.Print(root.Data, " ")
	Preorder(root.Left)
	Preorder(root.Right)
}

func Postorder(root *Node) {
	if root == nil {
		return
	}
	Postorder(root.Left)
	Postorder(root.Right)
	fmt.Print(root.Data, " ")
}

// ------------------- Обход в ширину -------------------
func printLevel(root *Node, level int) {
	if root == nil {
		return
	}
	if level == 1 {
		fmt.Print(root.Data, " ")
	} else if level > 1 {
		printLevel(root.Left, level-1)
		printLevel(root.Right, level-1)
	}
}

func LevelOrder(root *Node) {
	h := Height(root)
	for i := 1; i <= h; i++ {
		printLevel(root, i)
	}
}

// ------------------- Красивый вывод дерева -------------------
func PrintTree(root *Node, space int, indent int) {
	if root == nil {
		return
	}

	PrintTree(root.Right, space+indent, indent)

	for i := 0; i < space; i++ {
		fmt.Print(" ")
	}
	fmt.Println(root.Data)

	PrintTree(root.Left, space+indent, indent)
}

// ------------------- Проверка полноты -------------------
func IsFullTree(root *Node) bool {
	if root == nil {
		return true
	}

	if root.Left == nil && root.Right == nil {
		return true
	}

	if root.Left != nil && root.Right != nil {
		return IsFullTree(root.Left) && IsFullTree(root.Right)
	}

	return false
}

// ------------------- Очистка -------------------
func ClearTree(root **Node) {
	if *root == nil {
		return
	}
	ClearTree(&(*root).Left)
	ClearTree(&(*root).Right)
	*root = nil
}

// ------------------- Сохранение и загрузка -------------------
func SaveToFile(root *Node, file *os.File) {
	if root == nil {
		file.WriteString("# ")
		return
	}
	file.WriteString(fmt.Sprintf("%d ", root.Data))
	SaveToFile(root.Left, file)
	SaveToFile(root.Right, file)
}

func LoadFromFile(scanner *bufio.Scanner) *Node {
	if !scanner.Scan() {
		return nil
	}
	val := scanner.Text()
	if val == "#" {
		return nil
	}

	num, err := strconv.Atoi(val)
	if err != nil {
		return nil
	}

	node := CreateNode(num)
	node.Left = LoadFromFile(scanner)
	node.Right = LoadFromFile(scanner)
	return node
}
