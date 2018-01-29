///////////////////////////////////////////////////////////////////////////////
// Title: Assignment #2
// Files: main.cpp
// Semester: CMPS 3013 Spring 2018
//
// Author: Yani Muskwe
// Email: hellrazor_17@yahoo.com
// Description:
// This program runs a linked list that implements two types of
// insert methods; an ordered insert, that maintains order throughout,
// and a front insert.
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>

using namespace std;

//Create a container for our list data
struct node {
	int data;
	node* next;
};

/**
* Class: intLinkedList
* Purpose:
*     Implements a singly linked list that holds integers.
* Methods:
*     void  frontSert(int x)
*     node* find(int key)
*     node* remove(int key)
*     void  print()
*/
class intLinkedList {
private:
	node* Head;
public:
	intLinkedList() {
		Head = NULL;
	}
	void frontSert(int x) {
		//empty list case
		if (!Head) {
			Head = new node;
			Head->data = x;
			Head->next = NULL;
		}
		else {//not empty list
			node* T = new node;
			T->data = x;
			T->next = Head;
			Head = T;
		}
	}

	//@func: orderedSert()
	//@para: int x
	//@comm: inserts items to the list, in ascending order.
	void orderedSert(int x) {

		//empty list case
		if (!Head) {
			frontSert(x);
		}
		else {//not empty list, maintain ascending order.
			node* p = Head; //temporary pointer
			node* T = new node;//new node to be inserted
			T->data = x;
			if (p->data > T->data) {
				frontSert(x);
			}
			else {
				while (p->next != NULL &&
					p->next->data < T->data)
				{
					p = p->next;
				}
				T->next = p->next;
				p->next = T;
			}

		}
	}

	//@func: Find()
	//@para: int key
	//@comm: finds any integer in the linked list.
	node* Find(int key) {
		node* temp = Head;
		while (temp) {
			if (temp->data == key) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}

	//@func: Remove()
	//@para: int key
	//@comm: removes any integer from the list.
	void Remove(int key) {
		node* result = Find(key);
		if (result) {
			node* temp = Head;
			while (temp->next != result) {
				temp = temp->next;
			}
			temp->next = result->next;
			delete result;
		}
	}

	//@func: print()
	//@para: none
	//@comm: prints the linked list.
	void print() {
		node* p = Head;
		while (p) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
};

int main() {
	// seed random number generator
	srand(8734587);


	// declare instance of intLinkedList turning
	// a class definition into an "object"
	intLinkedList mylist;
	intLinkedList mylist_2;

	//Load 10 random ints into our list
	for (int i = 0; i<10; i++) {
		mylist.frontSert(rand() % 100);
		mylist_2.orderedSert(rand() % 100);
	}

	//print the list
	mylist.print();

	//print orderedSert() list
	mylist_2.print();


	system("pause");
}