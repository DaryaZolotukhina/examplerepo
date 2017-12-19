#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_

#include <iostream>
#include <string>
#include <set>

using namespace std;

template<typename T>
class DoubleLinkedList 
{ 
private: 
	struct Node{ 
		T data;
		Node* next;
		Node* prev;
		Node(const T& el)
		{
			data = el;
			prev = next = nullptr;
		}
	}; 
	Node *head, *tail; 
	int count;

public: 
	DoubleLinkedList();
	~DoubleLinkedList();

	int getLength() const { return count; }// вычисление длины

	void addToBeg(const T&);
	void addToEnd(const T&);

	void print();

	bool symmetric();
	int cntUniqueNodes();
	void delMetNodes();
	void reverseList();
	void sortList();

};

#endif