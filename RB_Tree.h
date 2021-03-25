#pragma once
#include "Queue.h"
#include "Stack.h"
#include "Iterator.h"
#include <fstream>

template <class Key_Type, class Value_Type>
class RB_Tree {
private:

	Node<Key_Type, Value_Type>* root = nullptr;
	Node<Key_Type, Value_Type>* Nil = nullptr; // node after all lists, one big common child that is a parent for root
	int size = 0; // amount of nodes in the tree
	void set_root(Node<Key_Type, Value_Type>* new_root) // used when root already exists
	{ root = new_root; }

	// change sides and order of two elements by rules of the left rotate
	void left_turn(Node<Key_Type, Value_Type>* turn_node)
	{
		if (turn_node->get_right() == get_Nil())
			throw out_of_range("error-call of left-rotate with Nil-child");
		Node<Key_Type, Value_Type>* right_of_turn_node = turn_node->get_right();
		turn_node->set_right(right_of_turn_node->get_left());
		if (right_of_turn_node->get_left() != get_Nil())
			right_of_turn_node->get_left()->set_parent(turn_node);
		right_of_turn_node->set_parent(turn_node->get_parent());
		if (turn_node->get_parent() == get_Nil())
			set_root(right_of_turn_node);
		else if (turn_node == turn_node->get_parent()->get_left())
			turn_node->get_parent()->set_left(right_of_turn_node);
		else
			turn_node->get_parent()->set_right(right_of_turn_node);
		right_of_turn_node->set_left(turn_node);
		turn_node->set_parent(right_of_turn_node);
	}
	// change sides and order of two elements by rules of the right rotate
	void right_turn(Node<Key_Type, Value_Type>* turn_node)
	{
		if (turn_node->get_left() == get_Nil())
			throw out_of_range("error-call of left-rotate with Nil-child");
		Node<Key_Type, Value_Type>* left_of_turn_node = turn_node->get_left();
		turn_node->set_left(left_of_turn_node->get_right());
		if (left_of_turn_node->get_right() != get_Nil())
			left_of_turn_node->get_right()->set_parent(turn_node);
		left_of_turn_node->set_parent(turn_node->get_parent());
		if (turn_node->get_parent() == get_Nil())
			set_root(left_of_turn_node);
		else if (turn_node == turn_node->get_parent()->get_left())
			turn_node->get_parent()->set_left(left_of_turn_node);
		else
			turn_node->get_parent()->set_right(left_of_turn_node);
		left_of_turn_node->set_right(turn_node);
		turn_node->set_parent(left_of_turn_node);
	}

	void restoring_propertires_after_insert(Node<Key_Type, Value_Type>* new_node)
	{
		while (new_node->get_parent()->get_color() == Color::red)
		{
			Node<Key_Type, Value_Type>* P = new_node->get_parent(); // father of new_node
			Node<Key_Type, Value_Type>* G = P->get_parent(); //grand father of new_node
			Node<Key_Type, Value_Type>* U = G->get_right(); // uncle of new_node
			if (U == P)
				U = G->get_left();
			//case 1: red uncle
			if (U->get_color() == Color::red)
			{
				G->set_color(Color::red);
				P->set_color(Color::black);
				U->set_color(Color::black);
				restoring_propertires_after_insert(G);
				return;
			}
			else
			{
				//case 2: black uncle, other-sided G-son and P-son are 
				if (((P == G->get_left()) && (new_node == P->get_right())) || ((P == G->get_right()) && (new_node == P->get_left())))
				{
					if (new_node == P->get_right())
						left_turn(P);
					else
						right_turn(P);
					//going to case 3
				}
				// case 3: black uncle, one-sided G-son and P-son
				if (P == G->get_left())
					right_turn(G);
				else
					left_turn(G);
				P->set_color(Color::black);
				G->set_color(Color::red);
			}
		}
		root->set_color(Color::black); // to fix root's color
	}

	void restoring_propertires_after_delete(Node<Key_Type, Value_Type>* D)
	{ // D - is the node to be deleted, we saved it only for restoring everything right
		if (D == D->get_parent()->get_right())
		{
			Node<Key_Type, Value_Type>* P = D->get_parent(); // father of the deleting node
			Node<Key_Type, Value_Type>* S = P->get_left(); // will be the only son after deleting D
			Node<Key_Type, Value_Type>* LgS = S->get_left(); // left grandson of P
			Node<Key_Type, Value_Type>* RgS = S->get_right(); // right grandson of P
			Node<Key_Type, Value_Type>* L_LgS_S = LgS->get_left(); // left son of LgS
			Node<Key_Type, Value_Type>* R_LgS_S = LgS->get_right(); // right son of LgS
			Node<Key_Type, Value_Type>* L_RgS_S = RgS->get_left(); // left son of RgS
			Node<Key_Type, Value_Type>* R_RgS_S = RgS->get_right(); // right son of RgS
			if ((P->get_color() == Color::red) && (S->get_color() == Color::black))
			{
				//case 1: red parent, black left child with black grandsons
				if ((LgS->get_color() == Color::black) && (RgS->get_color() == Color::black))
				{
					P->set_color(Color::black);
					S->set_color(Color::red);
					return;
				}
				//case 2: red parent, black left child with left red son
				if (LgS->get_color() == Color::red)
				{
					right_turn(P);
					P->set_color(Color::black);
					S->set_color(Color::red);
					LgS->set_color(Color::black);
					return;
				}
				else if (RgS->get_color() == Color::red)
					P->set_color(Color::black); // to get into the case 5
			}

			if (P->get_color() == Color::black)
			{
				if (S->get_color() == Color::red)
				{
					//case 3: black parent, red left son, RgS has black grandsons
					if ((L_RgS_S->get_color() == Color::black) && (R_RgS_S->get_color() == Color::black))
					{
						right_turn(P);
						S->set_color(Color::black);
						RgS->set_color(Color::red); // he was black like son of the red one
						return;
					}
					//case 4: black parent, red left son, RgS has left red son
					else if (L_RgS_S->get_color() == Color::red)
					{
						left_turn(S);
						right_turn(P);
						L_RgS_S->set_color(Color::black);
						return;
					}
				}
				else
				{
					//case 5: black parent, black left son with right red son
					if (RgS->get_color() == Color::red)
					{
						left_turn(S);
						right_turn(P);
						RgS->set_color(Color::black);
						return;
					}
					//case 6: black parent, black left son with black sons
					else if (LgS->get_color() == Color::black)
					{
						S->set_color(Color::red);
						restoring_propertires_after_delete(P);
						return;
					}
				}
			}
		}
		else // simmetric cases
		{
			Node<Key_Type, Value_Type>* P = D->get_parent(); // father of the deleting node
			Node<Key_Type, Value_Type>* S = P->get_right(); // will be the only son after deleting D
			Node<Key_Type, Value_Type>* LgS = S->get_left(); // left grandson of P
			Node<Key_Type, Value_Type>* RgS = S->get_right(); // right grandson of P
			Node<Key_Type, Value_Type>* L_LgS_S = LgS->get_left(); // left son of LgS
			Node<Key_Type, Value_Type>* R_LgS_S = LgS->get_right(); // right son of LgS
			Node<Key_Type, Value_Type>* L_RgS_S = RgS->get_left(); // left son of RgS
			Node<Key_Type, Value_Type>* R_RgS_S = RgS->get_right(); // right son of RgS
			if ((P->get_color() == Color::red) && (S->get_color() == Color::black))
			{
				//case 1: red parent, black right child with black grandsons
				if ((LgS->get_color() == Color::black) && (RgS->get_color() == Color::black))
				{
					P->set_color(Color::black);
					S->set_color(Color::red);
					return;
				}
				//case 2: red parent, black right child with right red son
				if (RgS->get_color() == Color::red)
				{
					left_turn(P);
					P->set_color(Color::black);
					S->set_color(Color::red);
					RgS->set_color(Color::black);
					return;
				}
				else if (LgS->get_color() == Color::red)
					P->set_color(Color::black); // to get into the case 5
			}
			if (P->get_color() == Color::black)
			{
				if (S->get_color() == Color::red)
				{
					//case 3: black parent, red left son, LgS has black grandsons
					if ((L_LgS_S->get_color() == Color::black) && (R_LgS_S->get_color() == Color::black))
					{
						left_turn(P);
						S->set_color(Color::black);
						LgS->set_color(Color::red); // he was black like son of the red one
						return;
					}
					//case 4: black parent, red left son, LgS has right red son
					else if (R_LgS_S->get_color() == Color::red)
					{
						right_turn(S);
						left_turn(P);
						R_LgS_S->set_color(Color::black);
						return;
					}
				}
				else
				{
					//case 5: black parent, black right son with left red son
					if (LgS->get_color() == Color::red)
					{
						right_turn(S);
						left_turn(P);
						LgS->set_color(Color::black);
						return;
					}
					//case 6: black parent, black right son with black sons
					else if (RgS->get_color() == Color::black)
					{
						S->set_color(Color::red);
						restoring_propertires_after_delete(P);
						return;
					}
				}
			}
		}
	}

public:

	RB_Tree() 
	{
		Nil = new Node<Key_Type, Value_Type>;
		Nil->set_color(Color::black);
		set_root(get_Nil());
	}

	int get_size() { return size; }

	Node<Key_Type, Value_Type>* get_Nil() { return Nil; }

	Node<Key_Type, Value_Type>* get_root() { return root; }

	//finds node by it's key
	Node<Key_Type, Value_Type>* find(Key_Type required_key)
	{
		if (get_root() == get_Nil())
			throw out_of_range("search in the empty tree");
		Node<Key_Type, Value_Type>* current = root;
		while (current->get_key() != required_key)
		{
			if (required_key < current->get_key())
				current = current->get_left();
			else
				current = current->get_right();
			if (current == get_Nil())
				throw out_of_range("search by non-existent key");
		}
		return current;
	}

	//inserting node by it's key and value
	void insert(Key_Type new_key, Value_Type new_value)
	{
		size++;
		Node<Key_Type, Value_Type>* new_node = new Node<Key_Type, Value_Type>(new_key, new_value, Color::red, get_Nil(), get_Nil(), get_Nil());
		Node<Key_Type, Value_Type>* current = get_root();
		Node<Key_Type, Value_Type>* current_parent = get_Nil();
		while (current != get_Nil()) // search for parent of new node
		{
			current_parent = current;
			if (new_node->get_key() < current->get_key()) // choose branch
				current = current->get_left();
			else
				current = current->get_right(); 
		}
		new_node->set_parent(current_parent);
		if (current_parent == get_Nil()) // set new node like a son for his parent
			root = new_node; // root is red now and it's not right, but it will be fixed in restoring
		else if (new_node->get_key() < current_parent->get_key()) //choose for parent ehat son to set
			current_parent->set_left(new_node);
		else
			current_parent->set_right(new_node);
		restoring_propertires_after_insert(new_node); // fixes root's color, problem of two reds and of black height
	}

	//removing element by it's key
	void remove(Key_Type to_delete_key)
	{
		if (get_root() == get_Nil())
			throw out_of_range("remove from empty tree");
		Node<Key_Type, Value_Type>* D = find(to_delete_key); // node to delete = D
		size--;
		if ((D->get_left() != get_Nil()) && (D->get_right() != get_Nil())) // if D has two sons
		{ // search for max node in left branch for node to delete
			Node<Key_Type, Value_Type>* replace_D = D->get_left();
			while (replace_D->get_right() != get_Nil())
				replace_D = replace_D->get_right();
			D->set_key(replace_D->get_key()); // D won't be really deleted
			D->set_value(replace_D->get_value());
			D = replace_D; // replace_D will be really deleted, we've just changed data of nodes
		}
		// now D is a node that has 1 or 0 sons 
		if (D->get_color() == Color::black) // deleting node is black
		{
			if (((D->get_right() != get_Nil()) || (D->get_left() != get_Nil())))
			{//case 1: black node with one son (son is red because he is the only one)
				Node<Key_Type, Value_Type>* replace_D = D->get_right();
				D->set_right(get_Nil());
				if (replace_D == get_Nil())
				{
					replace_D = D->get_left();
					D->set_left(get_Nil());
				}
				D->set_key(replace_D->get_key()); // D won't be really deleted
				D->set_value(replace_D->get_value()); // exchange values and keys and delete node without sons
				delete replace_D;
				return;
			}
			else //case 2: deleting node is black without sons
			{ 
				if (D == get_root())
				{
					delete D;
					set_root(get_Nil());
				}
				else
				{
					// after deleting D the rule of the black height is broken
					restoring_propertires_after_delete(D);
					if (D->get_parent()->get_left() == D)
						D->get_parent()->set_left(get_Nil());
					else
						D->get_parent()->set_right(get_Nil());
					delete D;
				}
			}
		}
		else // deleting node is red, red node can't have 1 son
		{ // in this place after all we did, red node can have only 0 sons
			if (D->get_parent()->get_left() == D)
				D->get_parent()->set_left(get_Nil());
			else
				D->get_parent()->set_right(get_Nil());
			delete D;
		}
	}

	Iterator<Key_Type, Value_Type>* create_breadth_first_traverse_iterator() // to realise this method of passing through elements
	{ return new BreadthFirstTraverse_Iterator(get_root()); }

	class BreadthFirstTraverse_Iterator : public Iterator<Key_Type, Value_Type>
	{
	private:
		Node<Key_Type, Value_Type>* current;
		Queue<Key_Type, Value_Type> queue;
		Node<Key_Type, Value_Type>* Nil;
	public:
		BreadthFirstTraverse_Iterator(Node<Key_Type, Value_Type>* start)
		{
			Nil = start->get_parent(); // = root->parent = Nil of the tree
			current = start;
			queue.push(current);
		}
		bool has_next() override
		{ return (!queue.is_empty()); }
		Node<Key_Type, Value_Type>* next() override
		{
			if (queue.is_empty())
				return current = Nil;
			current = queue.top()->get_data();
			if (current->get_left() != Nil)
				queue.push(current->get_left());
			if (current->get_right() != Nil)
				queue.push(current->get_right());
			return queue.pop()->get_data();
		}
	};

	void print(string filename) //print pairs <key, value> in file with data filename
	{
		Iterator<Key_Type, Value_Type>* iterator = create_breadth_first_traverse_iterator();
		ofstream out(filename);
		out << "pairs <key, value>:" << endl;
		while (iterator->has_next())
		{
			Node<Key_Type, Value_Type>* now = new Node<Key_Type, Value_Type>(iterator->next());
			out << now->get_key() << ", " << now->get_value() << endl;
		}
		out.close();
	}

	void print() // print pairs <key, value> in console
	{
		Iterator<Key_Type, Value_Type>* iterator = create_breadth_first_traverse_iterator();
		cout << "pairs <key, value>:" << endl;
		while (iterator->has_next())
		{
			Node<Key_Type, Value_Type>* now = new Node<Key_Type, Value_Type>(iterator->next());
			cout << now->get_key() << ", " << now->get_value() << endl;
		}
	}

	//returning an array of keys in order of bft iterator
	Key_Type* get_keys()
	{
		Iterator<Key_Type, Value_Type>* iterator = create_breadth_first_traverse_iterator();
		Key_Type* keys = new Key_Type[get_size()];
		int i = 0;
		while (iterator->has_next())
		{
			keys[i] = iterator->next()->get_key();
			i++;
		}
		return keys;
	}

	//returning an array of values in order of bft iterator
	Value_Type* get_values()
	{
		Iterator<Key_Type, Value_Type>* iterator = create_breadth_first_traverse_iterator();
		Value_Type* values = new Value_Type[get_size()];
		int i = 0;
		while (iterator->has_next())
		{
			values[i] = iterator->next()->get_value();
			i++;
		}
		return values;
	}

	// removing all elements of the tree
	void clear(Node<Key_Type, Value_Type>* now = nullptr)
	{
		if (now == nullptr)
			now = get_root();
		if (get_root() == get_Nil())
			throw out_of_range("clearing empry tree");
		size--;
		if (now->get_left() != Nil)
			clear(now->get_left());
		if (now->get_right() != Nil)
			clear(now->get_right());
		delete now;
		if (size == 0)
			set_root(get_Nil());
	}
};