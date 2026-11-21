#include "BinaryTree.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(BinaryTreeTest, DefaultConstructor)
{
	BinaryTree<int, int> tree;
	EXPECT_EQ(0u, tree.Size());
	EXPECT_EQ(0, tree.Height());
	EXPECT_EQ(nullptr, tree.Find(5));
}

TEST(BinaryTreeTest, ConstructorWithDifferentTypes)
{
	BinaryTree<std::string, double> stringDoubleTree;
	EXPECT_EQ(0u, stringDoubleTree.Size());

	BinaryTree<char, int> charIntTree;
	EXPECT_EQ(0u, charIntTree.Size());
}

TEST(BinaryTreeTest, MoveConstructor)
{
	BinaryTree<int, int> tree1;
	tree1.Insert(5, 5);
	tree1.Insert(3, 3);

	BinaryTree<int, int> tree2(std::move(tree1));
	EXPECT_EQ(2u, tree2.Size());
	EXPECT_NE(nullptr, tree2.Find(5));
	EXPECT_NE(nullptr, tree2.Find(3));
}

TEST(BinaryTreeTest, MoveAssignment)
{
	BinaryTree<int, int> tree1;
	tree1.Insert(5, 5);

	BinaryTree<int, int> tree2;
	tree2 = std::move(tree1);
	EXPECT_EQ(1u, tree2.Size());
	EXPECT_NE(nullptr, tree2.Find(5));
}

TEST(BinaryTreeTest, InsertSingleElement)
{
	BinaryTree<int, int> tree;
	EXPECT_TRUE(tree.Insert(5, 5));
	EXPECT_EQ(1u, tree.Size());
}

TEST(BinaryTreeTest, InsertMultipleElements)
{
	BinaryTree<int, int> tree;
	EXPECT_TRUE(tree.Insert(5, 5));
	EXPECT_TRUE(tree.Insert(3, 3));
	EXPECT_TRUE(tree.Insert(7, 7));
	EXPECT_EQ(3u, tree.Size());
}

TEST(BinaryTreeTest, InsertDuplicateElement)
{
	BinaryTree<int, int> tree;
	EXPECT_TRUE(tree.Insert(5, 5));
	EXPECT_FALSE(tree.Insert(5, 10));
	EXPECT_EQ(1u, tree.Size());
}

TEST(BinaryTreeTest, FindExistingElement)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 50);
	tree.Insert(3, 30);
	tree.Insert(7, 70);

	const int *val5 = tree.Find(5);
	const int *val3 = tree.Find(3);
	const int *val7 = tree.Find(7);

	ASSERT_NE(nullptr, val5);
	EXPECT_EQ(50, *val5);

	ASSERT_NE(nullptr, val3);
	EXPECT_EQ(30, *val3);

	ASSERT_NE(nullptr, val7);
	EXPECT_EQ(70, *val7);
}

TEST(BinaryTreeTest, FindNonExistingElement)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	EXPECT_EQ(nullptr, tree.Find(7));
	EXPECT_EQ(nullptr, tree.Find(1));
}

TEST(BinaryTreeTest, FindInEmptyTree)
{
	BinaryTree<int, int> tree;
	EXPECT_EQ(nullptr, tree.Find(5));
}

TEST(BinaryTreeTest, RemoveLeafNode)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	EXPECT_TRUE(tree.Remove(3));
	EXPECT_EQ(2u, tree.Size());
	EXPECT_EQ(nullptr, tree.Find(3));
}

TEST(BinaryTreeTest, RemoveNodeWithOneChild)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(1, 1);
	EXPECT_TRUE(tree.Remove(3));
	EXPECT_EQ(2u, tree.Size());
	EXPECT_EQ(nullptr, tree.Find(3));
	EXPECT_NE(nullptr, tree.Find(1));
}

TEST(BinaryTreeTest, RemoveNodeWithTwoChildren)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(6, 6);
	EXPECT_TRUE(tree.Remove(7));
	EXPECT_EQ(3u, tree.Size());
	EXPECT_EQ(nullptr, tree.Find(7));
	EXPECT_NE(nullptr, tree.Find(3));
	EXPECT_NE(nullptr, tree.Find(5));
	EXPECT_NE(nullptr, tree.Find(6));
}

TEST(BinaryTreeTest, RemoveNodeWithManyChildren)
{
	BinaryTree<int, int> tree;
	std::string str;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(6, 6);
	EXPECT_EQ(4u, tree.Size());
	EXPECT_TRUE(tree.Remove(5));
	tree.Traversal(str);
	EXPECT_EQ("3 6 7 ", str);
	EXPECT_EQ(3u, tree.Size());
}

TEST(BinaryTreeTest, RemoveNonExistingElement)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	EXPECT_FALSE(tree.Remove(3));
	EXPECT_EQ(1u, tree.Size());
}

TEST(BinaryTreeTest, RemoveFromEmptyTree)
{
	BinaryTree<int, int> tree;
	EXPECT_FALSE(tree.Remove(5));
}

TEST(BinaryTreeTest, HeightOfEmptyTree)
{
	BinaryTree<int, int> tree;
	EXPECT_EQ(0, tree.Height());
}

TEST(BinaryTreeTest, HeightOfSingleNode)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	EXPECT_EQ(1, tree.Height());
}

TEST(BinaryTreeTest, HeightOfBalancedTree)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	EXPECT_EQ(2, tree.Height());
}

TEST(BinaryTreeTest, HeightOfUnbalancedTree)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(1, 1);
	EXPECT_EQ(3, tree.Height());
}

TEST(BinaryTreeTest, TraversalEmptyTree)
{
	BinaryTree<int, int> tree;
	std::string str;

	EXPECT_EQ(1, tree.Traversal(str, Order::LNR));
	EXPECT_TRUE(str.empty());

	EXPECT_EQ(1, tree.Traversal(str, Order::NLR));
	EXPECT_TRUE(str.empty());
}

TEST(BinaryTreeTest, TraversalSingleNode)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	std::string str;

	EXPECT_EQ(0, tree.Traversal(str, Order::LNR));
	EXPECT_EQ("5 ", str);

	EXPECT_EQ(0, tree.Traversal(str, Order::NLR));
	EXPECT_EQ("5 ", str);
}

TEST(BinaryTreeTest, TraversalLNR)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);
	tree.Insert(6, 6);
	tree.Insert(8, 8);

	std::string str;
	tree.Traversal(str, Order::LNR);
	EXPECT_EQ("1 3 4 5 6 7 8 ", str);
}

TEST(BinaryTreeTest, TraversalLRN)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);
	tree.Insert(6, 6);
	tree.Insert(8, 8);

	std::string str;
	tree.Traversal(str, Order::LRN);
	EXPECT_EQ("1 4 3 6 8 7 5 ", str);
}

TEST(BinaryTreeTest, TraversalNLR)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);
	tree.Insert(6, 6);
	tree.Insert(8, 8);

	std::string str;
	tree.Traversal(str, Order::NLR);
	EXPECT_EQ("5 3 1 4 7 6 8 ", str);
}

TEST(BinaryTreeTest, TraversalNRL)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);
	tree.Insert(6, 6);
	tree.Insert(8, 8);

	std::string str;
	tree.Traversal(str, Order::NRL);
	EXPECT_EQ("5 7 8 6 3 4 1 ", str);
}

TEST(BinaryTreeTest, TraversalRLN)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);
	tree.Insert(6, 6);
	tree.Insert(8, 8);

	std::string str;
	tree.Traversal(str, Order::RLN);
	EXPECT_EQ("8 6 7 4 1 3 5 ", str);
}

TEST(BinaryTreeTest, TraversalRNL)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);
	tree.Insert(6, 6);
	tree.Insert(8, 8);

	std::string str;
	tree.Traversal(str, Order::RNL);
	EXPECT_EQ("8 7 6 5 4 3 1 ", str);
}

TEST(BinaryTreeTest, TraversalDefaultOrder)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);

	std::string str;
	tree.Traversal(str);
	EXPECT_EQ("3 5 7 ", str);
}

TEST(BinaryTreeTest, TraversalWithDifferentValues)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 50);
	tree.Insert(3, 30);
	tree.Insert(7, 70);
	tree.Insert(1, 10);
	tree.Insert(4, 40);

	std::string str;
	tree.Traversal(str, Order::LNR);
	EXPECT_EQ("10 30 40 50 70 ", str);
}

TEST(BinaryTreeTest, TraversalStringValues)
{
	BinaryTree<int, std::string> tree;
	tree.Insert(2, "two");
	tree.Insert(1, "one");
	tree.Insert(3, "three");

	std::string str;
	tree.Traversal(str, Order::LNR);
	EXPECT_EQ("one two three ", str);

	tree.Traversal(str, Order::NLR);
	EXPECT_EQ("two one three ", str);
}

TEST(BinaryTreeTest, TraversalUnbalancedTree)
{
	BinaryTree<int, int> tree;
	tree.Insert(1, 1);
	tree.Insert(2, 2);
	tree.Insert(3, 3);
	tree.Insert(4, 4);

	std::string str;
	tree.Traversal(str, Order::LNR);
	EXPECT_EQ("1 2 3 4 ", str);

	tree.Traversal(str, Order::RNL);
	EXPECT_EQ("4 3 2 1 ", str);
}

TEST(BinaryTreeTest, TraversalAfterBalance)
{
	BinaryTree<int, int> tree;
	tree.Insert(1, 1);
	tree.Insert(2, 2);
	tree.Insert(3, 3);
	tree.Insert(4, 4);
	tree.Insert(5, 5);

	tree.Balance();

	std::string str;
	tree.Traversal(str, Order::LNR);
	EXPECT_EQ("1 2 3 4 5 ", str);
}

TEST(BinaryTreeTest, TraversalAfterRemove)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);

	tree.Remove(3);

	std::string str;
	tree.Traversal(str, Order::LNR);
	EXPECT_EQ("1 4 5 7 ", str);
}

TEST(BinaryTreeTest, SizeAfterOperations)
{
	BinaryTree<int, int> tree;
	EXPECT_EQ(0u, tree.Size());

	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	EXPECT_EQ(3u, tree.Size());

	tree.Remove(3);
	EXPECT_EQ(2u, tree.Size());

	tree.Remove(5);
	EXPECT_EQ(1u, tree.Size());

	tree.Remove(7);
	EXPECT_EQ(0u, tree.Size());
}

TEST(BinaryTreeTest, ComplexInsertAndRemove)
{
	BinaryTree<int, int> tree;
	for (int i = 1; i <= 10; ++i) {
		EXPECT_TRUE(tree.Insert(i, i * 10));
	}
	EXPECT_EQ(10u, tree.Size());

	for (int i = 1; i <= 5; ++i) {
		EXPECT_TRUE(tree.Remove(i));
	}
	EXPECT_EQ(5u, tree.Size());

	for (int i = 6; i <= 10; ++i) {
		EXPECT_NE(nullptr, tree.Find(i));
	}
}

TEST(BinaryTreeTest, InsertStringValues)
{
	BinaryTree<std::string, std::string> stringTree;
	EXPECT_TRUE(stringTree.Insert("hello", "world"));
	EXPECT_TRUE(stringTree.Insert("foo", "bar"));
	EXPECT_NE(nullptr, stringTree.Find("hello"));
	EXPECT_NE(nullptr, stringTree.Find("foo"));
	EXPECT_EQ(nullptr, stringTree.Find("test"));
}

TEST(BinaryTreeTest, BalanceEmptyTree)
{
	BinaryTree<int, int> tree;
	tree.Balance();
	EXPECT_EQ(0u, tree.Size());
	EXPECT_EQ(0, tree.Height());
}

TEST(BinaryTreeTest, BalanceSingleNode)
{
	BinaryTree<int, int> tree;
	tree.Insert(1, 1);
	tree.Balance();
	EXPECT_EQ(1u, tree.Size());
	EXPECT_EQ(1, tree.Height());
	EXPECT_NE(nullptr, tree.Find(1));
}

TEST(BinaryTreeTest, BalanceUnbalancedRightSkewed)
{
	BinaryTree<int, int> tree;
	for (int i = 1; i <= 5; ++i) {
		tree.Insert(i, i);
	}

	EXPECT_EQ(5, tree.Height());

	tree.Balance();

	EXPECT_LE(tree.Height(), 3);
	EXPECT_EQ(5u, tree.Size());

	for (int i = 1; i <= 5; ++i) {
		EXPECT_NE(nullptr, tree.Find(i));
	}
}

TEST(BinaryTreeTest, BalanceUnbalancedLeftSkewed)
{
	BinaryTree<int, int> tree;
	for (int i = 5; i >= 1; --i) {
		tree.Insert(i, i);
	}

	EXPECT_EQ(5, tree.Height());

	tree.Balance();

	EXPECT_LE(tree.Height(), 3);
	EXPECT_EQ(5u, tree.Size());

	for (int i = 1; i <= 5; ++i) {
		EXPECT_NE(nullptr, tree.Find(i));
	}
}

TEST(BinaryTreeTest, BalancePreservesInOrderTraversal)
{
	BinaryTree<int, int> tree;
	std::string strBefore, strAfter;

	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);
	tree.Insert(6, 6);
	tree.Insert(8, 8);

	tree.Traversal(strBefore);

	tree.Balance();

	tree.Traversal(strAfter);

	EXPECT_EQ(strBefore, strAfter);
	EXPECT_EQ("1 3 4 5 6 7 8 ", strAfter);
}

TEST(BinaryTreeTest, BalanceAlreadyBalancedTree)
{
	BinaryTree<int, int> tree;

	tree.Insert(4, 4);
	tree.Insert(2, 2);
	tree.Insert(6, 6);
	tree.Insert(1, 1);
	tree.Insert(3, 3);
	tree.Insert(5, 5);
	tree.Insert(7, 7);

	int heightBefore = tree.Height();

	tree.Balance();

	EXPECT_LE(tree.Height(), heightBefore);
	EXPECT_EQ(7u, tree.Size());

	for (int i = 1; i <= 7; ++i) {
		EXPECT_NE(nullptr, tree.Find(i));
	}
}

TEST(BinaryTreeTest, BalanceComplexCase)
{
	BinaryTree<int, int> tree;

	std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
	for (int val : values) {
		tree.Insert(val, val * 10);
	}

	EXPECT_EQ(11u, tree.Size());

	tree.Balance();

	EXPECT_EQ(11u, tree.Size());

	for (int val : values) {
		EXPECT_NE(nullptr, tree.Find(val));
	}

	EXPECT_LE(tree.Height(), 4);
}

TEST(BinaryTreeTest, MapEmptyTree)
{
	BinaryTree<int, int> tree;
	auto newTree = tree.Map([](const int &val) { return val * 2; });

	EXPECT_EQ(0u, newTree.Size());
	EXPECT_EQ(0, newTree.Height());
}

TEST(BinaryTreeTest, MapSingleElement)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 10);

	auto newTree = tree.Map([](const int &val) { return val * 2; });

	EXPECT_EQ(1u, newTree.Size());
	EXPECT_NE(nullptr, newTree.Find(5));
}

TEST(BinaryTreeTest, MapMultipleElements)
{
	BinaryTree<int, int> tree;
	tree.Insert(3, 30);
	tree.Insert(1, 10);
	tree.Insert(5, 50);

	auto newTree = tree.Map([](const int &val) { return val + 100; });

	EXPECT_EQ(3u, newTree.Size());
	EXPECT_NE(nullptr, newTree.Find(1));
	EXPECT_NE(nullptr, newTree.Find(3));
	EXPECT_NE(nullptr, newTree.Find(5));
}

TEST(BinaryTreeTest, MapChangeType)
{
	BinaryTree<int, int> tree;
	tree.Insert(1, 1);
	tree.Insert(2, 2);
	tree.Insert(3, 3);

	auto newTree = tree.Map(
		[](const int &val) -> std::string { return std::to_string(val); });

	EXPECT_EQ(3u, newTree.Size());
	EXPECT_NE(nullptr, newTree.Find(1));
	EXPECT_NE(nullptr, newTree.Find(2));
	EXPECT_NE(nullptr, newTree.Find(3));
}

TEST(BinaryTreeTest, MapPreservesStructure)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);

	std::string originalStr, mappedStr;
	tree.Traversal(originalStr);

	auto newTree = tree.Map([](const int &val) { return val * 10; });
	newTree.Traversal(mappedStr);

	EXPECT_EQ("1 3 4 5 7 ", originalStr);
	EXPECT_EQ("10 30 40 50 70 ", mappedStr);
}

TEST(BinaryTreeTest, MapIntToString)
{
	BinaryTree<int, int> tree;
	tree.Insert(1, 10);
	tree.Insert(2, 20);
	tree.Insert(3, 30);

	auto newTree = tree.Map([](const int &val) -> std::string {
		return "Value: " + std::to_string(val);
	});

	EXPECT_EQ(3u, newTree.Size());
	EXPECT_NE(nullptr, newTree.Find(1));
	EXPECT_NE(nullptr, newTree.Find(2));
	EXPECT_NE(nullptr, newTree.Find(3));
}

TEST(BinaryTreeTest, MapStringToInt)
{
	BinaryTree<std::string, std::string> tree;
	tree.Insert("a", "hello");
	tree.Insert("b", "world");

	auto newTree = tree.Map([](const std::string &val) -> int {
		return static_cast<int>(val.length());
	});

	EXPECT_EQ(2u, newTree.Size());
	EXPECT_NE(nullptr, newTree.Find("a"));
	EXPECT_NE(nullptr, newTree.Find("b"));
}

TEST(BinaryTreeTest, SubtreeExistingKey)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);
	tree.Insert(1, 1);
	tree.Insert(4, 4);
	tree.Insert(6, 6);
	tree.Insert(8, 8);

	BinaryTree<int, int> sub = tree.Subtree(3);

	EXPECT_EQ(3u, sub.Size());
	EXPECT_NE(nullptr, sub.Find(3));
	EXPECT_NE(nullptr, sub.Find(1));
	EXPECT_NE(nullptr, sub.Find(4));
	EXPECT_EQ(nullptr, sub.Find(5));
	EXPECT_EQ(nullptr, sub.Find(7));
}

TEST(BinaryTreeTest, SubtreeRoot)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(7, 7);

	BinaryTree<int, int> sub = tree.Subtree(5);

	EXPECT_EQ(3u, sub.Size());
	EXPECT_NE(nullptr, sub.Find(5));
	EXPECT_NE(nullptr, sub.Find(3));
	EXPECT_NE(nullptr, sub.Find(7));
}

TEST(BinaryTreeTest, SubtreeLeaf)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);
	tree.Insert(1, 1);

	BinaryTree<int, int> sub = tree.Subtree(1);

	EXPECT_EQ(1u, sub.Size());
	EXPECT_NE(nullptr, sub.Find(1));
	EXPECT_EQ(nullptr, sub.Find(3));
}

TEST(BinaryTreeTest, SubtreeNonExistingKey)
{
	BinaryTree<int, int> tree;
	tree.Insert(5, 5);
	tree.Insert(3, 3);

	BinaryTree<int, int> sub = tree.Subtree(10);

	EXPECT_EQ(0u, sub.Size());
	EXPECT_EQ(0, sub.Height());
}

TEST(BinaryTreeTest, SubtreeEmptyTree)
{
	BinaryTree<int, int> tree;
	BinaryTree<int, int> sub = tree.Subtree(5);

	EXPECT_EQ(0u, sub.Size());
}