#include <iostream>
#include "my_stack.h"
#include "pch.h"

using namespace std;

template <class INF>
MyStack<INF>::MyStack(void) {
	Node newNode;
	top = &newNode;
}

template <class INF>
MyStack<INF>::~MyStack(void) {
	while (top->next != nullptr) {
		Node* temp = top->next;
		top->next = top->next->next;
		delete temp;
	}
}

template <class INF>
bool MyStack<INF>::empty(void) {
	return (top->next != nullptr);
}

template <class INF>
bool MyStack<INF>::push(INF data) {
	top->d = data;
	Node newNode;
	newNode.next = top;
	top = &newNode;
	return true;
}

template <class INF>
bool MyStack<INF>::pop(void) {
	if (empty()) {
		return false;
	}
	top->next = top->next->next;
	if (top->d != nullptr) {
		delete top->d;
	}
	return true;
}

template <class INF>
INF* MyStack<INF>::top_inf(void) {
	return top->next->d;
}
