#include "BinaryTree.hpp"
#include <iostream>
#include <limits>
#include <string>

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string &prompt)
{
	int value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value)
			break;
		std::cout << "Некорректный ввод. Попробуйте снова.\n";
		clearInput();
	}
	return value;
}

Order readOrder()
{
	std::cout << "Выберите обход:\n";
	std::cout << "  1 - LNR (симметричный)\n";
	std::cout << "  2 - LRN (обратный)\n";
	std::cout << "  3 - NLR (прямой)\n";
	std::cout << "  4 - NRL\n";
	std::cout << "  5 - RLN\n";
	std::cout << "  6 - RNL\n";

	int choice = readInt("Ваш выбор: ");
	switch (choice) {
	case 1:
		return Order::LNR;
	case 2:
		return Order::LRN;
	case 3:
		return Order::NLR;
	case 4:
		return Order::NRL;
	case 5:
		return Order::RLN;
	case 6:
		return Order::RNL;
	default:
		std::cout << "Неизвестный обход, использую LNR.\n";
		return Order::LNR;
	}
}

void printTreeInfo(const BinaryTree<int, int> &tree)
{
	std::cout << "Размер: " << tree.Size() << "\n";
	std::cout << "Высота: " << tree.Height() << "\n";

	std::string str;
	tree.Traversal(str, Order::LNR);
	std::cout << "LNR:    " << str << "\n";
}

int main()
{
	BinaryTree<int, int> tree;
	bool running = true;

	while (running) {
		std::cout << "\n===== Бинарное дерево =====\n";
		std::cout << " 1. Вставить элемент\n";
		std::cout << " 2. Найти элемент\n";
		std::cout << " 3. Удалить элемент\n";
		std::cout << " 4. Обход дерева\n";
		std::cout << " 5. Высота и размер\n";
		std::cout << " 6. Балансировка\n";
		std::cout << " 7. Извлечь поддерево\n";
		std::cout << " 8. Map (x2, x^2, +N)\n";
		std::cout << " 9. Показать дерево (все обходы)\n";
		std::cout << " 0. Выход\n";

		int choice = readInt("Выберите операцию: ");

		switch (choice) {

		case 1: {
			int key = readInt("Ключ: ");
			int value = readInt("Значение: ");
			if (tree.Insert(key, value))
				std::cout << "Элемент вставлен.\n";
			else
				std::cout << "Ключ уже существует.\n";
			break;
		}

		case 2: {
			int key = readInt("Ключ для поиска: ");
			const int *result = tree.Find(key);
			if (result)
				std::cout << "Найден: " << *result << "\n";
			else
				std::cout << "Не найден.\n";
			break;
		}

		case 3: {
			int key = readInt("Ключ для удаления: ");
			if (tree.Remove(key))
				std::cout << "Удалён.\n";
			else
				std::cout << "Не найден.\n";
			break;
		}

		case 4: {
			Order order = readOrder();
			std::string str;
			tree.Traversal(str, order);
			std::cout << "Результат: " << str << "\n";
			break;
		}

		case 5: {
			printTreeInfo(tree);
			break;
		}

		case 6: {
			if (tree.Balance() == 0) {
				std::cout << "Дерево сбалансировано.\n";
				printTreeInfo(tree);
			} else {
				std::cout << "Дерево пусто.\n";
			}
			break;
		}

		case 7: {
			int key = readInt("Ключ корня поддерева: ");
			BinaryTree<int, int> sub = tree.Subtree(key);
			if (sub.Size() == 0) {
				std::cout << "Узел не найден.\n";
			} else {
				std::cout << "Поддерево извлечено:\n";
				printTreeInfo(sub);
			}
			break;
		}

		case 8: {
			std::cout << "Операция над значениями:\n";
			std::cout << "  1 - Умножить на 2\n";
			std::cout << "  2 - Возвести в квадрат\n";
			std::cout << "  3 - Прибавить N\n";

			int op = readInt("Выбор: ");
			BinaryTree<int, int> mapped;

			if (op == 1) {
				mapped = tree.Map([](const int &v) { return v * 2; });
			} else if (op == 2) {
				mapped = tree.Map([](const int &v) { return v * v; });
			} else if (op == 3) {
				int n = readInt("Прибавить: ");
				mapped = tree.Map([n](const int &v) { return v + n; });
			} else {
				std::cout << "Неизвестная операция.\n";
				break;
			}

			std::cout << "Результат:\n";
			printTreeInfo(mapped);
			break;
		}

		case 9: {
			if (tree.Size() == 0) {
				std::cout << "Дерево пусто.\n";
				break;
			}
			std::string str;
			std::cout << "Размер: " << tree.Size()
					  << ", Высота: " << tree.Height() << "\n";

			tree.Traversal(str, Order::LNR);
			std::cout << "LNR: " << str << "\n";

			tree.Traversal(str, Order::LRN);
			std::cout << "LRN: " << str << "\n";

			tree.Traversal(str, Order::NLR);
			std::cout << "NLR: " << str << "\n";

			tree.Traversal(str, Order::NRL);
			std::cout << "NRL: " << str << "\n";

			tree.Traversal(str, Order::RLN);
			std::cout << "RLN: " << str << "\n";

			tree.Traversal(str, Order::RNL);
			std::cout << "RNL: " << str << "\n";
			break;
		}

		case 0:
			running = false;
			break;

		default:
			std::cout << "Неизвестная команда.\n";
			break;
		}
	}

	std::cout << "Выход.\n";
	return 0;
}