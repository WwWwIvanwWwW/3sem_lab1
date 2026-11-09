#include "BinaryTree.hpp"
#include <gtest/gtest.h>

TEST(BinaryTreeTest, DefaultConstructor)
{
	BinaryTree<int, int> tree;
	EXPECT_EQ(0u, tree.Size());
	EXPECT_EQ(0, tree.Height());
	EXPECT_FALSE(tree.Find(5));
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
	tree1.Insert(5);
	tree1.Insert(3);

	BinaryTree<int, int> tree2(std::move(tree1));
	EXPECT_EQ(2u, tree2.Size());
	EXPECT_TRUE(tree2.Find(5));
	EXPECT_TRUE(tree2.Find(3));
}

TEST(BinaryTreeTest, MoveAssignment)
{
	BinaryTree<int, int> tree1;
	tree1.Insert(5);

	BinaryTree<int, int> tree2;
	tree2 = std::move(tree1);
	EXPECT_EQ(1u, tree2.Size());
	EXPECT_TRUE(tree2.Find(5));
}

TEST(BinaryTreeTest, InsertSingleElement)
{
	BinaryTree<int, int> tree;
	EXPECT_TRUE(tree.Insert(5));
	EXPECT_EQ(1u, tree.Size());
}

TEST(BinaryTreeTest, InsertMultipleElements)
{
	BinaryTree<int, int> tree;
	EXPECT_TRUE(tree.Insert(5));
	EXPECT_TRUE(tree.Insert(3));
	EXPECT_TRUE(tree.Insert(7));
	EXPECT_EQ(3u, tree.Size());
}

TEST(BinaryTreeTest, InsertDuplicateElement)
{
	BinaryTree<int, int> tree;
	EXPECT_TRUE(tree.Insert(5));
	EXPECT_FALSE(tree.Insert(5));
	EXPECT_EQ(1u, tree.Size());
}

TEST(BinaryTreeTest, FindExistingElement)
{
	BinaryTree<int, int> tree;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);
	EXPECT_TRUE(tree.Find(5));
	EXPECT_TRUE(tree.Find(3));
	EXPECT_TRUE(tree.Find(7));
}

TEST(BinaryTreeTest, FindNonExistingElement)
{
	BinaryTree<int, int> tree;
	tree.Insert(5);
	tree.Insert(3);
	EXPECT_FALSE(tree.Find(7));
	EXPECT_FALSE(tree.Find(1));
}

TEST(BinaryTreeTest, FindInEmptyTree)
{
	BinaryTree<int, int> tree;
	EXPECT_FALSE(tree.Find(5));
}

TEST(BinaryTreeTest, RemoveLeafNode)
{
	BinaryTree<int, int> tree;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);
	EXPECT_TRUE(tree.Remove(3));
	EXPECT_EQ(2u, tree.Size());
	EXPECT_FALSE(tree.Find(3));
}

TEST(BinaryTreeTest, RemoveNodeWithOneChild)
{
	BinaryTree<int, int> tree;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(1);
	EXPECT_TRUE(tree.Remove(3));
	EXPECT_EQ(2u, tree.Size());
	EXPECT_FALSE(tree.Find(3));
	EXPECT_TRUE(tree.Find(1));
}

TEST(BinaryTreeTest, RemoveNodeWithTwoChildren)
{
	BinaryTree<int, int> tree;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);
	tree.Insert(6);
	EXPECT_TRUE(tree.Remove(7));
	EXPECT_EQ(3u, tree.Size());
	EXPECT_FALSE(tree.Find(7));
	EXPECT_TRUE(tree.Find(3));
	EXPECT_TRUE(tree.Find(5));
	EXPECT_TRUE(tree.Find(6));
}

TEST(BinaryTreeTest, RemoveNodeWithManyChildren)
{
	BinaryTree<int, int> tree;
	std::string str;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);
	tree.Insert(6);
	EXPECT_EQ(4u, tree.Size());
	EXPECT_TRUE(tree.Remove(5));
	tree.LNR(str);
	EXPECT_EQ("3 6 7 ", str);
	EXPECT_EQ(3u, tree.Size());
}

TEST(BinaryTreeTest, RemoveNonExistingElement)
{
	BinaryTree<int, int> tree;
	tree.Insert(5);
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
	tree.Insert(5);
	EXPECT_EQ(1, tree.Height());
}

TEST(BinaryTreeTest, HeightOfBalancedTree)
{
	BinaryTree<int, int> tree;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);
	EXPECT_EQ(2, tree.Height());
}

TEST(BinaryTreeTest, HeightOfUnbalancedTree)
{
	BinaryTree<int, int> tree;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(1);
	EXPECT_EQ(3, tree.Height());
}

TEST(BinaryTreeTest, LNREmptyTree)
{
	BinaryTree<int, int> tree;
	std::string str;
	tree.LNR(str);
	EXPECT_TRUE(str.empty());
}

TEST(BinaryTreeTest, LNRSingleElement)
{
	BinaryTree<int, int> tree;
	std::string str;
	tree.Insert(5);
	tree.LNR(str);
	EXPECT_EQ("5 ", str);
}

TEST(BinaryTreeTest, LNRMultipleElements)
{
	BinaryTree<int, int> tree;
	std::string str;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);
	tree.Insert(1);
	tree.Insert(4);
	tree.LNR(str);
	EXPECT_EQ("1 3 4 5 7 ", str);
}

TEST(BinaryTreeTest, SizeAfterOperations)
{
	BinaryTree<int, int> tree;
	EXPECT_EQ(0u, tree.Size());

	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);
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
		EXPECT_TRUE(tree.Insert(i));
	}
	EXPECT_EQ(10u, tree.Size());

	for (int i = 1; i <= 5; ++i) {
		EXPECT_TRUE(tree.Remove(i));
	}
	EXPECT_EQ(5u, tree.Size());

	for (int i = 6; i <= 10; ++i) {
		EXPECT_TRUE(tree.Find(i));
	}
}

TEST(BinaryTreeTest, InsertStringValues)
{
	BinaryTree<std::string, std::string> stringTree;
	EXPECT_TRUE(stringTree.Insert("hello"));
	EXPECT_TRUE(stringTree.Insert("world"));
	EXPECT_TRUE(stringTree.Find("hello"));
	EXPECT_TRUE(stringTree.Find("world"));
	EXPECT_FALSE(stringTree.Find("test"));
}