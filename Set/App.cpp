///* C++ program to construct tree using inorder and
//postorder traversals */
#include <iostream>
#include <map>
#include <unordered_map>
//
//using namespace std;
//
///* A binary tree node has data, pointer to left
//child and a pointer to right child */
//struct Node {
//	int data;
//	Node* left, * right;
//};
//
//// Utility function to create a new node 
//Node* newNode(int data);
//
///* Recursive function to construct binary of size n
//from Inorder traversal in[] and Postorder traversal
//post[]. Initial values of inStrt and inEnd should
//be 0 and n -1. The function doesn't do any error
//checking for cases where inorder and postorder
//do not form a tree */
//Node* buildUtil(int in[], int post[], int inStrt,
//	int inEnd, int* pIndex, unordered_map<int, int>& mp)
//{
//	// Base case 
//	if (inStrt > inEnd)
//		return NULL;
//
//	/* Pick current node from Postorder traversal
//	using postIndex and decrement postIndex */
//	int curr = post[*pIndex];
//	Node* node = newNode(curr);
//	(*pIndex)--;
//
//	/* If this node has no children then return */
//	if (inStrt == inEnd)
//		return node;
//
//	/* Else find the index of this node in Inorder
//	traversal */
//	int iIndex = mp[curr];
//
//	/* Using index in Inorder traversal, construct
//	left and right subtress */
//	node->right = buildUtil(in, post, iIndex + 1,
//		inEnd, pIndex, mp);
//	node->left = buildUtil(in, post, inStrt,
//		iIndex - 1, pIndex, mp);
//
//	return node;
//}
//
//// This function mainly creates an unordered_map, then 
//// calls buildTreeUtil() 
//struct Node* buildTree(int in[], int post[], int len)
//{
//	// Store indexes of all items so that we 
//	// we can quickly find later 
//	unordered_map<int, int> mp;
//	for (int i = 0; i < len; i++)
//		mp[in[i]] = i;
//
//	int index = len - 1; // Index in postorder 
//	return buildUtil(in, post, 0, len - 1,
//		&index, mp);
//}
//
///* Helper function that allocates a new node */
//Node* newNode(int data)
//{
//	Node* node = (Node*)malloc(sizeof(Node));
//	node->data = data;
//	node->left = node->right = NULL;
//	return (node);
//}
//
///* This funtcion is here just to test */
//void preOrder(Node* node)
//{
//	if (node == NULL)
//		return;
//	printf("%d ", node->data);
//	preOrder(node->left);
//	preOrder(node->right);
//}
//
//// Driver code 
//int main()
//{
//	int in[] = { 9, 3, 2, 4, 8, 7, 5, 1, 6 };
//	int post[] = { 9, 3, 2, 8, 5, 1, 7, 6, 4 };
//	int n = sizeof(in) / sizeof(in[0]);
//
//	Node* root = buildTree(in, post, n);
//
//	cout << "Preorder of the constructed tree : \n";
//	preOrder(root);
//
//	return 0;
//}
/* A O(n) program for construction of
BST from postorder traversal */
//#include <bits/stdc++.h> 
using namespace std;

/* A binary tree node has data,
pointer to left child and a
pointer to right child */
struct node
{
	int data;
	struct node* left, * right;
};

// A utility function to create a node 
struct node* newNode(int data)
{
	struct node* temp =
		(struct node*)malloc(sizeof(struct node));

	temp->data = data;
	temp->left = temp->right = NULL;

	return temp;
}

// A recursive function to construct 
// BST from post[]. postIndex is used 
// to keep track of index in post[]. 
struct node* constructTreeUtil(int post[], int* postIndex,
	int key, int min, int max,
	int size)
{
	// Base case 
	if (*postIndex < 0)
		return NULL;

	struct node* root = NULL;

	// If current element of post[] is 
	// in range, then only it is part 
	// of current subtree 
	if (key > min && key < max)
	{
		// Allocate memory for root of this 
		// subtree and decrement *postIndex 
		root = newNode(key);
		*postIndex = *postIndex - 1;

		if (*postIndex >= 0)
		{

			// All nodes which are in range {key..max} 
			// will go in right subtree, and first such 
			// node will be root of right subtree. 
			root->right = constructTreeUtil(post, postIndex,
				post[*postIndex],
				key, max, size);

			// Construct the subtree under root 
			// All nodes which are in range {min .. key} 
			// will go in left subtree, and first such 
			// node will be root of left subtree. 
			root->left = constructTreeUtil(post, postIndex,
				post[*postIndex],
				min, key, size);
		}
	}
	return root;
}

// The main function to construct BST 
// from given postorder traversal. 
// This function mainly uses constructTreeUtil() 
struct node* constructTree(int post[],
	int size)
{
	int postIndex = size - 1;
	return constructTreeUtil(post, &postIndex,
		post[postIndex],
		INT_MIN, INT_MAX, size);
}

// A utility function to print 
// inorder traversal of a Binary Tree 
void printInorder(struct node* node)
{
	if (node == NULL)
		return;
	printInorder(node->left);
	cout << node->data << " ";
	printInorder(node->right);
}

// Driver Code 
int main()
{
	int post[] = { 3, 2, 1, 5, 6, 4, 9, 8, 7 };
	int size = sizeof(post) / sizeof(post[0]);

	struct node* root = constructTree(post, size);

	cout << "Inorder traversal of "
		<< "the constructed tree: \n";
	printInorder(root);

	return 0;
}

// This code is contributed 
// by Akanksha Rai 
