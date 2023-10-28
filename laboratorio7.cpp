#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	int data;
	Node *left;
	Node *right;
};

struct GeneralNode
{
	int data;
	vector<GeneralNode*> nodes;
};

// binary tree functions
Node* create_node(int data);
Node* insert_node(Node *root, int data);
void print_tree(Node *root);
bool search_node(Node *root, int searching);
Node* search_minimum(Node *root);
Node* search_maximum(Node *root);
Node* delete_node(Node *root, int deleting);

// general tree functions
GeneralNode* create_general_node(int data);
void insert_general_node(GeneralNode *root, int parent_data, int data);
void print_general_tree(GeneralNode *root, int depth);

int main()
{
	int election, data, parent_data;
	Node *binary_root = NULL;
	GeneralNode *general_root = NULL;
	
	do{
		cout << "---Binary Tree Menu---" << endl;
		cout << "[1] Create Node\n[2] Print Tree\n[3] Delete Node\n[4] Search Maximum and Minimum" << endl << endl;
		cout << "--- General Tree Menu---" << endl;
		cout << "[5] Create Node\n[6] Print Tree" << endl << endl;
		cout << "[7] Exit" << endl;
		cout << "Election: ";
		cin >> election;
		
		switch (election)
		{
			case 1: // create node
				cout << "Data: ";
				cin >> data;
				binary_root = insert_node(binary_root, data);
				cout << "Node added to Binary Tree." << endl;
				break;
				
			case 2: // print tree
				cout << "---Binary Tree--- " << endl;
				print_tree(binary_root);
				break;
				
			case 3: // delete node
				cout << "Data to Delete: ";
				cin >> data;
				delete_node(binary_root, data);
				break;
				
			case 4: // maximum & minimum
				cout << "Minimum: " << search_minimum(binary_root)->data << endl;
				cout << "Maximum: " << search_maximum(binary_root)->data << endl;
				break;
				
			case 5: // create general node
				cout << "Data: ";
				cin >> data;
				if (general_root != NULL)
				{
					cout << "Data of Parent Node: ";
					cin >> parent_data;
					insert_general_node(general_root, parent_data, data);
				}
				else
					general_root = create_general_node(data);
				
				cout << "Node Added to General Tree" << endl;
				break;
				
			case 6: // print general tree
				cout << "---General Tree---" << endl;
				print_general_tree(general_root, 0);
				break;
		}
		cout << endl;
	} while (election != 7);
	
	return 0;
}

// creates node for binary tree
Node* create_node(int data)
{
	Node* new_node = new Node;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

// inserts node in binary tree
Node* insert_node(Node *root, int data)
{
	if (search_node(root, data))
	{
		cout << "Data Presviously Added..." << endl;
		return root;
	}

	if (root == NULL)
		root = create_node(data);
	else
	{
		if (root->data >= data)
			root->left = insert_node(root->left, data);
		else
			root->right = insert_node(root->right, data);
	}
	return root;
}

// prints binary tree
void print_tree(Node *root)
{
	if (root == NULL)
		return;
		
	print_tree(root->left);
	cout << root->data << " ";
	print_tree(root->right);
}

// searches node data in tree
bool search_node(Node *root, int searching)
{
	if (root == NULL)
		return false;
	
	if (root->data > searching)
		return search_node(root->left, searching);
	else if (root->data < searching)
		return search_node(root->right, searching);
	else
		return true;
}

// searches minimum value data
Node* search_minimum(Node *root)
{
	if (root->left == NULL)
		return root;
		
	return search_minimum(root->left);
}

// seraches maximum value data
Node* search_maximum(Node *root)
{
	if (root->right == NULL)
		return root;
		
	return search_maximum(root->right);
}

// deletes requested node data
Node* delete_node(Node *root, int deleting)
{
	if (root == NULL)
		return root;
		
	if (root->data > deleting)
		root->left = delete_node(root->left, deleting);
	else if (root->data < deleting)
		root->right = delete_node(root->right, deleting);
	else
	{
		if (root->left == NULL)
		{
			Node *temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			Node *temp = root->left;
			delete root;
			return temp;
		}
		
		Node *temp = root->right;
		while (temp->left != NULL)
			temp = temp->left;
			
		root->data = temp->data;
		root->right = delete_node(root->right, temp->data);
	}
	
	return root;
}

// creates node for general tree
GeneralNode* create_general_node(int data)
{
	GeneralNode* newNode = new GeneralNode;
	newNode->data = data;
	newNode->nodes.clear();
	
	return newNode;
}

// inserts node in general tree
void insert_general_node(GeneralNode *root, int parent_data, int data)
{
	if (root == NULL)
		return;
		
	if (root->data == parent_data)
	{
		GeneralNode *newNode = create_general_node(data);
		root->nodes.push_back(newNode);
	}
		
	for (GeneralNode* node : root->nodes)
		insert_general_node(node, parent_data, data);
	
	return;
}

// prints general tree
void print_general_tree(GeneralNode *root, int depth)
{
	if (root == NULL)
		return;
		
	for (int i=0; i < depth; i++)
		cout << "  ";
		
	cout << "|-- " << root->data << endl;
	
	for (GeneralNode* node : root->nodes)
		print_general_tree(node, depth+1);
}
