#ifndef RECORD_H
#define RECORD_H
#include <iostream>
#include <string>
#include<fstream>
#include"Date.h"


using namespace std;

class Record
{
	unsigned int library_card;
	string surname;
	Date date_get;
	Date date_return;
	string author;
	string title;
	unsigned int year_book;
	string pub_house;// publishing house
	unsigned int price;
public:
	unsigned int get_card();
	string get_surname();
	Date get_date_get();
	Date get_date_return();
	string get_author();
	string get_title();
	unsigned int get_year_book();
	string get_pub_house();
	unsigned int get_price();

	void set_card(unsigned int );
	void set_surname(string);
	void set_date_get(Date);
	void set_date_return(Date);
	void set_author(string);
	void set_title(string);
	void set_year_book(unsigned int);
	void set_pub_house(string);
	void set_price(unsigned int);

	bool operator ==(Record);

	Record();


	friend bool search_element_card(Record, Record);
	friend bool search_element_author(Record, Record);
	friend bool search_element_pub_house(Record, Record);
	friend bool search_element_date_return(Record, Record);

	friend	Record search_type(int);

	friend bool sorte_card(Record, Record);
	friend bool sorte_author(Record, Record);
	friend bool sorte_pub_house(Record, Record);
	friend bool sorte_date_return(Record, Record);

	friend void print_record(Record);

	friend Record from_string_record(ifstream&);

	friend Record add_record();

	friend string to_string_record(Record, int);

	Record& operator= (Record);

};


#endif
