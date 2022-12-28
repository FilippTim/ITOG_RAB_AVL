#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct node
{
	float value;
	node* left;
	node* right;
	int balance;
};

class Tree
{
public:

	virtual int height(node* root) = 0;//функция определения высоты
	virtual void SetBalance(node* (&root)) = 0;//функция изменения поля balance
	virtual void TurnLeft(node* (&root)) = 0; //функция левого поворота
	virtual void TurnRight(node* (&root)) = 0; //функция правого поворота
	virtual void insert(node*(&root), float value) = 0; //функция вставки
	virtual float setValue(node* (&root)) = 0;
	//virtual void print_n(const node* p, int n, int level, int prob) = 0;
	//virtual void print(node* p) = 0;

};

class AVL_TREE : public Tree
{
private:

	float setValue(node* (&root)) override {
		return root->value;
	}

	int height(node *root) override {

		if (root == NULL) return 0;
		
		else {return (max(height(root->left), height(root->right)) + 1);}

	}

	void SetBalance(node* (&root)) override {

		if (root != NULL) {
			if (!(root->right)) {
				root->balance = -height(root->left);
			}
			else if (!(root->left)) {
				root->balance = height(root->right);
			}
			else if ((!(root->left)) && (!(root->right))) {
				root->balance = 0;
			}
			else {
				root->balance = height(root->right) - height(root->left);
			}
		}
	}

	void balanceTree(node* (&root))
	{
		SetBalance(root);
		if (root->balance >= 2) //большой левый
		{
			SetBalance(root->right);
			if (root->right->balance < 0)
				TurnRight(root->right);
			TurnLeft(root);
		}

		if (root->balance <= -2) // большой правый
		{
			SetBalance(root->left);
			if (root->left->balance > 0)
				TurnLeft(root->left);
			TurnRight(root);
		}
	}

	void TurnLeft(node* (&root)) override {

		rightsubtree = root->right;//(3)
		leftsubtree_of_rightsubtree = rightsubtree->left;//(4)

		rightsubtree->left = root;
		root->right = leftsubtree_of_rightsubtree;
		root = rightsubtree;
		SetBalance(root->left);
		SetBalance(root);
	}

	void TurnRight(node*(&root)) override{

		leftsubtree = root->left;//(1)
		rightsubtree_of_leftsubtree = leftsubtree->right;//(2)

		leftsubtree->right = root;
		root->left = rightsubtree_of_leftsubtree;
		root = leftsubtree;
		SetBalance(root->right);
		SetBalance(root);

	}

	node* find_min(node* (&root)) {

		return root->left ? find_min(root->left) : root;
	}
	node* find_max(node* (&root)) {

		return root->right ? find_max(root->right) : root;
	}

public:

	void insert(node* (&root), float value) override {

		if (root == NULL) {
			root = new node;
			root->value = value;
			root->balance = 0;
			root->left = NULL;
			root->right = NULL;
		}
		else if (value > root->value) {//идем вправо

			insert(root->right, value);
			balanceTree(root);
		}
		else if (value < root->value) {//идем влево

			insert(root->left, value);
			balanceTree(root);
		}
		else if (value == root->value) {//такой узел уже имеется
		}

		//balanceTree(root);

	}





	

	void remove2(node* root, float value) {

		if (root) {

			if (value < root->value) {
				remove2(root->left, value);
			}
			else if (value > root->value) {
				remove2(root->right, value);
			}
			else if (value == root->value) {

				node* L = root->left;
				node* R = root->right;
				if (!R) {
					if (!L) {
						delete root;
					}
					else {
						node* ptr = find_max(L);
						root->value = ptr->value;
						remove2(ptr, ptr->value);
						balanceTree(root);
					}
				}
				else{
				
					node* ptr = find_min(R);
					root->value = ptr->value;
					remove2(ptr, ptr->value);
					balanceTree(root);
				}

			}

		}
	}



	void print_DFS(node* root) {
		if (root) {
			if (root->left) print_DFS(root->left);
			cout << root->value << " ";
			if (root->right) print_DFS(root->right);
		}
	}
	void DFS(node* root) {
		cout << " " << endl;
		print_DFS(root);
		cout << endl  << endl;
	}


	void print_BFS(const node* p, int n, int level) {

		if (p) {

			if (level == n) {

				for (int i = 0; i <= prob; i++) cout << " ";
				cout << p->value;
			}
			else {

				print_BFS(p->left, n, level + 1);
				print_BFS(p->right, n, level + 1);
			}
		}
	}

	void BFS(node* p) {

		cout << endl;

		h = height(p);
		if (p) {

			for (int i = 0; i <= h; i++) {
				print_BFS(p, i, 0);
			}
		}
		cout << endl << endl;;
	}

	

	
	public:

		int heightleft, heightright;
		string str = "";
		int h, prob;
		node* rightsubtree, * leftsubtree;
		node* leftsubtree_of_rightsubtree, * rightsubtree_of_leftsubtree;



		//void remove(node* (&root), float value) {

//	if (!root) { cout << "Узел с ключом " << value << " не найден" << endl; }
//	else if (value < root->value) {
//		remove(root->left, value);
//	}
//	else if (value > root->value) {
//		remove(root->right, value);
//	}
//	else if (value == root->value) {

//		node* L = root->left;
//		node* R = root->right;

//		if (!R) {
//			if (!L) {
//				delete root; //goto metka1;
//			}
//			else {
//				node* q = find_max(root->left);
//				root->value = q->value;

//				if ((!(q->left)) && (!(q->right))) {
//					delete find_max(root->left);
//					balanceTree(root->left);
//				}
//				else {
//					remove(q, q->value);
//				}
//			}
//		}
//		else
//		{

//			node* min = find_min(root->right);
//			root->value = min->value;

//			if (!((min->left) && (min->right))) {
//				delete find_min(root->right);
//				if (root->right) {
//					balanceTree(root->right);
//				}
//			}
//			else {
//				remove(min, min->value);
//			}
//		}
//	}
//	//metka1:
//		balanceTree(root);
//}

		//void insert(node* (&root), float value) override {

	//	if (root == NULL){
	//		root = new node;
	//		root->value = value;
	//		root->balance = 0;
	//		root->left = NULL; 
	//		root->right = NULL;
	//	}
	//	else if (value > root->value) {//идем вправо

	//		insert(root->right, value);
	//		if (height(root->right) - height(root->left) > 1) {

	//			if (height(root->right->right) < height(root->right->left)) TurnRight(root->right);
	//			TurnLeft(root);
	//		}
	//	}
	//	else if (value < root->value) {//идем влево

	//		insert(root->left, value);
	//		if (height(root->left) - height(root->right) > 1) {

	//			if (height(root->left->left) < height(root->left->right)) TurnLeft(root->left);
	//			TurnRight(root);
	//		}
	//	}
	//	else if(value == root->value){//такой узел уже имеется
	//	}

	//	SetBalance(root);

	//}




	//void print_n(const node* p, int n, int level, int prob) {

//	if (p) {

//		if (level == n) {

//			for (int i = 0; i <= prob; i++) cout << ".";
//			cout << p->value;
//		}
//		else {

//			print_n(p->left, n, level + 1, prob);
//			print_n(p->right, n, level + 1, prob);
//		}
//	}
//}

//void print(node* p) {

//	h = height(p);
//	prob = 3;
//	if (p) {

//		for (int i = 0; i <= h; i++) {
//			print_n(p, i, 0, prob * (h - i));
//			cout << endl;
//		}
//	}
//}

};
