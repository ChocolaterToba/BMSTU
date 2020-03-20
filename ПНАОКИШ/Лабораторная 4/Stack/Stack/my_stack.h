#ifndef MY_STACK_H
#define MY_STACK_H

#include "pch.h"
#include "framework.h"

//Шаблонный класс ListNode (узел односвязного списка)
template <class INF, class FRIEND>
class ListNode				//узел списка
{
private:
	INF d;             			     //информационная часть узла
	ListNode* next;   		         //указатель на следующий узел списка
	ListNode(void) { next = NULL; }  //конструктор 
	friend FRIEND;
};

//Шаблонный класс MyStack на основе односвязного списка.
template <class INF>
class MyStack
{
	typedef class ListNode < INF, MyStack <INF> > Node;
	Node* top;
public:
	MyStack(void);		// конструктор
	~MyStack(void);         	// освободить динамическую память
	bool empty(void);		// стек пустой?
	bool push(INF n);		// добавить узел в вершину стека
	bool pop(void);		// удалить узел из вершины стека
	INF top_inf(void);		//считать информацию из вершины стека
};

template <class INF>
MyStack<INF>::MyStack(void) {
	top = nullptr;
}

template <class INF>
MyStack<INF>::~MyStack(void) {
	while (top != nullptr) {
		Node* temp = top;
		top = top->next;
		delete temp;
	}
}

template <class INF>
bool MyStack<INF>::empty(void) {
	return (top == nullptr);
}

template <class INF>
bool MyStack<INF>::push(INF data) {
	Node* node = new Node();
	node->next = top;
	node->d = data;
	top = node;
	return true;
}

template <class INF>
bool MyStack<INF>::pop(void) {
	if (!empty()) {
		top = top->next;
		return true;
	}
	return false;
}

template <class INF>
INF MyStack<INF>::top_inf(void) {
	return top->d;
}


#endif //  MY_STACK_H
