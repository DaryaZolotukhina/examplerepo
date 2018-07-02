#ifndef LIBRARY_H
#define LIBRARY_H
#include<iostream>
#include<vector>
#include "Record.h"
#include"Date.h"
#include<iterator>
#include<algorithm>

using namespace std;

#define MAX_ELEM 100

template <class T>
class Library
{
	vector<T> records;
public:
	Library();

	void add(T&);
	Record change(T&);
	void remove(int);

	vector<T>& get_vector();

	bool load_from_file(T(*f)(ifstream&), string);

	void read_from_console(T(*f)());
	
	vector<T> LinearySearch(T search_elem, bool(*Equal)(T, T));

	vector<T> BinarySearch(T find_element, bool(*Compare)(T, T), bool(*Equal)(T, T));

	void print_to_file(vector<T> items, string(*f)(T, int), string);

	void print_to_screen(vector<T> items, void(*f) (T));

	~Library();
};
#endif
