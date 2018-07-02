#include "Date.h"

//проверка на високостность
bool Date::is_leap(unsigned int year) {
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

// проверка даты на корректность 
bool Date::is_valid(Date date_) {
	// если год високосный если не високосный 
	if ((date_.month == 2) && ((date_.day > 29 && is_leap(date_.year)) || (date_.day > 28 && !is_leap(date_.year))))
	{
		cout << "Неверное кол-во дней в феврале!" << endl;
		return false;
	}
	//кол-во дней в месяце 
	if (date_.month == 4 || date_.month == 6 || date_.month == 9 || date_.month == 11)
	{
		if (date_.day > 30)
		{
			cout << "Неверное кол-во дней в месяце!";
			return false;
		}
	}
	//кол-во дней не может быть больше 31 и меньше 1 -- проверяется при вводе
	return true;
}

Date Date::get_date() {

	Date date_;
	do
	{
		date_.day = input_number(1, 31, "Ввод даты:\nВведите день (1-31): ");
		date_.month = input_number(1, 12, "Введите номер месяца (1-12): ");
		date_.year = input_number(1700, 2050, "Введите год (1700-2050): ");
	} while (!is_valid(date_));

	return date_;
}

string Date::to_string_date() {
	return to_string(day) + '.' + to_string(month) + '.' + to_string(year);
}

bool Date::operator == (const Date& oper1) {
	return cmp(*this, oper1) == 0;
}

void Date::operator = (const Date& date) {
	day = date.day;
	month = date.month;
	year = date.year;
}

Date Date::from_string_date(string str){
	Date result;
	try
	{
		istringstream is(str);
		string s;
		if (getline(is, s, '.'))
			result.day = atoi(s.c_str());
		if (getline(is, s, '.'))
			result.month = atoi(s.c_str());
		if (getline(is, s, '.'))
			result.year = atoi(s.c_str());
	}
	catch (...)
	{
		cout << "Ошибка записи в файл!" << endl;
	}
	return result;
}

Date::Date( int Days,  int Month,  int Year) {
	day = Days;
	month = Month;
	year = Year;
}

Date::Date()
{
	day = 1;
	month = 1;
	year = 1700;
}

bool Date::operator < (const Date& oper1) {
	return cmp(*this, oper1) < 0;
}

int Date::cmp(const Date& lval, const Date& rval) {
	if (lval.year != rval.year)
		return lval.year - rval.year;
	if (lval.month != rval.month)
		return lval.month - rval.month;
	if (lval.day != rval.day)
		return lval.day - rval.day;
	return 0;
}

//template <class Type>
int input_number(int min, int max, string mesg)
{
	int n;
	std::cout << mesg;
	do
	{
		cout << "Введите число из диапазона!\n";
		while ((!(cin >> n)) || cin.get() != '\n' )
		{
			std::cout << "Неправильный ввод!  Повторите ввод!\n";
			cin.clear(); 
			while (cin.get() != '\n');
		}
	} while ((n < min) || (n > max));
	cout << endl;
	return n;
}

Date::~Date()
{
}
