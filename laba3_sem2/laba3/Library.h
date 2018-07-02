#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include<iostream>
#include<vector>
#include"Book.h"
#include"Reader.h"
#include"Date.h"

#include<iterator>
#include<algorithm>

using namespace std;

//#define MAX_ELEM 100

template <class T>
class Library
{

public:
	vector<T> records;
	Library() {
	}
	 
	int size()
	{
		return records.size();
	}

	bool load_from_file(T(*f)(ifstream&), string file_name)
	{
		ifstream input(file_name);

		if (!input)
		{
			cout << "Ошибка!" << endl;
			return false;
		}
		else
		{
			while (!input.eof())
				records.push_back(f(input));
			//vect.erase(vect.begin() + vect.size() - 1);

			input.close();
			return true;
		}
	}

	void read_from_console(T(*f)()) {
		int n;
		T elem;
		do
		{
			records.push_back(f());
			n = input_number(0, 1, "Вы хотите добавить новый элемент? (1 - да, 0 - нет)\nВаш выбор: ");
		} while (n != 0);
	}

	vector<T> LinearySearch(T search_elem, bool(*Equal)(T, T))
	{
		vector<T> NewVect;
		for (auto iter = records.begin(); iter != records.end(); iter++) {
			if (Equal(search_elem, *iter))
				NewVect.push_back(*iter);
		}
		return NewVect;
	}

	vector<T> BinarySearch(T find_element, bool(*Compare)(T, T), bool(*Equal)(T, T)) {
		vector<T> NewVect;

		sort(records.begin(), records.end(), Compare);
		auto index = lower_bound(records.begin(), records.end(), find_element, Compare);

		while ((index != records.end()) /*&& Equal(*index, find_element)*/) {
			if (Equal(*index, find_element)) 
				NewVect.push_back(*index);
			++index;
		}
		return NewVect;
	}

	void print_to_file(vector<T> items, string(*f)(T, int), string file_name)
	{
		ofstream fout(file_name);
		if (fout)
		{
			vector<T>::const_iterator pos;
			for (pos = items.begin(); pos != items.end(); ++pos) {

				fout << f(*pos, count) << ' ';
			}
			cout << endl;
			fout.close();
		}
		else
			cout << "Ошибка!" << endl;
	}

	void print_to_screen(vector<T> items, void(*f) (T))
	{
		vector<T>::const_iterator pos;
		int count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos) {
			cout << "Запись №" << count << endl;
			f(*pos);
			count++;
			cout << endl;
		}
	}

	bool Library<T>::ReadFromFile(T(*f)(ifstream&), string newfname)
	{
		std::ifstream input;

		input.open(newfname, ios::binary);

		if (!input)
		{
			cout << "Ошибка!" << endl;
			return false;
		}
		else
		{
			int size;
			T  elem;
			input.read((char*)&size, sizeof(int)); 
			for (int i = 0; i < size; i++)
			{
				records.push_back(f(input));
			}

			input.close();
			return true;
		}
	}
	
	void Library<T>::OutputFile(void(*f)(T, ofstream&), string newfname)
	{
		ofstream fout(newfname, ios::binary);
		if (fout)
		{
			int i = records.size();

			fout.write((char*)&i, sizeof(int));

			vector<T>::const_iterator pos;
			for (pos = records.begin(); pos != records.end(); ++pos)
			{
				f(*pos, fout);
			}
		}
	}
	
	//поиск индекса
	int search_ind(T el)
	{
		int s = records.size();
		if ((s <= 0))
		{
			return -1;
		}
		for (int i = 0; i < s; i++)
		{
			if (el == records[i])
			{
				return i;
			}
		}
		return -1;
	}

	~Library()
	{

	}
};
