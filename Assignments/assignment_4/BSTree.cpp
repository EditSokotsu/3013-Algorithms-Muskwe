///////////////////////////////////////////////////////////////////////////////
//This is the implementation file for the BSTree class. 
/////////////////////////////////////////////////////////////////////////////////

#include "BSTree.h"
using namespace std;

//@func: int count
//@para: node *root
//@ret: int
//@comm: counts the number of nodes in the BST.
int BSTree::count(node *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		return 1 + count(root->left) + count(root->right);
	}
}

//@func: void count
//@para: node *root
//@ret: void
//@comm: implements the private inserts method, meant to abstract root from
//		the user.
void BSTree::insert(node *&root, node *&temp)
{
	if (!root)
	{
		root = temp;
	}
	else
	{
		if (temp->data < root->data)
		{
			insert(root->left, temp);
		}
		else
		{
			insert(root->right, temp);
		}
	}
}

//@func: void print_node
//@para: node *n, string label
//@ret: void
//@comm: prints the BST in GraphViz format.
void BSTree::print_node(node *n, string label)
{
	label = "";
	if (label != "")
	{
		cout << "[" << label << "]";
	}
	cout << "[[" << n << "][" << n->data << "]]\n";
	if (n->left)
	{
		cout << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[L][null]\n";
	}
	if (n->right)
	{
		cout << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[R][null]\n";
	}
}

/**
* type = ['predecessor','successor']
*/
//@func: node* minValueNode
//@para: node *root
//@ret: node*
//@comm: finds the successor of a given node.
node* BSTree::minValueNode(node *root)
{
	node *current = root;

	if (root->right)
	{
		current = root->right;
		while (current->left != NULL)
		{
			current = current->left;
		}
	}
	else if (root->left)
	{
		current = root->left;
		while (current->right != NULL)
		{
			current = current->right;
		}
	}

	return current;
}

//@func: deleteNode
//@para: node *&root, int key
//@ret: node*
//@comm: implements the private delete method, abstracts root
//		from user.
node* BSTree::deleteNode(node *&root, int key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->data)
	{
		cout << "going left" << endl;
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data)
	{
		cout << "going right" << endl;
		root->right = deleteNode(root->right, key);
	}
	else
	{
		if (root->left == NULL)
		{
			node *temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			node *temp = root->left;
			delete root;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		node *temp = minValueNode(root);

		print_node(temp, "minvaluenode");

		// Copy the inorder successor's content to this node
		root->data = temp->data;
		
		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->data);
		
		
	}
	return root;
}

//@func: height
//@para: node *root
//@ret: node*
//@comm: responsible for finding the height of the BST.
int BSTree::height(node *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		int left = height(root->left);
		int right = height(root->right);
		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}

/* Print nodes at a given level */
//@func: printGivenLevel
//@para: node *root, int level
//@ret: void
//@comm: prints the nodes on a given level of a BST.
void BSTree::printGivenLevel(node *root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
	{
		print_node(root);
	}
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}
//************************************************************************
// Method to help create GraphViz code so the expression tree can
// be visualized. This method prints out all the unique node id's
// by traversing the tree.
// Recivies a node pointer to root and performs a simple recursive
// tree traversal.
//************************************************************************
void BSTree::GraphVizGetIds(node *nodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizGetIds(nodePtr->left, VizOut);
		VizOut << "node" << nodePtr->data
			<< "[label=\"" << nodePtr->data << "\\n"
			//<<"Add:"<<nodePtr<<"\\n"
			//<<"Par:"<<nodePtr->parent<<"\\n"
			//<<"Rt:"<<nodePtr->right<<"\\n"
			//<<"Lt:"<<nodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!nodePtr->left)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		GraphVizGetIds(nodePtr->right, VizOut);
		if (!nodePtr->right)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
	}
}

//************************************************************************
// This method is partnered with the above method, but on this pass it
// writes out the actual data from each node.
// Don't worry about what this method and the above method do, just
// use the output as your told:)
//************************************************************************
void BSTree::GraphVizMakeConnections(node *nodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizMakeConnections(nodePtr->left, VizOut);
		if (nodePtr->left)
			VizOut << "node" << nodePtr->data << "->"
			<< "node" << nodePtr->left->data << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->data << "->"
				<< "nnode" << NullCount << endl;
		}

		if (nodePtr->right)
			VizOut << "node" << nodePtr->data << "->"
			<< "node" << nodePtr->right->data << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->data << "->"
				<< "nnode" << NullCount << endl;
		}

		GraphVizMakeConnections(nodePtr->right, VizOut);
	}
}

//@func: BSTree
//@para: none
//@ret: none
//@comm: default constructor of the BSTree class, does nothing.
BSTree::BSTree()
{
	root = NULL;
}

//@func: ~BSTree
//@para: none
//@ret: none
//@comm: destructor of the BSTree class, does nothing.
BSTree::~BSTree()
{
}

//@func: count
//@para: none
//@ret: int
//@comm: counts the number of nodes in the BST.
int BSTree::count()
{
	return count(root);
}

//@func: insert
//@para: int x
//@ret: int
//@comm: implements the public insert method, meant to be used
//		by user.
void BSTree::insert(int x)
{
	node *temp = new node(x);
	insert(root, temp);
}

//@func: deleteNode
//@para: int key
//@ret: int
//@comm: implements the public delete method, meant to be used
//		by user.
void BSTree::deleteNode(int key)
{
	root = deleteNode(root, key);
}

void BSTree::minValue()
{
	print_node(minValueNode(root), "minVal");
}

//@func: height
//@para: int key
//@ret: int
//@comm: implements the public height method, meant to be used
int BSTree::height(int key )
{
	key = -1;
	if (key > 0)
	{
		//find node
	}
	else
	{
		return height(root);
	}
	return 0;
}

//@func: top
//@para: none
//@ret: int
//@comm: keeps track of the root node.
int BSTree::top()
{
	if (root)
		return root->data;
	else
		return 0;
}

/* Function to line by line print level order traversal a tree*/
void BSTree::printLevelOrder()
{
	cout << "Begin Level Order===================\n";
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printGivenLevel(root, i);
		cout << "\n";
	}
	cout << "End Level Order===================\n";
}

//************************************************************************
// Recieves a filename to place the GraphViz data into.
// It then calls the above two graphviz methods to create a data file
// that can be used to visualize your expression tree.
//************************************************************************
void BSTree::GraphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	VizOut << "Digraph G {\n";
	GraphVizGetIds(root, VizOut);
	GraphVizMakeConnections(root, VizOut);
	VizOut << "}\n";
	VizOut.close();
}

