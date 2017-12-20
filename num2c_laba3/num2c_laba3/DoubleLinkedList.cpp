#include "DoubleLinkedList.h"

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	Node *tmp;

	while (head) 
	{
		tmp = head;
		head = tmp->next;
		delete(tmp);
	}
}

template <typename T>
void DoubleLinkedList<T>::addToBeg(const T &el)
{
	Node *tmp = new Node(el);

	if (head != nullptr){
		tmp->next = head;
		head->prev = tmp;
	}
	else {
		tail = tmp;
	}

	head = tmp;
	count++;
}

template <typename T>
void DoubleLinkedList<T>::addToEnd(const T &el)
{
	Node *tmp = new Node(el);	

	if (tail != nullptr){
		tmp->prev = tail;
		tail->next = tmp;
	} 
	else {
		head = tmp;
	}

	tail = tmp;
	count++;
}

template <typename T>
void DoubleLinkedList<T>::print()
{
	Node* tmp = head;
	while (tmp != nullptr)
	{
		cout << tmp->data << ' ';
		tmp = tmp->next;
	}
	cout << endl << endl;
}

template<typename T>
bool DoubleLinkedList<T>::symmetric() {

	Node* tmpLeft = head;
	Node* tmpRight = tail;

	bool noErr = true; 
	int i = 0;

	while ( i != count/2 && noErr)
	{ 
		if (tmpLeft->data == tmpRight->data) 
		{ 
			tmpLeft = tmpLeft->next; 
			tmpRight = tmpRight->prev; 
		} 
		else 
			noErr = false; 

		i++; 
	}

	return noErr;
}

template<typename T>
int DoubleLinkedList<T>::cntUniqueNodes()
{
	set<T> uniqueEl; //пустое множество

	Node *tmp;
	for (tmp = head; tmp; tmp = tmp->next)
	{
		uniqueEl.insert(tmp->data);
	}
	//copy(uniqueEl.begin(), uniqueEl.end(), ostream_iterator<T>(cout, " ")); //вывод элементов множества 

	return int(uniqueEl.size());
}

template<typename T>
void DoubleLinkedList<T>::delMetNodes()
{
	Node *compared, *tmp, *link;
	for (compared = head; compared != nullptr ; compared = compared->next) 
	{
		link = compared;
		for (tmp = link->next; tmp != nullptr; )
		{
			if (tmp->data == compared->data) {
				link->next = tmp->next;
				delete(tmp); 
				count--;
				tmp = link->next;	
				if (tmp != nullptr) tmp->prev = link; 
			}
			else {
				link = tmp;
				tmp = tmp->next;
			}
		}
	}
	//после удалений ставим хвост на место
	for (tmp = head; tmp->next; tmp = tmp->next) {}
	tail = tmp;

}

template<typename T>
void DoubleLinkedList<T>::sortList() //сортировка по возрастанию
{	

	Node *tmp1, *tmp2, *minNode;
	T i;
	for(tmp1 = head; tmp1 != tail; tmp1 = tmp1->next)
	{
		minNode = tmp1;
		for (tmp2 = tmp1; tmp2; tmp2=tmp2->next){
			if (tmp2->data < tmp->data) { minNode = tmp2;}
		}
		i = tmp1->data; 
		tmp1->data = minNode->data;
		minNode->data = i;
	}

}

template<typename T>
void DoubleLinkedList<T>::reverseList()
{
	if (head == tail) return;

	Node* tmpLeft = head;
	Node* tmpRight = tail;
	Node* tmp;


	tail->next = head->next;
	head->next->prev = tail;
	tail->prev->next = head;
	head->prev = tail->prev;
	tail->prev = nullptr;
	head->next = nullptr;

	tmp = head;
	head = tail;
	tail = tmp;
	
	tmpLeft = head->next;
	tmpRight = tail->prev;

	while (tmpLeft != tmpRight && tmpLeft->prev != tmpRight)
	{ 
		tmpLeft->next->prev = tmpRight;
		tmpLeft->prev->next = tmpRight;

		tmpRight->prev->next = tmpLeft;
		tmpRight->next->prev = tmpLeft;

		tmp = tmpRight->next;
		tmpRight->next = tmpLeft->next;
		tmpLeft->next = tmp;

		tmp = tmpRight->prev;
		tmpRight->prev = tmpLeft->prev;
		tmpLeft->prev = tmp;

	}
}
