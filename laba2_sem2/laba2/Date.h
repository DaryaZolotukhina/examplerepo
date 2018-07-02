#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class Date
{
	int day;
	int month;
	int year;

public:

	bool operator == (const Date&);

	void operator = (const Date&);


	bool operator < (const Date&);

	bool is_leap(unsigned int);

	bool is_valid(Date);

	Date get_date();

	Date from_string_date(string);

	string to_string_date();

	int cmp(const Date&, const Date& );

	Date();

	Date(int,  int,  int);

	friend int input_number(int min, int max, string);

	~Date();
};

#endif