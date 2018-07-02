#include "Reader.h"
#include "HelpUtils.h"

int Reader::get_card() {
	return library_card;
}

string Reader::get_surname() {
	return surname;
}

Date Reader::get_date_get() {
	return date_get;
}

Date Reader::get_date_return() {
	return date_return;
}

Book Reader::get_book() {
	return book;
}

void Reader::set_card(int library_card_) {
	library_card = library_card_;
}

void Reader::set_surname(string surname_) {
	surname = surname_;
}

void Reader::set_date_get(Date date_get_) {
	date_get = date_get_;
}

void Reader::set_date_return(Date date_return_) {
	date_return = date_return_;
}

void Reader::set_book(Book book_){
	book = book_;
}

Reader Reader::add(Book book_) {
	//Reader rec;
	cout << "Введите информацию о читателе." << endl;

	int card_;
	card_ = input_number(1, 999999, "Введите номер читательского билета(1-999999): ");
	library_card = card_;

	cout << "Фамилия: " << endl;
	string surname_;
	cin >> surname_;
	surname = surname_;
	cout << endl;

	book = book_;

	Date date_get_, date_return_;
	date_get = date_get_;
	date_return = date_return_;

	if (book_.get_title() != "")
	{
		cout << "Введите дату выдачи: " << endl;
		date_get = date_get_.get_date();

		//cout << "Введите дату возврата: " << endl;
		//date_return = date_return_.get_date();
		
	}

	
	return *this;
}

Reader::Reader()
{
}

Reader::~Reader()
{
}

Reader from_string_reader(ifstream& input) {
	Reader result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Читательский билет: ";
			result.set_card(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Фамилия абонента: ";
			result.set_surname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Дата выдачи: ";
			Date date_;
			date_ = result.get_date_get().from_string_date(s.substr(wrd.length(), s.length()));
			result.set_date_get(date_);
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Дата возврата: ";
			Date date_;
			date_ = result.get_date_return().from_string_date(s.substr(wrd.length(), s.length()));
			result.set_date_return(date_);
		}
		
		result.book = from_string_record(input);
		/*
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Автор: ";
			result.book.set_author(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Название: ";
			result.book.set_title(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Год издания: ";
			result.set_year_book(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Издательство: ";
			result.set_pub_house(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Цена: ";
			result.set_price(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Наличие: ";
			result.set_available(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "История выдачи: ";
			Date date;
			s = s.substr(wrd.length(), s.length());
			while (!s.length()) {
				result.history_get_book.push_back(date.from_string_date(s.substr(0, 10)));
				s = s.substr(11, s.length());
			}
		}*/
	}
	catch (...)
	{
		cout << "Ошибка чтения из файла!" << endl;
	}
	return result;
}

void Reader::WriteReaderToFile(Reader a, ofstream& os)
{
	os.write((char*)&a.library_card, sizeof(int));
	StringInBinFile(os, a.surname);
	Book::WriteBookToFile(a.book, os);
	string date = a.date_get.to_string_date();
	StringInBinFile(os, date);
	date = a.date_return.to_string_date();
	StringInBinFile(os, date);
}

Reader Reader::ReadReaderFromFile(ifstream& in)
{
Reader b;

in.read((char*)&b.library_card, sizeof(int));
b.surname = StringFromBinFile(in);
b.book = Book::ReadBookFromFile(in);
Date d;
b.date_get = d.from_string_date(StringFromBinFile(in));
b.date_return = d.from_string_date(StringFromBinFile(in));

return b;
}

bool search_element_date(Reader first, Reader second) {
	return (first.get_date_get() > second.get_date_get());
}

bool sort_date_beg(Reader first, Reader second)
{
	return (first.get_date_get() < second.get_date_get());
}

void print_book_date(Reader r) {
	Date date = r.get_date_get();
	cout << date.to_string_date() << endl;
}

void print_reader(Reader c)
{
	cout << "Номер читательского билета: " << to_string(c.get_card()) << endl;
	cout << "Фамилия: " << c.get_surname() << endl;
	if (c.book.get_title() != "") {
		cout << "Автор: " << c.book.get_author() << endl;
		cout << "Название: " << c.book.get_title() << endl;
		cout << "Год издания: " << to_string(c.book.get_year_book()) << endl;
		cout << "Идательство: " << c.book.get_pub_house() << endl;
		cout << "Цена: " << to_string(c.book.get_price()) << endl;
		cout << "Дата выдачи: " << c.get_date_get().to_string_date() << endl;
		//cout << "Дата возврата: " << c.get_date_return().to_string_date() << endl;
	}
}