#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <map>
using namespace std;

//template<typename Key, typename Data>
//class TreeIterator;

template <typename Key, typename Data>
class AVLTree;


template <typename Key, typename Data>
class Node {
public:
	Key key;
	int height=1;
	Data value=0;
	Node* left;
	Node* right;
	Node* parent;
	Node(Key k, Data d) : key(k), value(d), left(nullptr), right(nullptr), parent(nullptr) {}
	Node(Key k, Data d, Node* l, Node* r, Node* p) : key(k), value(d), left(l), right(r), parent(p) {}
};

template <typename Key, typename Data>
class TreeIterator
{
	friend class AVLTree<Key, Data>;
private:
	Node<Key, Data>* node;
	vector<Node<Key, Data>*> v;
public:
	TreeIterator() : node(nullptr) {}
	TreeIterator(Node<Key, Data>* other) : node(other) {}
	TreeIterator(Node<Key, Data>* other, vector<Node<Key, Data>*>& vec)
	{
		node = other;
		for (auto el : vec)
		{
			v.push_back(el);
		}
	}

	Node<Key, Data>* getNode()
	{
		return node;
	}

	bool operator==(TreeIterator const& other)
	{
		return node == other.node;
	}

	bool operator!=(TreeIterator const& other)
	{
		return node != other.node;
	}

	Key& operator*()
	{
		return node->key;
	}

	TreeIterator& operator++()
	{
		for (int i = 0; i < v.size() - 1; i++)
		{
			if (node == v[i])
			{
				node = v[i + 1];
				return *this;
			}
		}
		if (node == v[v.size() - 1]) { node = nullptr; }
		return *this;
	}


};

template <typename Key, typename Data>
class AVLTree {
public:

	Node<Key, Data>* root;
	AVLTree() : root(nullptr) {}

	int size()
	{
		int s = 0;
		AVLTree<Key, Data>::TreeIterator it;
		for (it = begin(); it != end(); ++it)
		{
			s++;
		}
		return s;
	}

	class TreeIterator
	{
		friend class AVLTree<Key, Data>;
	private:
		Node<Key, Data>* node;
		vector<Node<Key, Data>*> v;
	public:
		TreeIterator() : node(nullptr) {}
		TreeIterator(Node<Key, Data>* other) : node(other) {}
		TreeIterator(Node<Key, Data>* other, vector<Node<Key, Data>*>& vec)
		{
			node = other;
			for (auto el : vec)
			{
				v.push_back(el);
			}
		}

		Node<Key, Data>* getNode()
		{
			return node;
		}

		bool operator==(TreeIterator const& other)
		{
			return node == other.node;
		}

		bool operator!=(TreeIterator const& other)
		{
			return node != other.node;
		}

		Key& operator*()
		{
			return node->key;
		}

		TreeIterator& operator++()
		{
			for (int i = 0; i < v.size() - 1; i++)
			{
				if (node == v[i])
				{
					node = v[i + 1];
					return *this;
				}
			}
			if (node == v[v.size() - 1]) { node = nullptr; }
			return *this;
		}


	};

	int myheight(Node<Key, Data>* p)
	{
		return p ? p->height : 0;
	}

	int height(Node<Key, Data>* node)
	{
		if (node != NULL)
		{
			return 1+max(height(node->left), height(node->right));
		}
		return 0;
	}

	Node<Key, Data>* find(Node<Key, Data>* node, Key k) const
	{
		if (node == nullptr || node->key == k)
		{
			return node;
		}
		if (k <= node->key)
		{
			return find(node->left, k);
		}
		else
		{
			return find(node->right, k);
		}
	}

	Node<Key, Data>* minimum(Node<Key, Data>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	Node<Key, Data>* maximum(Node<Key, Data>* node)
	{
		if (node == nullptr)
		{
			return NULL;
		}
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node;
	}

	//old shit code
	/*void insert(Node<Key, Data>* node, Key k, Data d)
	{
		Node<Key, Data>* p = new Node<Key, Data>(k, d);
		if (IsEmpty()) {
			root = p;
		}
		else
		{
			auto parent = FindParent(k);
			p->height = 1;
			if (k < parent->key)
			{
				parent->left = p;
			}
			else
			{
				parent->right = p;
			}
			p->parent = parent;
			Rebalance(parent);
		}
	}

	//Node<Key, Data>* LLRotate(Node<Key, Data>* n2)
	//{
	//	Node<Key, Data>* n1;
	//	n1 = n2->left;
	//	n2->left = n1->right;
	//	n1->right = n2;

	//	n2->height = max(height(n2->left), height(n2->right)) + 1;
	//	n1->height = max(height(n1->left), n2->height) + 1;

	//	return n1;
	//}

	//Node<Key, Data>* RRRotate(Node<Key, Data>* n1)
	//{
	//	Node<Key, Data>* n2;
	//	n2 = n1->right;
	//	n1->right = n2->left;
	//	n2->left = n1;

	//	n1->height = max(height(n1->left), height(n1->right)) + 1;
	//	n2->height = max(height(n2->right), n1->height) + 1;

	//	return n2;
	//}

	//Node<Key, Data>* LRRotate(Node<Key, Data>* n3)
	//{
	//	n3->left = RRRotate(n3->left);
	//	return LLRotate(n3);
	//}

	//Node<Key, Data>* RLRotate(Node<Key, Data>* n1)
	//{
	//	n1->right = LLRotate(n1->right);
	//	return RRRotate(n1);
	//}

	Node<Key, Data>* remove(Node<Key, Data>*& node, Node<Key, Data>* n)
	{
		if (node == nullptr || n == nullptr)
		{
			Node<Key, Data>* n(nullptr);
			return n;
		}

		if (n->key < node->key)
		{
			node->left = remove(node->left, n);
			if (height(node->right) - height(node->left) == 2)
			{
				Node<Key, Data>* r = node->right;
				if (height(r->left) > height(r->right))
				{
					node = RLRotate(node);
				}
				else
				{
					node = RRRotate(node);
				}
			}
		}
		else if (n->key > node->key)
		{
			node->right = remove(node->right, n);
			if (height(node->right) - height(node->left) == 2)
			{
				Node<Key, Data>* l = node->left;
				if (l != nullptr) {
					if (height(l->right) > height(l->left))
					{
						node = LRRotate(node);
					}
					else
					{
						node = LLRotate(node);
					}
				}
			}
		}
		else
		{
			if ((node->left != nullptr) && (node->right != nullptr))
			{
				if (height(node->left) > height(node->right))
				{
					Node<Key, Data>* M = maximum(node->left);
					node->key = M->key;
					node->left = remove(node->left, M);
				}
				else
				{
					Node<Key, Data>* m = minimum(node->right);
					node->key = m->key;
					node->right = remove(node->right, m);
				}
			}
			else
			{
				Node<Key, Data>* tmp = node;
				node = (node->left != nullptr) ? node->left : node->right;
				tmp = NULL;
			}
		}
		return node;
	}*/

	int balancefactor(Node<Key, Data>* p)
	{
		return myheight(p->right) - myheight(p->left);
	}

	void fixheight(Node<Key, Data>* p)
	{
		int hl = myheight(p->left);
		int hr = myheight(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	Node<Key, Data>* rotateright(Node<Key, Data>* p) // ������ ������� ������ p
	{
		Node<Key, Data>* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	Node<Key, Data>* rotateleft(Node<Key, Data>* q) // ����� ������� ������ q
	{
		Node<Key, Data>* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	Node<Key, Data>* findmin(Node<Key, Data>* p) // ����� ���� � ����������� ������ � ������ p 
	{
		return p->left ? findmin(p->left) : p;
	}

	Node<Key, Data>* balance(Node<Key, Data>* p) // ������������ ���� p
	{
		fixheight(p);
		if (balancefactor(p) == 2)
		{
			if (balancefactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (balancefactor(p) == -2)
		{
			if (balancefactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // ������������ �� �����
	}

	Node<Key, Data>* removemin(Node<Key, Data>* p) // �������� ���� � ����������� ������ �� ������ p
	{
		if (p->left == NULL)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}


	Node<Key, Data>* myInsert(Node<Key, Data>* p, Key k, Data d) // ������� ����� k � ������ � ������ p
	{
		if (!p) return new Node<Key, Data>(k, d);
		if (k < p->key)
			p->left = myInsert(p->left, k, d);
		else
			p->right = myInsert(p->right, k, d);
		return balance(p);
	}


	Node<Key, Data>* myRemove(Node<Key, Data>* p, Key k)
	{
		if (p == NULL)
		{
			return NULL;
		}
		if (k < p->key)
			p->left = myRemove(p->left, k);
		else if (k > p->key)
			p->right = myRemove(p->right, k);
		else //  k == p->key 
		{
			Node<Key, Data>* q = p->left;
			Node<Key, Data>* r = p->right;
			delete p;
			if (!r) return q;
			Node<Key, Data>* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	void printTree(Node<Key, Data>* node, int tab = 2)
	{
		if (node != nullptr)
		{
			if (node->right != nullptr) { printTree(node->right, tab + 4); }
			if (tab > 0) { cout << setw(tab) << " "; }
			if (node->right != nullptr) { cout << "/\n" << setw(tab) << " "; }
			cout << node->key << endl;
			if (node->left != nullptr)
			{
				cout << setw(tab) << " " << "\\\n";
				printTree(node->left, tab + 4);
			}
		}
	}

	Node<Key, Data>* getRoot()
	{
		return root;
	}

	TreeIterator begin()
	{
		vector<Node<int, int>* >v;
		this->TreeToArray(this->getRoot(), v);
		TreeIterator it(this->find(this->minimum()), v);
		return it;
	}

	TreeIterator end()
	{
		TreeIterator it(nullptr);
		return it;
	}

	int height()
	{
		return height(root);
	}

	Node<Key, Data>* find(Key k)
	{
		return find(root, k);
	}

	Key minimum()
	{
		Node<Key, Data>* n = minimum(root);
		if (n != nullptr)
		{
			return n->key;
		}
		return (Key)NULL;
	}

	Key maximum()
	{
		Node<Key, Data>* n = maximum(root);
		if (n != nullptr)
		{
			return n->key;
		}
		return (Key)NULL;
	}

	void insert(Key k, Data d)
	{
		root = myInsert(root, k, d);
	}

	void remove(Key k)
	{
		root = myRemove(root, k);
	}

	void printTree()
	{
		printTree(root);
	}

	Data& operator[](Key k)
	{
		Node<Key, Data>* p = find(root, k);
		if (p != nullptr)
		{
			return p->value;
		}
		insert(k, NULL);
		Node<Key, Data>* t = find(root, k);
		return t->value;
	}

	void TreeToArray(Node<Key, Data>* root, vector<Node<Key, Data>*>& v)
	{
		if (root != nullptr)
		{
			TreeToArray(root->left, v);
			v.push_back(root);
			TreeToArray(root->right, v);
		}
		else return;
	}
};


//int main()
//{
//	AVLTree<int, int> t;
//	map<int, int> m;
//	vector<int>v;
//
//	/*t.insert(10, 0);
//	t.insert(20, 0);
//	t.insert(30, 0);
//	t.insert(40, 0);
//	t.insert(50, 0);
//	t.insert(25, 0);
//	t.insert(15, 0);
//	t.insert(60, 0);
//	t.printTree();
//	t.remove(30);
//	t.printTree();
//	t.remove(40);
//
//	t.printTree();*/
//
//	for (int i = 0; i < 10000; i++)
//	{
//		v.push_back(i);
//	}
//	std::shuffle(v.begin(), v.end(), default_random_engine(0));
//	int st = clock();
//	for (int i = 0; i < 10000; i++)
//	{
//		t.insert(v[i], 1);
//	}
//	int end = clock();
//
//	cout << end - st << endl;
//	int st1 = clock();
//	for (int i = 0; i < 9990; i++)
//	{
//		t.remove(v[i]);
//	}
//	int end1 = clock();
//	cout << end1 - st1 << endl;
//	t.printTree();
//	cout << endl << endl << t.size() << endl << t.height() << endl << t.minimum() <<endl<< t.maximum();
//		
//}