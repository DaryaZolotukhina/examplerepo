#include "Librarian.h"

void Librarian::add_reader() {
	Reader reader;
	Book book_;
	readers.push_back(reader.add(book_));
}

void Librarian::add_reader(Book book_) {
	if (!book_.get_available())
	{
		Reader reader;
		readers.push_back(reader.add(book_));
		book_.set_available(reader.get_card());
		book_.get_history_book().push_back(reader.get_date_get());
	}
	else
		cout << "Книга недоступна!" << endl;	
}

void Librarian::change_reader() {
	unsigned short int choose;
	print_all_readers();
	int numb = input_number(0, readers.size(), "Введите номер читателя, поле которого хотите изменить,\nиначе - 0:\n");
	if (numb) {
		cout << "Что вы хотете изменить?" << endl
			<< "1 - Номер читательского билета;" << endl
			<< "2 - Фамилию абонента;" << endl;
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
		{
			unsigned int card_;
			card_ = input_number(1, 999999, "Введите новый номер читательского билета: ");
			readers[numb - 1].set_card(card_);
			break;
		}
		case 2:
		{
			string surname_;
			cout << "Введите новую фамилию:" << endl;
			cin >> surname_;
			readers[numb - 1].set_surname(surname_);
			break;
		}
		default:
			break;
		}
	}
}

void Librarian::change_book() {
	operations.print_to_screen(get_all_books(), print_record);
	int numb = input_number(0, books.size(), "Введите номер книги, информацию которой надо изменить,\nиначе - 0:\n"),
		choose;
	if (numb) {
		cout << "Что вы хотете изменить?" << endl
			<< "1 - Автора книги;" << endl
			<< "2 - Название книги;" << endl
			<< "3 - Год издания книги;" << endl
			<< "4 - Издателство книги;" << endl
			<< "5 - Цену книги." << endl;
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
		{
			string author;
			cout << "Введите нового автора: " << endl;
			cin >> author;
			books[numb - 1].set_author(author);
			break;
		}
		case 2:
		{
			string title;
			cout << "Введите новое название: " << endl;
			cin >> title;
			books[numb - 1].set_title(title);
			break;
		}
		case 3:
		{
			unsigned int year;
			year = input_number(1400, 2018, "Введите год издания книги: ");
			books[numb - 1].set_year_book(year);
			break;
		}
		case 4:
		{
			string house;
			cout << "Введите название издательства: " << endl;
			cin >> house;
			books[numb - 1].set_pub_house(house);
			break;
		}
		case 5:
		{
			unsigned int pr;
			pr = input_number(1, 10000, "Введите новую цену книги в рублях: ");
			books[numb - 1].set_price(pr);
			break;
		}
		default:
			break;
		}
	}
}

void Librarian::change_reader(int numb, Book book_) {
	if (!book_.get_available()){
		readers[numb - 1].set_book(book_);
		book_.set_available(readers[numb - 1].get_card());

		cout << "Введите дату выдачи: " << endl;
		Date date_get_;
		readers[numb - 1].set_date_get(date_get_.get_date());

		cout << "Введите дату возврата: " << endl;
		Date date_return_;
		readers[numb - 1].set_date_return(date_return_.get_date());

		book_.get_history_book().push_back(readers[numb - 1].get_date_get());
	}
}

void Librarian::delete_reader() {
	print_all_readers();
	int numb = input_number(0, readers.size(), "Введите номер читателя, которого хотите удалить,\nиначе - 0:\n");
	if (numb)
		readers.erase(readers.begin() + numb - 1);
}

void Librarian::delete_book() {
	operations.print_to_screen(get_all_books(), print_record);
	int numb = input_number(0, books.size(), "Введите номер книги, которую надо удалить,\nиначе - 0:\n");
	if (numb){
		books.erase(books.begin() + numb - 1);
	}
}



void Librarian::change_vector_of_books(){
	int numb = input_number(0, 3, "1 - Добавить\n2 - Удалить\n3 - Изменить\n0 - Выход\n");
	Book book;
	switch (numb)
	{
	case 1:
	{
		books.push_back(book.add_book());
		break;
	}
	case 2:
	{
		delete_book();
		break;
	}
	case 3:
	{
		change_book();
		break;
	}
	default:
		break;
	}
}

void Librarian::change_vector_of_readers() {
	int numb = input_number(0, 3, "1 - Добавить\n2 - Удалить\n3 - Изменить\n0 - Выход\n");
	Reader reader;
	Book book;
	switch (numb)
	{
	case 1:
		readers.push_back(reader.add(book));
		break;
	case 2:
		delete_reader();
		break;
	case 3:
		change_reader();
		break;
	default:
		break;
	}
}