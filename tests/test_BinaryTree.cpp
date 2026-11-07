#include "BinaryTree.hpp"
#include <gtest/gtest.h>
TEST(BinaryTreeTest, create)
{
	BinaryTree<int, int> tree;
	EXPECT_EQ(tree.Height(), 0);
}