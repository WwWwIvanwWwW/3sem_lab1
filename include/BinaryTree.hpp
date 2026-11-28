#pragma once
#include <memory>
#include <sstream>
#include <string>

enum class Order { LNR, LRN, NLR, NRL, RLN, RNL };
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

	static constexpr char kOrders[][3] = {{'L', 'N', 'R'}, {'L', 'R', 'N'},
										  {'N', 'L', 'R'}, {'N', 'R', 'L'},
										  {'R', 'L', 'N'}, {'R', 'N', 'L'}};

	const BinaryNode *findNode(const Key &key) const
	{
		const BinaryNode *curr = root.get();
		while (curr) {
			if (key < curr->key)
				curr = curr->lchild.get();
			else if (curr->key < key)
				curr = curr->rchild.get();
			else
				return curr;
		}
		return nullptr;
	}

	void copySubtree(const BinaryNode *src,
					 std::unique_ptr<BinaryNode> &dst) const
	{
		if (!src)
			return;
		dst = std::make_unique<BinaryNode>(src->key, src->data);
		copySubtree(src->lchild.get(), dst->lchild);
		copySubtree(src->rchild.get(), dst->rchild);
	}

	std::size_t countNodes(const std::unique_ptr<BinaryNode> &node) const
	{
		if (!node)
			return 0;
		return 1 + countNodes(node->lchild) + countNodes(node->rchild);
	}

	bool removeImpl(std::unique_ptr<BinaryNode> &curr, const Key &key)
	{
		if (!curr)
			return false;

		if (key < curr->key)
			return removeImpl(curr->lchild, key);
		if (curr->key < key)
			return removeImpl(curr->rchild, key);

		if (!curr->lchild) {
			curr = std::move(curr->rchild);
			--size_;
		} else if (!curr->rchild) {
			curr = std::move(curr->lchild);
			--size_;
		} else {

			BinaryNode *succ = curr->rchild.get();
			while (succ->lchild)
				succ = succ->lchild.get();
			curr->key = succ->key;
			curr->data = succ->data;
			removeImpl(curr->rchild, succ->key);
		}
		return true;
	}
	int HeightImpl(const std::unique_ptr<BinaryNode> &node) const
	{
		if (!node)
			return 0;

		int leftHeight = HeightImpl(node->lchild);
		int rightHeight = HeightImpl(node->rchild);
		return 1 + std::max(leftHeight, rightHeight);
	}

	int TraversalImpl(std::ostream &os, Order format,
					  const std::unique_ptr<BinaryNode> &node) const
	{
		if (!node)
			return 1;

		for (char i : kOrders[static_cast<int>(format)]) {
			if (i == 'L')
				TraversalImpl(os, format, node->lchild);
			else if (i == 'R')
				TraversalImpl(os, format, node->rchild);
			else {
				os << node->data << ' ';
			}
		}
		return 0;
	}
	void rotateRight(std::unique_ptr<BinaryNode> &node)
	{
		if (!node || !node->lchild)
			return;

		std::unique_ptr<BinaryNode> newRoot = std::move(node->lchild);
		node->lchild = std::move(newRoot->rchild);
		newRoot->rchild = std::move(node);
		node = std::move(newRoot);
	}

	int toList(std::unique_ptr<BinaryNode> &root)
	{
		int count = 0;
		std::unique_ptr<BinaryNode> *curr = &root;

		while (*curr) {
			if ((*curr)->lchild) {
				rotateRight(*curr);
			} else {
				count++;
				curr = &((*curr)->rchild);
			}
		}
		return count;
	}

	void compress(BinaryNode *dummy, int count)
	{
		BinaryNode *scanner = dummy;
		for (int i = 0; i < count; ++i) {
			if (!scanner->rchild || !scanner->rchild->rchild)
				break;

			auto child = std::move(scanner->rchild);
			auto grandchild = std::move(child->rchild);

			child->rchild = std::move(grandchild->lchild);
			grandchild->lchild = std::move(child);
			scanner->rchild = std::move(grandchild);

			scanner = scanner->rchild.get();
		}
	}

	template <typename NewT, typename Func>
	void mapImpl(const std::unique_ptr<BinaryNode> &node,
				 BinaryTree<Key, NewT> &newTree, Func &&func) const
	{
		if (!node)
			return;

		mapImpl(node->lchild, newTree, func);
		newTree.Insert(node->key, func(node->data));
		mapImpl(node->rchild, newTree, func);
	}

  public:
	bool Insert(const Key &key, const T &value)
	{
		if (!root) {
			root = std::make_unique<BinaryNode>(key, value);
			++size_;
			return true;
		}

		BinaryNode *curr = root.get();

		while (true) {
			if (key < curr->key) {
				if (!curr->lchild) {
					curr->lchild = std::make_unique<BinaryNode>(key, value);
					++size_;
					return true;
				}
				curr = curr->lchild.get();
			} else if (curr->key < key) {
				if (!curr->rchild) {
					curr->rchild = std::make_unique<BinaryNode>(key, value);
					++size_;
					return true;
				}
				curr = curr->rchild.get();
			} else
				return false;
		}
	}

	const T *Find(const Key &key) const
	{
		const BinaryNode *node = findNode(key);
		return node ? &node->data : nullptr;
	}
	bool Remove(const Key &key) { return removeImpl(root, key); }

	int Height() const { return HeightImpl(root); }

	std::size_t Size() const { return size_; }

	int Traversal(std::string &str, Order format = Order::LNR) const
	{
		std::ostringstream oss;
		int result = TraversalImpl(oss, format, root);
		str = oss.str();
		return result;
	}

	int Balance()
	{
		if (!root)
			return 1;

		std::unique_ptr<BinaryNode> dummy =
			std::make_unique<BinaryNode>(Key{}, T{});
		dummy->rchild = std::move(root);

		int count = toList(dummy->rchild);

		int m = 0;
		int power = 1;
		while (power <= count) {
			m = power;
			power = power * 2 + 1;
		}

		compress(dummy.get(), count - m);

		while (m > 1) {
			m /= 2;
			compress(dummy.get(), m);
		}

		root = std::move(dummy->rchild);
		return 0;
	}

	template <typename Func> auto Map(Func &&func) const
	{
		using NewT = decltype(func(std::declval<const T &>()));
		BinaryTree<Key, NewT> newTree;
		mapImpl(root, newTree, func);
		return newTree;
	}

	BinaryTree Subtree(const Key &key) const
	{
		BinaryTree result;
		const BinaryNode *node = findNode(key);
		if (node) {
			copySubtree(node, result.root);
			result.size_ = countNodes(result.root);
		}
		return result;
	}

	bool isLeaf(BinaryNode *node)
	{
		if (!node)
			return false;

		return !node->lchild && !node->rchild;
	}
};