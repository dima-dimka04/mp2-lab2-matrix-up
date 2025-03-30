#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;



template <typename Key, typename Data>
class Tree;


template <typename Key, typename Data>
class Node {
public:
	Key key;
	int height=1;
	Data value = 0;
	Node* left;
	Node* right;
	Node(Key k, Data d) : key(k), value(d), left(nullptr), right(nullptr) {}
	Node(Key k, Data d, Node* l, Node* r) : key(k), value(d), left(l), right(r) {}
};

template <typename Key, typename Data>
class TreeIterator
{
	friend class Tree<Key, Data>;
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
class Tree {
public:

	Node<Key, Data>* root;

	int size()
	{
		int s = 0;
		Tree<Key, Data>::TreeIterator it;
		for (it = begin(); it != end(); ++it)
		{
			s++;
		}
		return s;
	}

	class TreeIterator
	{
		friend class Tree<Key, Data>;
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

	int height(Node<Key, Data>* node)
	{
		if (node != NULL)
		{
			return 1 + max(height(node->left), height(node->right));
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

	Node<Key, Data>* findmin(Node<Key, Data>* p) // ����� ���� � ����������� ������ � ������ p 
	{
		return p->left ? findmin(p->left) : p;
	}

	Node<Key, Data>* removemin(Node<Key, Data>* p) // �������� ���� � ����������� ������ �� ������ p
	{
		if (p->left == NULL)
			return p->right;
		p->left = removemin(p->left);
		return p;
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

	Node<Key, Data>* insert(Node<Key, Data>* p, Key k, Data d)
	{
		if (!p) return new Node<Key, Data>(k, d);
		if (k <= p->key)
			p->left = insert(p->left, k, d);
		else
			p->right = insert(p->right, k, d);
		return p;
	}

	Node<Key, Data>* remove(Node<Key, Data>* node, Key k)
	{
		if (node == NULL)
		{
			return NULL;
		}
		if (k < node->key)
			node->left = remove(node->left, k);
		else if (k > node->key)
			node->right = remove(node->right, k);
		else //  k == node->key 
		{
			Node<Key, Data>* q = node->left;
			Node<Key, Data>* r = node->right;
			delete node;
			if (!r) return q;
			Node<Key, Data>* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return min;
		}
		return node;
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



	Tree() : root(nullptr) {}

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

	void inorder()
	{
		inorder(root);
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
		root = insert(root, k, d);
	}

	void remove(Key k)
	{
		root = remove(root, k);
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
