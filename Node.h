#pragma once
#include <stdexcept>
#include <iostream> // is needed?

using namespace std;
enum class Color { red, black };

template <class Key_Type, class Value_Type>
class Node {
private:
	Key_Type key;
	Value_Type value;
	Color color;
	Node<Key_Type, Value_Type>* left = nullptr; // left child of current node
	Node<Key_Type, Value_Type>* right = nullptr; // right child of current node
	Node<Key_Type, Value_Type>* parent = nullptr; // parent of current node
	void set_key(Key_Type new_key) { key = new_key; }
	void set_value(Value_Type new_value) { value = new_value; }
	void set_color(Color new_color) { color = new_color; }
	void set_left(Node<Key_Type, Value_Type>* new_left) { left = new_left; }
	void set_right(Node<Key_Type, Value_Type>* new_right) { right = new_right; }
	void set_parent(Node<Key_Type, Value_Type>* new_parent) { parent = new_parent; }

public:
	Node(void) {}
	Node(Key_Type new_key, Value_Type new_value, Color new_color = Color::red, Node<Key_Type, Value_Type>* new_left = nullptr, Node<Key_Type, Value_Type>* new_right = nullptr, Node<Key_Type, Value_Type>* new_parent = nullptr)
	{
		key = new_key;
		value = new_value;
		color = new_color;
		left = new_left;
		right = new_right;
		parent = new_parent;
	}
	Node(Node<Key_Type, Value_Type>* node)
	{
		key = node->get_key();
		value = node->get_value();
		color = node->get_color();
		left = node->get_left();
		right = node->get_right();
		parent = node->get_parent();
	}
	//Node& operator=(const Node<Key_Type, Value_Type>& right)
	//{
	//	if (this == &right) // if made like a = a
	//		return (*this);
	//	key = right->get_key();
	//	value = right->get_value();
	//	color = right->get_color();
	//	left = right->get_left();
	//	right = right->get_right();
	//	parent = right->get_parent();
	//	return *this;
	//}
	Key_Type get_key() { return key; }
	Value_Type get_value() { return value; }
	Color get_color() { return color; }
	Node<Key_Type, Value_Type>* get_left() { return left; }
	Node<Key_Type, Value_Type>* get_right() { return right; }
	Node<Key_Type, Value_Type>* get_parent() { return parent; }
	template <class Key_Type, class Value_Type> friend class RB_Tree;
	template <class Key_Type, class Value_Type> friend class Element;
	template <class Key_Type, class Value_Type> friend class Queue;
	template <class Key_Type, class Value_Type> friend class Stack;
	~Node(void) {}
};
