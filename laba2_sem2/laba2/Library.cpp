#include "Library.h"

template<class T>
void Library<T>::add(T& rec) {
	records.push_back(rec);
}

template<class T>
Record Library<T>::change(T& person) {
	unsigned short int choose;
	cout << "Что вы хотете изменить?" << endl
		<< "1 - Номер читательского билета;" << endl
		<< "2 - Фамилию абонента;" << endl
		<< "3 - Дату получения книги;" << endl
		<< "4 - Дату возврата книги;" << endl
		<< "5 - Автора книги;" << endl
		<< "6 - Название книги;" << endl
		<< "7 - Год издания книги;" << endl
		<< "8 - Издателство книги;" << endl
		<< "9 - Цену книги." << endl;
	cin >> choose;
	system("cls");
	switch (choose)
	{
	case 1:
	{
		unsigned int card_;
		card_ = input_number(1, 999999, "Введите новый номер читательского билета: ");
		person.set_card(card_);
		break;
	}
	case 2:
	{
		string surname_;
		cout << "Введите новую фамилию:" << endl;
		cin >> surname_;
		person.set_surname(surname_);
		break;
	}
	case 3:
	{
		cout << "Введите новую дату выдачи: " << endl;
		Date date_;
		person.set_date_get(date_.get_date());
		break;
	}
	case 4:
	{
		cout << "Введите новую дату возврата:" << endl;
		Date date_;
		person.set_date_return(date_.get_date());
		break;
	}
	case 5:
	{
		string author;
		cout << "Введите нового автора: " << endl;
		cin >> author;
		person.set_author(author);
		break;
	}
	case 6:
	{
		string title;
		cout << "Введите новое название: " << endl;
		cin >> title;
		person.set_title(title);
		break;
	}
	case 7:
	{
		unsigned int year;
		year = input_number(1400, 2018, "Введите год издания книги: ");
		person.set_year_book(year);
		break;
	}
	case 8:
	{
		string house;
		cout << "Введите название издательства: " << endl;
		cin >> house;
		person.set_pub_house(house);
		break;
	}
	case 9:
	{
		unsigned int pr;
		pr = input_number(1, 10000, "Введите новую цену книги в рублях: ");
		person.set_price(pr);
		break;
	}
	default:
		break;
	}
	return person;
}

template<class T>
void Library<T>::remove(int num) {
	if (num)	{
		records.erase(records.begin() + num - 1);
	}
}

template<class T>
vector<T>& Library<T>::get_vector() {
	return records;
}


template<class T>
bool Library<T>::load_from_file(T(*f)(ifstream&), string file_name)
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


		input.close();
		return true;
	}
}


template<class T>
void Library<T>::read_from_console(T(*f)())
{
	int n;
	T elem;
	do
	{
		records.push_back(f());
		n = input_number(0, 1, "Вы хотите добавить новый элемент? (1 - да, 0 - нет)\nВаш выбор: ");
	} while (n != 0);
}

template<class T>
vector<T> Library<T>::LinearySearch(T search_elem, bool(*Equal)(T, T))
{
	vector<T> NewVect;
	for (auto iter = records.begin(); iter != records.end(); iter++){
		if (Equal(search_elem, *iter))
			NewVect.push_back(*iter);
	}
	return NewVect;
}

template<class T>
vector<T> Library<T>::BinarySearch(T find_element, bool(*Compare)(T, T), bool(*Equal)(T, T)){
	vector<T> NewVect;

	sort(records.begin(), records.end(), Compare);
	auto index = lower_bound(records.begin(), records.end(), find_element, Compare);
	
		while ((index != records.end()) && Equal(find_element, *index)){
			NewVect.push_back(*index);
			++index;
		}
	return NewVect;
}

template<class T>
Library<T>::Library(){
	records.reserve(MAX_ELEM);
}

template<class T>
Library<T>::~Library()
{
}


template<class T>
void Library<T>::print_to_file(vector<T> items, string (*f)(T, int), string file_name)
{
	ofstream fout(file_name);
	if (fout)
	{
		vector<T>::const_iterator pos;
		int count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos) {

			fout << f(*pos, count) << ' ';
			count++;
		}
		cout << endl;
		fout.close();
	}
	else
		cout << "Ошибка!" << endl;
}


template<class T>
void Library<T>::print_to_screen(vector<T> items, void(*f) (T))
{
	vector<T>::const_iterator pos;
	int count = 1;
	for (pos = items.begin(); pos != items.end(); ++pos) {
		cout << "Запись №" << count << endl;
		f(*pos);
		count++;
	}
}



