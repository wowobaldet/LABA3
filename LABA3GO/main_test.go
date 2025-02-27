package main

import (
    //"strings"
	"fmt"
    "testing"
)

// Тест проверки поиска элементов в дереве
func TestFind(t *testing.T) {
    tree := &Tree{root: nil}
    tree.TFind(tree.root, "69") 
    // Добавляем элементы в дерево
    tree.TPush(tree.root, "5")
    tree.TPush(tree.root, "3")
    tree.TPush(tree.root, "7")

    // Проверяем наличие элементов
    if !tree.TFind(tree.root, "5") {
        t.Errorf("Expected '5' to be found in the tree")
    }
    if !tree.TFind(tree.root, "3") {
        t.Errorf("Expected '3' to be found in the tree")
    }
    if tree.TFind(tree.root, "69") {
        t.Errorf("Expected '69' not to be found in the tree")
    }
}

// Тест проверки добавления элементов в дерево
func TestPush(t *testing.T) {
    tree := &Tree{root: nil}

    // Добавляем элементы в дерево
    tree.TPush(tree.root, "5")
    tree.TPush(tree.root, "53")
    tree.TPush(tree.root, "4")
    tree.TPush(tree.root, "51")

    // Проверяем наличие добавленных элементов
    if !tree.TFind(tree.root, "5") {
        t.Errorf("Expected '5' to be found in the tree")
    }
    if !tree.TFind(tree.root, "53") {
        t.Errorf("Expected '53' to be found in the tree")
    }
    if !tree.TFind(tree.root, "4") {
        t.Errorf("Expected '4' to be found in the tree")
    }
    if !tree.TFind(tree.root, "51") {
        t.Errorf("Expected '51' to be found in the tree")
    }
}

// Тест проверки полноты дерева
func TestIsFull(t *testing.T) {
    tree := &Tree{root: nil}
    if tree.IsFull(tree.root) {
        t.Errorf("Expected tree not to be full")
    }
    // Добавляем элементы в дерево
    tree.TPush(tree.root, "b")
    tree.TPush(tree.root, "c")

    // Проверяем, что дерево не полностью заполнено
    if tree.IsFull(tree.root) {
        t.Errorf("Expected tree to not be full")
    }

    // Добавляем третий элемент
    tree.TPush(tree.root, "a")

    // Проверяем, что дерево теперь полностью заполнено
    if !tree.IsFull(tree.root) {
        t.Errorf("Expected tree to be full")
    }
}

// Тест проверки пустого дерева
func TestIsEmpty(t *testing.T) {
    tree := &Tree{root: nil}

    // Проверяем, что дерево пустое
    if !tree.IsEmpty() {
        t.Errorf("Expected tree to be empty")
    }

    // Добавляем элемент в дерево
    tree.TPush(tree.root, "5")

    // Проверяем, что дерево больше не пустое
    if tree.IsEmpty() {
        t.Errorf("Expected tree to not be empty after adding an element")
    }
}

// Тест печати дерева (проверка структуры)
func TestPrintTree(t *testing.T) {
    
    tree := &Tree{root: nil}
    tree.PrintTree(tree.root, 0)
    // Добавляем элементы в дерево
    tree.TPush(tree.root, "5")
    tree.TPush(tree.root, "3")
    tree.TPush(tree.root, "7")
    tree.TPush(tree.root, "2")
    tree.TPush(tree.root, "4")
    tree.TPush(tree.root, "6")
    tree.TPush(tree.root, "8")


    tree.PrintTree(tree.root, 0)

}

// Бенчмарк для метода TPush
func BenchmarkTPush(b *testing.B) {
    tree := &Tree{}

    // Запускаем b.N итераций, чтобы измерить производительность
    for i := 0; i < b.N; i++ {
        tree.TPush(tree.root, fmt.Sprintf("item-%d", i))
    }
}

// Бенчмарк для метода TFind
func BenchmarkTFind(b *testing.B) {
    tree := &Tree{}

    // Добавляем элементы в дерево перед началом бенчмарка
    for i := 0; i < 1000; i++ {
        tree.TPush(tree.root, fmt.Sprintf("item-%d", i))
    }

    // Запускаем b.N итераций поиска
    b.ResetTimer() // Сбрасываем таймер, чтобы не учитывать время подготовки данных
    for i := 0; i < b.N; i++ {
        tree.TFind(tree.root, fmt.Sprintf("item-%d", i%1000)) // Ищем случайные элементы
    }
}

// Бенчмарк для метода PrintTree
func BenchmarkPrintTree(b *testing.B) {
    tree := &Tree{}

    // Добавляем элементы в дерево перед началом бенчмарка
    for i := 0; i < 1000; i++ {
        tree.TPush(tree.root, fmt.Sprintf("item-%d", i))
    }

    // Запускаем b.N итераций печати
    b.ResetTimer() // Сбрасываем таймер, чтобы не учитывать время подготовки данных
    for i := 0; i < b.N; i++ {
        tree.PrintTree(tree.root, 0)
    }
}