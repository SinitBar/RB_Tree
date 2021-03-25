#pragma once
#include "Element.h"
template <class Key_Type, class Value_Type>
class Queue
{
private:
	Element<Key_Type, Value_Type>* head; // the first in queue, leaves first
	Element<Key_Type, Value_Type>* tail; // the last, new in queue
	void set_head(Element<Key_Type, Value_Type>* key) { head = key; }
	void set_tail(Element<Key_Type, Value_Type>* key) { tail = key; }
public:
	Queue()
	{
		head = nullptr;
		tail = nullptr;
	}
	bool is_empty() // returns true if queue is empty
	{
		if (tail == nullptr)
			return true;
		return false;
	}
	int size() // return a number of elements in queue
	{
		if (is_empty())
			return 0;
		int size = 1;
		for (Element<Key_Type, Value_Type>* now = tail; now->get_next() != nullptr; now = now->get_next())
			size++;
		return size;
	}
	Element<Key_Type, Value_Type>* top() // to know who will leave first
	{ return head; }

	Element<Key_Type, Value_Type>* push(Node<Key_Type, Value_Type>* data_key) // to add in the end of the queue the element with key-data and return it to user
	{
		Element<Key_Type, Value_Type>* new_element = new Element<Key_Type, Value_Type>;
		new_element->set_data(data_key);
		if (is_empty())
			head = tail = new_element;
		else
		{
			new_element->set_next(tail);
			tail = new_element;
		}
		return new_element;
	}

	Element<Key_Type, Value_Type>* pop() // to delete first in queue and return it to user
	{
		Element<Key_Type, Value_Type>* to_delete;
		if (is_empty())
			throw out_of_range("the queue is empty");
		else if (size() == 1)
		{
			to_delete = head;
			head = tail = nullptr;
		}
		else
		{
			to_delete = head;
			for (Element<Key_Type, Value_Type>* now = tail; now->get_next() != nullptr; now = now->get_next())
				head = now;
			head->next = nullptr;
		}
		return to_delete;
	}
	
	~Queue()
	{
		while (!is_empty())
			pop();
	}
};