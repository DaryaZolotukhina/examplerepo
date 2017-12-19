/*
Здоровцова Елена, 91 гр
2.
Реализовать шаблон класса двусвязный (двунаправленный) список (DoublyLinkedList<X>), хранящий элементы произвольного типа. 
Класс должен содержать:
>> Инициализация списка; 
>> Добавление элемента в начало списка; 
>> Добавление элемента в конец списка; 
>> Показ всех элементов списка. 
с)
>> Определение, является ли список симметричным; 
>> Определение, сколько различных значений содержится в списке;
>> Удаление из списка элементов, значения которых уже встречались в предыдущих элементах; 
>> Изменение порядка элементов на обратный; 
>> Сортировка элементов списка. 
*/

#include <iostream>
#include <string>
#include "DoubleLinkedList.cpp"

template <typename T>
void Program(DoubleLinkedList<T> A)
{
	int k;
	do {
		cout << "Menu:\n"
			<< "1.Get size\n"
			<< "2.Add to the end\n"
			<< "3.Add to the beginning\n"
			<< "4.Find out if the list is SYMMETRICAL\n"
			<< "5.Find how much different elemens are in the list\n"
			<< "6.Delete nodes that have been already met\n"
			<< "7.Reverse list\n"
			<< "8.Sort list\n"
			<< "9.Print\n"
			<< "0.Exit\n"
			<< "Your choise: ";
		cin >> k;
		switch (k)
		{
		case 1: cout << A.getLength() << endl; break;
		case 2: {
			T n;
			cout << "Input new elem: " << endl;
			cin >> n;
			A.addToEnd(n);
				} break;
		case 3: {
			T n;
			cout << "Input new elem: " << endl;
			cin >> n;
			A.addToBeg(n);
				} break;
		case 4: {
			if (A.getLength() == 0) cout << "the list is empty" << endl; break;
			if (A.symmetric()) 
				cout << "\nYes, it is!" << endl << endl;
			else cout << "\nNo, it isn't!" << endl << endl;
				} break;
		case 5: cout << "\nNumber of unique elements = " << A.cntUniqueNodes() << endl << endl; break;
		case 6: {
			if (A.getLength() == 0) cout << "the list is empty" << endl; break;
			A.delMetNodes();
			cout << "Done!" << endl << endl;
				}break;
		case 7: {
			if (A.getLength() == 0) cout << "the list is empty" << endl; break;
			A.reverseList();
			cout << "Done!" << endl << endl;	
				}break;
		case 8: {
			if (A.getLength() == 0) cout << "the list is empty" << endl; break;
			A.sortList();
			cout << "Sorted!" << endl << endl;
				}break;
		case 9: {
			if (A.getLength() == 0) cout << "the list is empty" << endl; break;
			A.print(); break;
				}
		case 0: cout << "Now exit"; break;
		default: cout << "error inputing, try again" << endl;
		}
	} while (k != 0);
}

void Test(DoubleLinkedList<int> A, DoubleLinkedList<string> B)
{

	int arrInt[] = { 1, 5, 4, 3, 4, 5, 1 };
	for (int i = 0; i < 7; ++i) {
		A.addToEnd(arrInt[i]);
	}
	cout << "\ncreated list:" << endl;
	A.print();

	if (A.symmetric()) 
		cout << "the list is symmetric!" << endl << endl;
	else cout << "the list is not symmetric!" << endl << endl;

	A.delMetNodes();
	cout << "nodes that have been already met are deleted. new list:" << endl;
	A.print();
	
	A.sortList();
	cout << "list have been sorted. new list:" << endl;
	A.print();

	A.reverseList();
	cout << "reserved list:" << endl;
	A.print();


	string arrStr[] = {"a", "bb", "cb", "bb", "zzz", "a", "xyz"};
	for (int i = 0; i < 7; ++i) {
		B.addToEnd(arrStr[i]);
	}
	cout << "\ncreated list:" << endl;
	B.print();

	if (B.symmetric()) 
		cout << "the list is symmetric!" << endl << endl;
	else cout << "the list is not symmetric!" << endl << endl;

	B.delMetNodes();
	cout << "nodes that have been already met are deleted. new list:" << endl;
	B.print();
	
	B.sortList();
	cout << "list have been sorted. new list:" << endl;
	B.print();

	B.reverseList();
	cout << "reserved list:" << endl;
	B.print();

    
	cin.get();
}


int main()
{
	DoubleLinkedList<int> A;
	DoubleLinkedList<string> B;

	int ans;
	cout << "Select the action: \n1 - see written tests,\n2 - check the program yourself" << endl;
	cin >> ans;
	switch (ans)
	{
	case 1: Test(A, B); break;

	case 2: {
		int k;
		cout << "Select data type: \n1 - int, 2 - string" << endl;
		cin >> k;
			if (k == 1) Program(A); 
			else if (k == 2) Program(B);
		} break;

	}	

	cin.get();
	return 0;
}