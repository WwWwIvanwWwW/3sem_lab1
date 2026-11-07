#pragma once
#include <memory>
#include <string>
template <typename Key, typename T> class BinaryTree
{
  private:
	struct BinaryNode {
		Key key;
		T data;
		std::unique_ptr<BinaryNode> lchild;
		std::unique_ptr<BinaryNode> rchild;
		BinaryNode(const Key &k, const T &value)
			: key(k), data(value), lchild(nullptr), rchild(nullptr)
		{
		}
	};
	std::unique_ptr<BinaryNode> root;
	std::size_t size_ = 0;

	bool removeImpl(std::unique_ptr<BinaryNode> &curr, const T &value)
	{
		if (!curr)
			return false;

		if (value < curr->data)
			return removeImpl(curr->lchild, value);
		if (curr->data < value)
			return removeImpl(curr->rchild, value);

		if (!curr->lchild) {
			curr = std::move(curr->rchild);
		} else if (!curr->rchild) {
			curr = std::move(curr->lchild);
		} else {

			BinaryNode *succ = curr->rchild.get();
			while (succ->lchild)
				succ = succ->lchild.get();
			curr->data = succ->data;
			removeImpl(curr->rchild, succ->data);
		}
		--size_;
		return true;
	}
	int HeightImpl(const std::unique_ptr<BinaryNode> &node)
	{
		if (!node)
			return 0;

		int leftHeight = HeightImpl(node->lchild);
		int rightHeight = HeightImpl(node->rchild);
		return 1 + std::max(leftHeight, rightHeight);
	}

  public:
	[[nodiscard]] bool Insert(const T &value)
	{
		if (!root) {
			root = std::make_unique<BinaryNode>(value);
			++size_;
			return true;
		}

		BinaryNode *curr = root.get();

		while (true) {
			if (value < curr->data) {
				if (!curr->lchild) {
					curr->lchild = std::make_unique<BinaryNode>(value);
					++size_;
					return true;
				}
				curr = curr->lchild.get();
			} else if (curr->data < value) {
				if (!curr->rchild) {
					curr->rchild = std::make_unique<BinaryNode>(value);
					++size_;
					return true;
				}
				curr = curr->rchild.get();
			} else
				return false;
		}
	}

	[[nodiscard]] bool Find(const T &value) const
	{
		if (!root) {
			return false;
		}

		const BinaryNode *curr = root.get();

		while (true) {
			if (value < curr->data) {
				if (!curr->lchild) {
					return false;
				}
				curr = curr->lchild.get();
			} else if (curr->data < value) {
				if (!curr->rchild) {
					return false;
				}
				curr = curr->rchild.get();
			} else
				return true;
		}
	}
	[[nodiscard]] bool Remove(const T &value)
	{
		return removeImpl(root, value);
	}

	[[nodiscard]] int Height() { return HeightImpl(root); }

	int LNR(const std::unique_ptr<BinaryNode> &node, std::string &str)
	{
		if (node == nullptr)
			return 0;

		LNR(node->lchild, &str);
		str += std::to_string(node->data) + " ";
		LNR(node->rchild, &str);
		return 0;
	}
};