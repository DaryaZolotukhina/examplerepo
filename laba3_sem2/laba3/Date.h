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
	const int monthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

public:

	bool operator == (const Date&);

	void operator = (const Date&);

	Date operator+ ( int);

	bool operator < (const Date&);
	bool operator > (const Date&);

	bool is_leap( int);

	bool is_valid(Date);

	Date get_date();

	Date from_string_date(string);

	string to_string_date();

	int last_day_in_month(const int&, const int&);

	int cmp(const Date&, const Date& );


	Date();

	Date(int,  int,  int);

	friend int input_number(int min, int max, string);

	~Date();
};

#endif