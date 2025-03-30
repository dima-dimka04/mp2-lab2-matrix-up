#include <iostream>
using namespace std;

enum Color : bool {BLACK, RED};
template<typename Key, typename Data>
class Node;
template<typename Key, typename Data>
class RBIterator;
template<typename Key, typename Data>
class RBTree;

template<typename Key, typename Data>
class Node
{
public:
	Key k;
	Data d;
	int height = 1;
	Node<Key, Data>* parent;
	Node<Key, Data>* left;
	Node<Key, Data>* right;
	Color color;

	Node(Key key, Data data, Color color) : k(key), d(data), parent(nullptr), left(nullptr), right(nullptr), color(color) {}
};

template<typename Key, typename Data>
class RBIterator
{
	friend class RBTree<Key, Data>;
	Node<Key, Data>* node = nullptr;
	Node<Key, Data>* root = nullptr;
	bool isEnd = false;
	RBIterator() = default;
	RBIterator(Node<Key, Data>* n, bool ie) : node(n), isEnd(ie) {}
	RBIterator(Node<Key, Data>* n, Node<Key, Data>* r) : node(n), root(r) {}

	RBIterator operator++()
	{
		auto next = getNext(node);
		node = next;
		if (next == nullptr)
		{
			isEnd = true;
		}
		return *this;
	}

	RBIterator operator++(int)
	{
		auto status = *this;
		auto next = getNext(node);
		node = next;
		if (next == nullptr)
		{
			isEnd = true;
		}
		return status;
	}

	//operator--

	bool operator==(const RBIterator& other) const
	{
		return root == other.root && node == other.node && isEnd == other.isEnd;
	}
	bool operator!=(const RBIterator& other) const
	{
		return !(other == *this);
	}
	
	const Key& operator*()
	{
		return node->k;
	}
};


template<typename Key, typename Data>
class RBTree
{
	Node<Key, Data>* root;
	int size = 0;
public:
	RBTree() : root(nullptr), size(0) {}
	void LeftRotate(Node<Key, Data>* node){}
	void RightRotate(Node<Key, Data>* node){}
	Node<Key, Data>* getNext(Node<Key, Data>* node){}

	Node<Key, Data>* getMin(Node<Key, Data>* node) 
	{
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	Node<Key, Data>* getMax(Node<Key, Data>* node) 
	{
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node;
	}
	RBIterator<Key, Data> begin()
	{
		RBIterator<Key, Data> it1(true, root);
		Node<Key, Data>* node = getMin(root);
		RBIterator<Key, Data> it2(node, root);
		return empty() ? it1 : it2;
	}
	RBIterator<Key, Data> end()
	{
		RBIterator<Key, Data> it(true, root);
		return it;
	}

	bool empty() const
	{
		return size == 0;
	}

	Node<Key, Data>* find(const Key &k) const 
	{
		Node<Key, Data>* node = root;
		while (node != nullptr && k != node->k)
		{
			if (k < node->k)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}
		return node;
	}

	void insert(Node<Key, Data>* node)
	{
		Node<Key, Data>* prev = nullptr;
		Node<Key, Data>* st = root;
		while (st != nullptr)
		{
			prev = st;
			if (node->k < st->k)
			{
				st = st->left;
			}
			else
			{
				st = st->left;
			}
		}
		if (prev == nullptr)
		{
			root = node;
		}
		else 
		{
			if (node->k < prev->k)
			{
				prev->left = node;
			}
			else
			{
				prev->right = node;
			}
		}
		insertBalance(node);
	}

	void insertBalance(Node<Key, Data>* node)
	{
		while (node->parent->color == RED)
		{
			if (node->parent == node->parent->parent->left) 
			{
				auto uncle = node->parent->parent->right; //cases 123 uncle right
				if (uncle->color == RED) // red uncle 1st case
				{
					node->parent->color = BLACK;
					uncle->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else if (node == node->parent->right) //uncle black 2nd case new node right
				{
					node = node->parent;
					LeftRotate(node);
				}
				else //uncle black 2nd case new node left
				{
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					RightRotate(node->parent->parent);
				}
			}
			else //cases 123 uncle left
			{
				auto uncle = node->parent->parent->left;
				if (uncle->color == RED)
				{
					node->parent->color = BLACK;
					uncle->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else if (node == node->parent->left)
				{
					node = node->parent;
					RightRotate(node);
				}
				else
				{
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					LeftRotate(node->parent->parent);
				}
			}
		}
		while (node->parent != nullptr)
		{
			node = node->parent;
		}
		root = node;
		root->color = BLACK;
	}

	
	RBIterator<Key, Data> insert(const Key& k, const Data& d)
	{
		++size;
		Node<Key, Data>* node = new Node<Key, Data>(k, d, RED);
		insert(node);
		RBIterator<Key, Data> it = new RBIterator<Key, Data>(node, root);
		return it;
	}


};