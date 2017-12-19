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

	while (head) //Пока по адресу на начало списка что-то есть
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

	Node *tmp1, *tmp2;
	T i;
	for (tmp1 = head; tmp1; tmp1 = tmp1->next )
		for (tmp2 = head; tmp2; tmp2 = tmp2->next )
			if (tmp1->data < tmp2->data ){
				i = tmp1->data;
				tmp1->data = tmp2->data;
				tmp2->data = i;
			}	
}

template<typename T>
void DoubleLinkedList<T>::reverseList()
{
	Node* tmpLeft = head;
	Node* tmpRight = tail;

	int i = 0;
	T tmpData;

	while (i != count/2)
	{ 
		tmpData = tmpLeft->data;
		tmpLeft->data = tmpRight->data;
		tmpRight->data = tmpData; 

		tmpLeft = tmpLeft->next;
		tmpRight = tmpRight->prev;

		i++; 
	}
}
