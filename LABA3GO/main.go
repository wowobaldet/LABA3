package main

import (
	"fmt"
	"strings"
)

// Узел дерева
type TNode struct {
	data  string
	left  *TNode
	right *TNode
}

// Дерево
type Tree struct {
	root *TNode
}

// Проверка, пусто ли дерево
func (t *Tree) IsEmpty() bool {
	return t.root == nil
}

// Добавление элемента в дерево
func (t *Tree) TPush(current *TNode, newData string) {
	if t.IsEmpty() {
		t.root = &TNode{data: newData, left: nil, right: nil}
		return
	}

	if current.left == nil {
		current.left = &TNode{data: newData, left: nil, right: nil}
		return
	}

	if current.right == nil {
		current.right = &TNode{data: newData, left: nil, right: nil}
		return
	}

	if newData >= current.data {
		t.TPush(current.right, newData)
	} else {
		t.TPush(current.left, newData)
	}
}

// Поиск элемента в дереве
func (t *Tree) TFind(current *TNode, findData string) bool {
	if t.IsEmpty() {
		fmt.Println("Tree is empty")
		return false
	}

	if current.data == findData {
		return true
	}

	for current != nil {
		if current.left == nil && current.right == nil {
			break
		}

		if current.left != nil && current.left.data == findData {
			return true
		}

		if current.right != nil && current.right.data == findData {
			return true
		}

		if findData > current.data {
			current = current.right
		} else {
			current = current.left
		}
	}

	return false
}

// Проверка, полностью ли заполнено дерево
func (t *Tree) IsFull(current *TNode) bool {
	if t.IsEmpty() {
		fmt.Println("Tree is empty")
		return false
	}

	if current == nil {
		return true
	}

	if current.left == nil && current.right == nil {
		return true
	}

	if current.left != nil && current.right != nil {
		return t.IsFull(current.left) && t.IsFull(current.right)
	}

	return false
}


// Печать дерева (возвращает bool)
func (t *Tree) PrintTree(root *TNode, level int) bool {
    if t.IsEmpty() {
        fmt.Println("Tree is empty")
        return false
    }
    if root != nil {
        t.PrintTree(root.right, level+1)
        fmt.Printf("%s%s\n", strings.Repeat("    ", level), root.data)
        t.PrintTree(root.left, level+1)
    }
    return true
}
