#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node *left;
	Node *right;
};

Node* create_node(int data);
Node* insert_node(Node *root, int data);
void print_tree(Node *root);
bool search_node(Node *root, int searching);
Node* search_minimum(Node *root);
Node* search_maximum(Node *root);

int main()
{
	int tamano, data;
	Node *root = NULL;
	
	cout << "How Many: ";
	cin >> tamano;
	
	while (tamano > 0)
	{
		cout << "data: ";
		cin >> data;
		
		root = insert_node(root, data);
		tamano--;
	}
	
	print_tree(root);
	
	cout << "minimo: " << search_minimum(root)->data << endl;
	cout << "maximo: " << search_maximum(root)->data << endl;
	
	return 0;
}

Node* create_node(int data)
{
	Node* new_node = new Node;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

Node* insert_node(Node *root, int data)
{
	if (search_node(root, data))
		return root;

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

void print_tree(Node *root)
{
	if (root == NULL)
		return;
		
	print_tree(root->left);
	cout << root->data << " ";
	print_tree(root->right);
}

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

Node* search_minimum(Node *root)
{
	if (root->left == NULL)
		return root;
		
	return search_minimum(root->left);
}
Node* search_maximum(Node *root)
{
	if (root->right == NULL)
		return root;
		
	return search_maximum(root->right);
}
