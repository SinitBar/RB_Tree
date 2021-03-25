#pragma once
#include "Node.h"
template <class Key_Type, class Value_Type>
class Iterator
{
public:
	virtual Node<Key_Type, Value_Type>* next() = 0; // return current element and goes to the next
	virtual bool has_next() = 0; // return true if next exists
};