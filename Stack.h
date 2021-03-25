#pragma once
#include "Element.h"
template <class Key_Type, class Value_Type>
class Stack
{
private:
	Element<Key_Type, Value_Type>* top;
	void set_top(Element<Key_Type, Value_Type>* top_element) { top = top_element; }
public:
	Stack() { top = nullptr; }
	bool is_empty()
	{
		if (top == nullptr)
			return true;
		return false;
	}
	int size()
	{
		int size = 1;
		if (is_empty())
			return 0;
		for (Element<Key_Type, Value_Type>* now = top; now->get_next() != nullptr; now = now->get_next())
			size++;
		return size;
	}
	Element<Key_Type, Value_Type>* peek() { return top; } // to show who's on the top
	Element<Key_Type, Value_Type>* pop() // to delte top and show it
	{
		Element<Key_Type, Value_Type>* to_delete = top;
		if (is_empty())
			throw out_of_range("the stack is empty");
		else
			top = top->get_next();
		return to_delete;
	}
	Element<Key_Type, Value_Type>* push(Node<Key_Type, Value_Type>* data) // to push on top and show it
	{
		Element<Key_Type, Value_Type>* new_element = new Element;
		new_element->set_data(data);
		if (is_empty())
			top = new_element;
		else
		{
			new_element->set_next(top);
			top = new_element;
		}
		return new_element;
	}
	~Stack()
	{
		while (!is_empty())
			pop();
	}
};
