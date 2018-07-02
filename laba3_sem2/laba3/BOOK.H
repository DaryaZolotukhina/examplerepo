#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include"Date.h"

using namespace std;

class Book
{
private:

	string author;
	string title;
	int year_book;
	string pub_house;// publishing house
	int price;
	int  is_available;

public:
	
	string get_author();
	string get_title();
	int get_year_book();
	string get_pub_house();
	int get_price();
	int  get_available();

	
	void set_author(string);
	void set_title(string);
	void set_year_book(int);
	void set_pub_house(string);
	void set_price(int);
	void set_available(int);

	Book();

	friend bool search_element_year(Book, Book);
	friend bool search_element_author(Book, Book);
	friend bool search_element_title(Book, Book);
	friend bool search_element_availability(Book, Book);
	friend bool sort_availability(Book, Book);
	friend bool search_non_available(Book, Book);
	friend	Book search_type(int);

	friend void print_record(Book);
	friend Book from_string_record(ifstream&);
	friend string to_string_record(Book, int);

	Book& operator= (Book);

	static void WriteBookToFile(Book a, ofstream& os);
	static Book ReadBookFromFile(ifstream& in);
		
	bool operator == (const Book&);

	Book add_book();
};


#endif
