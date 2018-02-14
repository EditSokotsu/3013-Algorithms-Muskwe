///////////////////////////////////////////////////////////////////////////////
// Title: Assignment #2
// Files: main.cpp, BSTree.cpp, BSTree.h
// Semester: CMPS 3013 Spring 2018
//
// Author: Yani Muskwe
// Email: hellrazor_17@yahoo.com
// Description:
// This program implements a BST and uses graphics to show the output
// of operations made on the tree.
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BSTree.h"
using namespace std;

int main()
{
	srand(2342);

	BSTree B;

	B.insert(38);
	B.insert(10);
	B.insert(29);
	B.insert(27);
	B.insert(5);
	B.insert(43);
	B.insert(36);
	B.insert(3);
	B.printLevelOrder();
	B.GraphVizOut("before.txt");

	while(B.top()){
	     cout<<"removing: "<<B.top()<<endl;
	     B.deleteNode(B.top());
	 }

	B.deleteNode(3);
	B.deleteNode(29);
	B.deleteNode(27);
	B.deleteNode(10);
	B.printLevelOrder();

	B.GraphVizOut("after.txt");
	system("pause>0");
	return 0;
}
