



#include<iostream>
#include<queue>
#include<vector>
using namespace std;

template<class K, class V>


struct node
{
public:
	K key;
	V value;
	node* leftChild;
	node* rightChild;
};

template<class K, class V>

class specialBST
{
public:
	node<K, V>* root;
	bool insert_flag;
	bool search_flag;
	vector<V> traverse;
	specialBST()
	{
		root = NULL;
		insert_flag=0;
		search_flag=0;
	}

	node<K, V>* insert(node<K, V>*& root, int key, int val)
	{
		if (root == NULL)
		{
			node<K, V>* temp = new node<K, V>();
			temp->key = key;
			temp->value = val;
			temp->leftChild = NULL;
			temp->rightChild = NULL;
			insert_flag = true;
			return temp;
		}
		else if (root->key == key)
		{
			return root;  //nothing to return
		}
		else if (root->key < key)   // inserting on right side of root
		{
			node<K, V>* temp = insert(root->rightChild, key, val);
			
			if (temp == NULL)
			{
				return root;
			}

				root->rightChild = temp->leftChild;
				temp->leftChild = root;
				return temp;

		}
		else                        // inserting on left side of root
		{
			node<K, V>* temp = insert(root->leftChild, key, val);
			
			if (temp == NULL)
			{
				return root;
			}

			root->leftChild = temp->rightChild;
			temp->rightChild = root;
			return temp;
		}
	}


	node<K, V>* search(node<K, V>*& root, K key)
	{
		if (root == NULL)
		{
			return nullptr;
		}
		else if (root->key == key)
		{
			search_flag = true;
			return root;
		}
		else if (root->key < key)
		{
			node<K, V>* temp = search(root->rightChild, key);
			if (temp == NULL)
			{
				return root;
			}
			root->rightChild = temp->leftChild;
			temp->leftChild = root;
			return temp;
		}
		else
		{
			node<K, V>* temp = search(root->leftChild, key);
			if (temp == NULL)
			{
				return root;
			}
			root->leftChild = temp->rightChild;
			temp->rightChild = root;
			return temp;
		}

	}

	node<K, V>* deleting(node<K, V>*& root, K key)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		if (root->key > key)
		{
			node<K, V>* temp = deleting(root->leftChild, key);
			
			if (temp == nullptr)
			{
				return root;
			}
			
			root->leftChild = temp->rightChild;
			temp->rightChild = root;
			return temp;
		}
		else if (root->key < key)
		{
			node<K, V>* temp = deleting(root->rightChild, key);
			
			if (temp == nullptr)
			{
				return root;
			}

			root->rightChild = temp->leftChild;
			temp->leftChild = root;
			return temp;
		}
	 
		else
		{
           search_flag = true;
			node<K, V>* temp = root;

           if (root->rightChild == nullptr) 
			{
				root = root->leftChild;
				delete temp;
               return root;
           }

			if (root->leftChild == nullptr)
			{
				root = root->rightChild;
				delete temp;
				return root;
			}

  
			else
			{
				node<K, V>* next_largest = getSmallestNode(root->rightChild);  // next smallest node
				root->key = next_largest->key;
				root->value = next_largest->value;
				root->rightChild = deleting(root->rightChild, next_largest->key);
				return root->rightChild;
			}
		}
	}
	node<K, V>* getSmallestNode(node<K, V>* &root)
	{
		while (root!= nullptr && root->leftChild != nullptr)
		{
			root = root->leftChild;
		}
		return root;
	}

	void getValuesInOrder(node<K, V>*& root)
	{
		if (root == NULL)
		{
			return;
		}
		getValuesInOrder(root->leftChild);
		cout << root->key << "->";
		traverse.push_back(root->key);  // add root to traversed
		getValuesInOrder(root->rightChild);
	}

	void getValuesLevelWise(node<K, V>* &root)
	{  
		// this is simply a level order traversal standard algorithms using queue
		if (root == nullptr) return;
		queue<node<K, V>*> que;
		que.push(root);
		// start from root, add root to visited and push left and right child to queue
		// do this untill all nodes are processed
		while (!que.empty())
		{
			node<K, V>* front = que.front();
			que.pop();
			traverse.push_back(front->key);
			cout << front->key<<"->";
			if (front->leftChild != nullptr)
			{
				que.push(front->leftChild);
			}
			if (front->rightChild != nullptr)
			{
				que.push(front->rightChild);
			}
		}
	}
	// wraper functions

	vector<V>*  getValuesInOrder()
	{
		cout << "In order traversal\n";
		traverse.clear();
		getValuesInOrder(root);
		cout << endl;
		return &traverse;
	}

	vector<V>* getValuesLevelWise()
	{
		cout << "Level order traversal\n";
		traverse.clear();
		getValuesLevelWise(root);
		cout << endl;
		return &traverse;
	}

	bool insert(int key, int val)
	{
		insert_flag = false;
		root = insert(root, key, val);
		return insert_flag;
	}

	V* search(K key)
	{
		search_flag = false;
		root = search(root, key);
		if (search_flag == true)
		{
			return &root->value;
		}
		else
		{
			return nullptr;
		}
		cout << endl;
	}

	bool deleting(int key)
	{
		search_flag = false;
		root = deleting(root, key);
		return search_flag;
	}


	void destroy(node<K, V>* root)
	{

		if (root == nullptr)
		{
			return;
		}
		destroy(root->leftChild);
		destroy(root->rightChild);
		delete root;
	}

	~specialBST()
	{
		destroy(root);
	}



};

int  main()
{
	specialBST<int, int> tree;

	tree.insert(13, 5);
	tree.insert(15, 4);	
	tree.insert(11, 4);	
	tree.search(13);
	tree.insert(19, 9);

	tree.deleting(11);

	tree.getValuesInOrder();
	tree.getValuesLevelWise();

	
	
	return 0;
}