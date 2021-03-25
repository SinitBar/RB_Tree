#include "pch.h"
#include "CppUnitTest.h"
#include "../RB_Tree/RB_Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestRBTree
{
	TEST_CLASS(UnitTestRBTree)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1); // check assembly of the project
		}
		TEST_METHOD(TestNodeConstructorKey)
		{
			Node<int, int> node(10, 12, Color::red);
			Assert::IsTrue(node.get_key() == 10);
		}
		TEST_METHOD(TestNodeConstructorRed)
		{
			Node<int, int> node(10, 12);
			Assert::IsTrue(node.get_color() == Color::red);
			Assert::AreEqual(node.get_key(), 10);
		}

		TEST_METHOD(TestNodeConstructorColorBlack)
		{
			Node<int, int> node(10, 12, Color::black);
			Assert::IsTrue(node.get_color() == Color::black);
		}
		TEST_METHOD(TestNodeConstructorParent)
		{
			Node<int, int>* Parent = new Node<int, int>;
			Node<int, int> node(10, 12, Color::red, nullptr, nullptr, Parent);
			Assert::IsTrue(node.get_parent() == Parent);
		}
		TEST_METHOD(TestInsert)
		{
			RB_Tree<int, int> tree;
			tree.insert(5, 10); // key, value
			Assert::IsTrue((*tree.get_root()).get_color() == Color::black);
			Assert::AreEqual((*tree.get_root()).get_key(), 5);
		}
		TEST_METHOD(TestInsertSecondNodeRightColor)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>();
			tree->insert(5, 10); // key, value 
			tree->insert(8, 3);
			Node<int, int>* test = tree->get_root();
			Assert::IsTrue(test->get_right()->get_color() == Color::red);
		}
		TEST_METHOD(TestInsertSecondNodeLeftColor)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 10); // key, value
			tree->insert(1, 3);
			Node<int, int>* test = tree->get_root();
			Assert::IsTrue(test->get_left()->get_color() == Color::red);
		}
		TEST_METHOD(TestInsertThirdNodeColor)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 10); // key, value
			tree->insert(8, 3);
			tree->insert(1, 4);
			Node<int, int>* test = tree->get_root();
			Assert::IsTrue(test->get_left()->get_color() == Color::red);
		}
		TEST_METHOD(TestInsertLeftTurnCheck)
		{

			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 5); // key, value
			tree->insert(10, 10);
			tree->insert(12, 12);
			Assert::AreEqual(tree->get_root()->get_key(), 10);
			Assert::IsTrue(tree->get_root()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_left()->get_key(), 5);
			Assert::AreEqual(tree->get_root()->get_right()->get_key(), 12);
			Assert::IsTrue(tree->get_root()->get_left()->get_color() == Color::red);
			Assert::IsTrue(tree->get_root()->get_right()->get_color() == Color::red);
		}
		TEST_METHOD(TestInsertRightTurnCheck)
		{

			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 5); // key, value
			tree->insert(4, 4);
			tree->insert(3, 3);
			Assert::AreEqual(tree->get_root()->get_key(), 4);
		}
		TEST_METHOD(test_insert_1_2_3_4)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(1, 1); // key, value
			tree->insert(2, 2);
			tree->insert(3, 3);
			tree->insert(4, 4);
			Assert::AreEqual(tree->get_root()->get_key(), 2);
			Assert::IsTrue(tree->get_root()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_left()->get_key(), 1);
			Assert::IsTrue(tree->get_root()->get_left()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_right()->get_key(), 3);
			Assert::IsTrue(tree->get_root()->get_right()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_right()->get_right()->get_key(), 4);
			Assert::IsTrue(tree->get_root()->get_right()->get_right()->get_color() == Color::red);
		}

		TEST_METHOD(test_insert_1_2_3_4_5)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(1, 1); // key, value
			tree->insert(2, 2);
			tree->insert(3, 3);
			tree->insert(4, 4);
			tree->insert(5, 5);
			Assert::AreEqual(tree->get_root()->get_key(), 2);
			Assert::IsTrue(tree->get_root()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_left()->get_key(), 1);
			Assert::IsTrue(tree->get_root()->get_left()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_right()->get_key(), 4);
			Assert::IsTrue(tree->get_root()->get_right()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_right()->get_right()->get_key(), 5);
			Assert::IsTrue(tree->get_root()->get_right()->get_right()->get_color() == Color::red);
			Assert::AreEqual(tree->get_root()->get_right()->get_left()->get_key(), 3);
			Assert::IsTrue(tree->get_root()->get_right()->get_left()->get_color() == Color::red);
		}

		TEST_METHOD(test_insert_1_2_3_4_5_6)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(1, 1); // key, value
			tree->insert(2, 2);
			tree->insert(3, 3);
			tree->insert(4, 4);
			tree->insert(5, 5);
			tree->insert(6, 6);
			Assert::AreEqual(tree->get_root()->get_key(), 2);
			Assert::IsTrue(tree->get_root()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_left()->get_key(), 1);
			Assert::IsTrue(tree->get_root()->get_left()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_right()->get_key(), 4);
			Assert::IsTrue(tree->get_root()->get_right()->get_color() == Color::red);
			Assert::AreEqual(tree->get_root()->get_right()->get_right()->get_key(), 5);
			Assert::IsTrue(tree->get_root()->get_right()->get_right()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_right()->get_left()->get_key(), 3);
			Assert::IsTrue(tree->get_root()->get_right()->get_left()->get_color() == Color::black);
			Assert::AreEqual(tree->get_root()->get_right()->get_right()->get_right()->get_key(), 6);
			Assert::IsTrue(tree->get_root()->get_right()->get_right()->get_right()->get_color() == Color::red);
		}
		TEST_METHOD(BigInsert)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 5); // key, value
			tree->insert(10, 10);
			tree->insert(12, 12);
			tree->insert(14, 14);
			tree->insert(7, 7);
			tree->insert(11, 11);
			tree->insert(19, 19);
			tree->insert(3, 3);
			tree->insert(8, 8);
			tree->insert(6, 6);
			Assert::AreEqual(tree->get_root()->get_key(), 10);
		}

		TEST_METHOD(test_delete_root)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 5); // key, value
			tree->remove(5);
			Assert::IsTrue(tree->get_root() == tree->get_Nil());
		}
		TEST_METHOD(test_delete_root_two_nodes_in_tree)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 5); // key, value
			tree->insert(3, 3);
			tree->remove(5);
			Assert::AreEqual(tree->get_root()->get_key(), 3);
			Assert::IsTrue((tree->get_root()->get_left() == tree->get_Nil()) && (tree->get_root()->get_right() == tree->get_Nil()));
		}
		TEST_METHOD(test_delete_not_root_two_nodes_in_tree)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 5); // key, value
			tree->insert(3, 3);
			tree->remove(3);
			Assert::AreEqual(tree->get_root()->get_key(), 5);
			Assert::IsTrue((tree->get_root()->get_left() == tree->get_Nil()) && (tree->get_root()->get_right() == tree->get_Nil()));
		}
		TEST_METHOD(test_delete_root_two_nodes_in_tree_right_child)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 5); // key, value
			tree->insert(7, 7);
			tree->remove(5);
			Assert::AreEqual(tree->get_root()->get_key(), 7);
			Assert::IsTrue((tree->get_root()->get_left() == tree->get_Nil()) && (tree->get_root()->get_right() == tree->get_Nil()));
		}
		TEST_METHOD(test_delete_not_root_two_nodes_in_tree_right_child)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(5, 5); // key, value
			tree->insert(7, 7);
			tree->remove(7);
			Assert::AreEqual(tree->get_root()->get_key(), 5);
			Assert::IsTrue((tree->get_root()->get_left() == tree->get_Nil()) && (tree->get_root()->get_right() == tree->get_Nil()));
		}
		TEST_METHOD(iterator_test)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(1, 1); // key, value
			tree->insert(2, 2);
			tree->insert(3, 3);
			tree->insert(4, 4);
			tree->insert(5, 5);
			tree->insert(6, 6);
			Iterator<int, int>* iterator = tree->create_breadth_first_traverse_iterator();
			if (iterator->has_next())
				Assert::AreEqual(iterator->next()->get_key(), 2);
			if (iterator->has_next())
				Assert::AreEqual(iterator->next()->get_key(), 1);
			if (iterator->has_next())
				Assert::AreEqual(iterator->next()->get_key(), 4);
			if (iterator->has_next())
				Assert::AreEqual(iterator->next()->get_key(), 3);
			if (iterator->has_next())
				Assert::AreEqual(iterator->next()->get_key(), 5);
			if (iterator->has_next())
				Assert::AreEqual(iterator->next()->get_key(), 6);
			Assert::AreEqual(iterator->has_next(), false);
		}
		TEST_METHOD(print_test)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(1, 1); // key, value
			tree->insert(2, 2);
			tree->insert(3, 3);
			tree->insert(4, 4);
			tree->insert(5, 5);
			tree->insert(6, 6);
			tree->print("../out.txt"); // check file "..UnitTest_RB_Tree/out.txt"
			tree->print();
			Assert::IsTrue(true);
		}

		TEST_METHOD(get_keys_test)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(1, 1); // key, value
			tree->insert(2, 2);
			tree->insert(3, 3);
			tree->insert(4, 4);
			tree->insert(5, 5);
			tree->insert(6, 6);
			int* keys = tree->get_keys();
			Assert::AreEqual(keys[0], 2);
			Assert::AreEqual(keys[1], 1);
			Assert::AreEqual(keys[2], 4);
			Assert::AreEqual(keys[3], 3);
			Assert::AreEqual(keys[4], 5);
			Assert::AreEqual(keys[5], 6);
		}

		TEST_METHOD(get_values_test)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(1, 1); // key, value
			tree->insert(2, 2);
			tree->insert(3, 3);
			tree->insert(4, 4);
			tree->insert(5, 5);
			tree->insert(6, 6);
			int* values = tree->get_values();
			Assert::AreEqual(values[0], 2);
			Assert::AreEqual(values[1], 1);
			Assert::AreEqual(values[2], 4);
			Assert::AreEqual(values[3], 3);
			Assert::AreEqual(values[4], 5);
			Assert::AreEqual(values[5], 6);
		}

		TEST_METHOD(clear_test)
		{
			RB_Tree<int, int>* tree = new RB_Tree<int, int>;
			tree->insert(1, 1); // key, value
			tree->insert(2, 2);
			tree->insert(3, 3);
			tree->insert(4, 4);
			tree->insert(5, 5);
			tree->insert(6, 6);
			tree->clear();
			Assert::IsTrue(tree->get_root() == tree->get_Nil());
		}
	};
}