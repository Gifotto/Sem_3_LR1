package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"Full_Binary_Tree/tree"
)

func processCommand(root **tree.Node, line, filename string) {
	tokens := strings.Fields(line)
	if len(tokens) == 0 {
		return
	}
	cmd := strings.ToUpper(tokens[0])

	switch cmd {
	case "TROOT":
		if len(tokens) < 2 {
			fmt.Println("Введите значение: TROOT <val>")
			return
		}
		if *root != nil {
			fmt.Println("Корень уже существует.")
			return
		}
		val, _ := strconv.Atoi(tokens[1])
		*root = tree.CreateNode(val)
		fmt.Println("Создан корень", val)

	case "TINSERT":
		if len(tokens) < 3 {
			fmt.Println("Введите два значения: TINSERT <a> <b>")
			return
		}
		a, _ := strconv.Atoi(tokens[1])
		b, _ := strconv.Atoi(tokens[2])
		tree.InsertPair(root, a, b)
		fmt.Println("Добавлены узлы", a, "и", b)

	case "NICEPRINT":
		if *root == nil {
			fmt.Println("Дерево пусто")
		} else {
			tree.PrintTree(*root, 0, 4)
		}

	case "PRINT":
		if len(tokens) < 2 {
			fmt.Println("Введите тип обхода: IN, PRE, POST, LEVEL")
			return
		}
		if *root == nil {
			fmt.Println("Дерево пусто")
			return
		}
		switch strings.ToUpper(tokens[1]) {
		case "IN":
			tree.Inorder(*root)
		case "PRE":
			tree.Preorder(*root)
		case "POST":
			tree.Postorder(*root)
		case "LEVEL":
			tree.LevelOrder(*root)
		default:
			fmt.Println("Неизвестный тип обхода. Используйте: IN, PRE, POST, LEVEL")
		}
		fmt.Println()

	case "ISFULL":
		fmt.Println(tree.IsFullTree(*root))

	case "SEARCH":
		if len(tokens) < 2 {
			fmt.Println("Введите значение: SEARCH <val>")
			return
		}
		val, _ := strconv.Atoi(tokens[1])
		fmt.Println(tree.FindValue(*root, val))

	case "CLEAR":
		tree.ClearTree(root)
		fmt.Println("Дерево очищено.")

	case "EXIT":
		fmt.Println("Выход из программы.")
		os.Exit(0)

	default:
		fmt.Println("Неизвестная команда:", cmd)
	}

	// Сохраняем после каждой операции
	fout, _ := os.Create(filename)
	tree.SaveToFile(*root, fout)
	fout.Close()
}

func main() {
	root := (*tree.Node)(nil)
	filename := "tree.data"

	// Загрузка из файла
	if file, err := os.Open(filename); err == nil {
		scanner := bufio.NewScanner(file)
		scanner.Split(bufio.ScanWords)
		root = tree.LoadFromFile(scanner)
		file.Close()
		fmt.Println("Файл", filename, "загружен.")
	} else {
		file, _ := os.Create(filename)
		file.WriteString("# ")
		file.Close()
		fmt.Println("Создан новый файл", filename)
	}

	fmt.Println("============= Меню ==============")
	fmt.Println(" TROOT <val>       - создать корень")
	fmt.Println(" TINSERT <a> <b>   - добавить пару узлов")
	fmt.Println(" NICEPRINT         - вывести дерево")
	fmt.Println(" PRINT <тип>       - обход дерева (IN, PRE, POST, LEVEL)")
	fmt.Println(" ISFULL            - проверить полноту")
	fmt.Println(" SEARCH <val>      - поиск значения")
	fmt.Println(" CLEAR             - очистить дерево")
	fmt.Println(" EXIT              - выход")
	fmt.Println("=================================")

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print(">> ")
		if scanner.Scan() {
			line := scanner.Text()
			processCommand(&root, line, filename)
		}
	}
}
