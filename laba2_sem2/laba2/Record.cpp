#include "Record.h"

unsigned int Record::get_card() {
	return library_card;
}
string Record::get_surname() {
	return surname;
}
Date Record::get_date_get() {
	return date_get;
}
Date Record::get_date_return() {
	return date_return;
}
string Record::get_author(){
	return author;
}
string Record::get_title() {
	return title;
}
unsigned int Record::get_year_book() {
	return year_book;
}
string Record::get_pub_house() {
	return pub_house;
}
unsigned int Record::get_price() {
	return price;
}

void Record::set_card(unsigned int library_card_) {
	library_card = library_card_;
}
void Record::set_surname(string surname_) {
	surname = surname_;
}
void Record::set_date_get(Date date_get_) {
	date_get = date_get_;
}
void Record::set_date_return(Date date_return_) {
	date_return = date_return_;
}
void Record::set_author(string author_) {
	author = author_;
}
void Record::set_title(string title_) {
	title = title_;
}
void Record::set_year_book(unsigned int year_) {
	year_book = year_;
}
void Record::set_pub_house(string pub_house_) {
	pub_house = pub_house_;
}
void Record::set_price(unsigned int price_) {
	price = price_;
}
bool Record::operator ==(Record record) {
	return (library_card == record.library_card && surname == record.surname && date_get == record.date_get && date_return == record.date_return &&
		author == record.author && pub_house == record.pub_house);
}

// поиск равного элемента по выбранному критерию
//1 - по номеру читательского билета 
//2 - по автору 
//3 - по издательству 
//4 - по дате возврата (просрочено)  
bool search_element_card( Record first, Record second){
	return (first.get_card() == second.get_card());
}

bool search_element_author(Record first, Record second){
	return (first.get_author() == second.get_author());
}

bool search_element_pub_house(Record first, Record second){
	return (first.get_pub_house() == second.get_pub_house());
}

bool search_element_date_return(Record rec, Record rec2){
	return (rec2.get_date_return() < rec.get_date_return() );
}


// ввод критерия поиска в зависимости от выбранного типа 
//1 - по номеру читательского билета 
//2 - по автору 
//3 - по издательству 
//4 - по дате возврата (просрочено) 
Record search_type(int type_search){
	Record result;
	switch (type_search)
	{
	case 1:
	{
		result.set_card(input_number(1, 999999, "Введите номер читательского билета (1 - 999999): "));
		return result;
		break;
	}
	case 2:
	{
		cout << "Введите автора: " << endl;
		string auth;
		cin >> auth;
		result.set_author(auth);
		return result;
		break;
	}
	case 3:
	{
		cout << "Введите издательство: " << endl;
		string house;
		cin >> house;
		result.set_pub_house(house);
		return result;
		break;
	}
	case 4:
	{
		cout << "Введите сегодняшнюю дату: " << endl;
		Date date;
	
		result.set_date_return(date.get_date());
		return result;
		break;
	}
	default:
		return result;
	}
}

bool sorte_card(Record n, Record m){
	return n.get_card() > m.get_card();
}

bool sorte_author(Record n, Record m){
	return n.get_author() > m.get_author();
}

bool sorte_pub_house(Record n, Record m){
	return n.get_pub_house() > m.get_pub_house();
}

bool sorte_date_return(Record n, Record m){
	return !(n.get_date_return() < m.get_date_return());
}

Record::Record(){
	library_card = 0;
	surname = "";
	date_get;
	date_return;
	author = "";
	title = "";
	year_book = 0;
	pub_house = "";
	price = 0;
}



Record add_record() {
	Record rec;
	cout << "Введите информацию об абоненте." << endl;

	unsigned int card_;
	card_  = input_number(1, 999999, "Введите номер читательского билета: ");
	rec.set_card(card_);

	cout << "Фамилия: " << endl;
	string surname_;
	cin >> surname_;
	rec.set_surname(surname_);
	cout << endl;

	cout << "Введите дату выдачи: " << endl;
	Date date_get_;
	rec.set_date_get(date_get_.get_date());

	cout << "Введите дату возврата: " << endl;
	Date date_return_;
	rec.set_date_return(date_return_.get_date());

	cout << "Автор: " << endl;
	string author_;
	cin >> author_;
	rec.set_author(author_);
	cout << endl;

	cout << "Название: " << endl;
	string title_;
	cin >> title_;
	rec.set_title(title_);
	cout << endl;
	
	unsigned int year_;
	year_ = input_number(1400, 2018, "Введите год издания книги: ");
	rec.set_year_book(year_);

	cout << "Введите название издательства:" << endl;
	string house_;
	cin >> house_;
	rec.set_pub_house(house_);
	cout << endl;

	unsigned int price_;
	price_ = input_number(1, 10000, "Введите новую цену книги в рублях: ");
	rec.set_price(price_);	

	return rec;
}

//считывание структуры "запись" из строки 
Record from_string_record(ifstream& input) {
	Record result;
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
			date_ =	result.get_date_get().from_string_date(s.substr(wrd.length(), s.length()));
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
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Автор: ";
			result.set_author(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Название: ";
			result.set_title(s.substr(wrd.length(), s.length()));
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

	}
	catch (...)
	{
		cout << "Ошибка записи в файл!" << endl;
	}
	return result;
}

string to_string_record(Record record, int count) {
	string info ="Запись №" + to_string(count) + "\n № читательского билета:  " + to_string(record.library_card) + "\n Фамилия абонента: " + record.surname + "\n Дата выдачи: " +
		record.date_get.to_string_date() + "\n Дата возврата: " + record.date_return.to_string_date() +
		"\n Автор: " + record.author + "\n Название : " + record.title + "\n Год издания: " + to_string(record.year_book) + "\n Идательство: " +
		record.pub_house + "\n Цена: " + to_string(record.price) + "\n";

	return info;
}

// функция вывода структуры "запись" на консоль 
void print_record(Record c)
{
	cout << "Номер читательского билета: " << to_string(c.get_card()) << endl;
	cout << "Фамилия абонента: " << c.get_surname() << endl;
	cout << "Дата выдачи: " << c.get_date_get().to_string_date() << endl;
	cout << "Дата возврата: " << c.get_date_return().to_string_date() << endl;
	cout << "Автор: " << c.get_author() << endl;
	cout << "Название: " << c.get_title() << endl;
	cout << "Год издания: " << to_string(c.get_year_book()) << endl;
	cout << "Идательство: " << c.get_pub_house() << endl;
	cout << "Цена: " << to_string(c.get_price()) << endl;
}

// перегруженный оператор присваивания для записей
Record& Record::operator = (Record c)
{
	library_card = c.library_card;
	surname = c.surname;
	date_get = c.date_get;
	date_return = c.date_return;
	author = c.author;
	title = c.title;
	year_book = c.year_book;
	pub_house = c.pub_house;
	price = c.price;
	
	return *this;
}

