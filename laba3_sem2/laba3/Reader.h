#pragma once
#include <iostream>
#include<vector>
#include"Date.h"
#include<string>
#include"Book.h"
#include"Library.h"

class Reader
{
private:

	int library_card;
	string surname;
	Book book;
	Date date_get;
	Date date_return;	

public:
	Reader();
	~Reader();

	int get_card();
	string get_surname();
	Date get_date_get();
	Date get_date_return();
	Book get_book();

	void set_card(int);
	void set_book(Book);
	void set_surname(string);
	void set_date_get(Date);
	void set_date_return(Date);

	Reader add(Book);
	
	friend bool search_element_date(Reader, Reader);
	friend bool sort_date_beg(Reader , Reader );

	friend void print_book_date(Reader r);
	friend void print_reader(Reader c);

	static Reader ReadReaderFromFile(ifstream& in);
	static void WriteReaderToFile(Reader a, ofstream& os);


	friend Reader from_string_reader(ifstream&);

};

