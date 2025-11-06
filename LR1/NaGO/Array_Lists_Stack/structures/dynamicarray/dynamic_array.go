package dynamicarray

import (
	"bufio"
  //"errors"
	"fmt"
	"os"
)

const MIN_SIZE = 4

// DynamicArray — аналог структуры из C++
type DynamicArray struct {
	arr      []string
	size     int
	max_size int
}

// Инициализация массива
func Minit(darr *DynamicArray, init_size int) {
	if init_size < MIN_SIZE {
		init_size = MIN_SIZE
	}
	darr.arr = make([]string, init_size)
	darr.size = 0
	darr.max_size = init_size
}

// Изменение размера
func MreSize(darr *DynamicArray, new_max_size int) {
	newArr := make([]string, new_max_size)
	copy(newArr, darr.arr[:darr.size])
	darr.arr = newArr
	darr.max_size = new_max_size
}

// Добавление элемента в конец
func Mpush_back(darr *DynamicArray, value string) {
	if darr.size == darr.max_size {
		MreSize(darr, darr.max_size*2)
	}
	darr.arr[darr.size] = value
	darr.size++
}

// Вставка по индексу
func Mpush_index(darr *DynamicArray, index int, value string) {
	if index < 0 || index > darr.size {
		return
	}
	if darr.size == darr.max_size {
		MreSize(darr, darr.max_size*2)
	}
	darr.arr = append(darr.arr[:index+1], darr.arr[index:darr.size]...)
	darr.arr[index] = value
	darr.size++
}

// Получение элемента
func Mget(arr *DynamicArray, index int) (string, error) {
    if index < 0 || index >= arr.size {
        return "", fmt.Errorf("индекс %d вне диапазона", index)
    }
    return arr.arr[index], nil
}

// Установка значения
func Mset(darr *DynamicArray, index int, value string) {
	if index < 0 || index >= darr.size {
		return
	}
	darr.arr[index] = value
}

// Удаление элемента
func Mremove(darr *DynamicArray, index int) {
	if index < 0 || index >= darr.size {
		return
	}
	copy(darr.arr[index:], darr.arr[index+1:darr.size])
	darr.size--
}

// Получение длины
func Mlength(darr *DynamicArray) int {
	return darr.size
}

// Печать массива
func Print(darr *DynamicArray) {
	for i := 0; i < darr.size; i++ {
		fmt.Print(darr.arr[i], " ")
	}
	fmt.Println()
}

// Удаление массива
func DelArr(darr *DynamicArray) {
	darr.arr = nil
	darr.size = 0
	darr.max_size = 0
}

// Сохранение динамического массива в файл
func SaveDArr(darr *DynamicArray, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка открытия файла для записи!")
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintln(writer, darr.size)
	for i := 0; i < darr.size; i++ {
		fmt.Fprintln(writer, darr.arr[i])
	}
	writer.Flush()
}

// Загрузка динамического массива из файла
func LoadDArr(darr *DynamicArray, filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Ошибка открытия файла для чтения!")
		return
	}
	defer file.Close()

	DelArr(darr)

	var n int
	fmt.Fscan(file, &n)
	Minit(darr, n)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		value := scanner.Text()
		if value != "" {
			Mpush_back(darr, value)
		}
	}
}
