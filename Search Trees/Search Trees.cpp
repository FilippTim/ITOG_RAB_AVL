#include "Tree.h"
#include <sstream>

AVL_TREE tree;

void user() {
	setlocale(LC_ALL, "rus");
	node* root;
	root = NULL;
	string ch = "";
	AVL_TREE tree;
	cout << "Команды: " << endl;
	cout << "1. start - начать ввод элементов" << endl;
	cout << "2. stop - закончить ввод элементов" << endl;
	cout << "3.print - вывести в порядке возрастания  " << endl;
	cout << "3. print_b вывести сбалансированую строку" << endl;
	cout << "4. exit - выход" << endl;
	while (ch != "exit") {
		cout <<"Введите команду:  ";
		cin >> ch;
		if (ch == "start") {

			cout << "Введите команду или значение: ";
			string x;
			cin >> x;

			while (x != "stop"){
				float x0 = stoi(x);
				tree.insert(root, x0);
				cout << "Элемент успешно вставлен" << endl;
				cout << "Введите команду или значение: ";
				cin >> x;
			}
			cout << "Ввод окончен" << endl;
		}

		else if (ch == "print") {
			tree.DFS(root);
			
		}
		else if (ch == "print_b") {

			tree.BFS(root);
		}
	}
}

void admin() {

	setlocale(LC_ALL, "rus");
	node* root;
	root = NULL;
	for (float i = 1; i <= 9; i++) {
		tree.insert(root, i);
	}

	//tree.remove2(root, 9);

	tree.BFS(root);
	tree.DFS(root);
}

int main()
{
	//admin();
	user();
}
