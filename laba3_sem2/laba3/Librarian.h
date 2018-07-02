#pragma once
#include <iostream>
#include <vector>
#include "Library.h"
#include "Date.h"
#include "Reader.h"
#include "Book.h"


class Librarian{
private:
	
	Library<Book> operations;
	void change_vector_of_readers();
	void change_vector_of_books();
	
public:
	//vector<Book> books;
	//vector<Reader> readers;

	void change_book();
	void delete_book();
	void delete_reader();
	void add_reader(Book);
	void add_reader();
	void change_reader(int, Book); 
	void change_reader();
	void Menu();

	//vector<Book>& get_all_books();
	//vector<Reader>& get_all_readers();
	void print_all_readers();
	Librarian();
	~Librarian();
};

