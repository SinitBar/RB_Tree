#pragma once
#include "Node.h"
template <class Key_Type, class Value_Type>
class Element
{
	Element<Key_Type, Value_Type>* next;
	Node<Key_Type, Value_Type>* data;
	void set_next(Element<Key_Type, Value_Type>* new_element) { next = new_element; }
	void set_data(Node<Key_Type, Value_Type>* new_data) { data = new_data; }

public:
	Element() { data = nullptr; next = nullptr; }
	Element<Key_Type, Value_Type>* get_next() { return next; }
	Node<Key_Type, Value_Type>* get_data() { return data; }
	~Element() {}
	template <class Key_Type, class Value_Type> friend class Queue;
	template <class Key_Type, class Value_Type> friend class Stack;
};