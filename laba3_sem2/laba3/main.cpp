#include<iostream>
#include <windows.h>
#include <locale.h>
#include "Reader.h"
#include"Library.h"
#include"Book.h"

using namespace std;

int Menu()
{
	cout << " �------------------����-------------------� " << endl;
	cout << "1 - ��������" << endl;
	cout << "2 - ������������" << endl;
	cout << "0 - �����" << endl;
	int n = input_number(0, 2, "��� �����: ");
	cout << "\n";
	return n;
}

Library<Book> library;
Library<Book> books;
Library<Reader> readers;

string out_file_name_books = "Booksbin.dat",
	   out_file_name_readers = "Readersbin.dat";

void librarian_add_reader() {
	Reader reader;
	Book book_;
	readers.records.push_back(reader.add(book_));
}

void print_all_readers() {
	int count = 1;
	for (auto iter = readers.records.begin(); iter != readers.records.end(); iter++) {
		cout << count << ". ����� ������������� ������: " << (*iter).get_card() << "\n   �������: " << (*iter).get_surname() << endl;
		count++;
	}
}

Reader librarian_add_reader(Book book_) {
	Reader reader;
	if (!book_.get_available())
	{
		readers.records.push_back(reader.add(book_));
	}
	else
		cout << "����� ����������!" << endl;
	return reader;
}

void librarian_change_reader() {
	int choose;
	//print_all_readers();
	readers.print_to_screen(readers.records, print_reader);
	int numb = input_number(0, readers.size(), "������� ����� ��������, ���� �������� ������ ��������,\n����� - 0:\n");
	if (numb) {
		cout << "��� �� ������ ��������?" << endl
			<< "1 - ����� ������������� ������;" << endl
			<< "2 - ������� ��������;" << endl;
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
		{
			int card_;
			card_ = input_number(1, 999999, "������� ����� ����� ������������� ������: ");
			
			//������ � ����� ���������
			int index = books.search_ind(readers.records[numb- 1].get_book());
			books.records[index].set_available(card_);

			readers.records[numb - 1].set_card(card_);
			break;
		}
		case 2:
		{
			string surname_;
			cout << "������� ����� �������:" << endl;
			cin >> surname_;
			readers.records[numb - 1].set_surname(surname_);
			break;
		}
		default:
			break;
		}
	}
}

void librarian_change_book() {
	library.print_to_screen(books.records, print_record);
	int numb = input_number(0, books.size(), "������� ����� �����, ���������� ������� ���� ��������,\n����� - 0:\n"),
		choose;
	if (numb) {
		cout << "��� �� ������ ��������?" << endl
			<< "1 - ������ �����;" << endl
			<< "2 - �������� �����;" << endl
			<< "3 - ��� ������� �����;" << endl
			<< "4 - ����������� �����;" << endl
			<< "5 - ���� �����." << endl;
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
		{
			string author;
			cout << "������� ������ ������: " << endl;
			cin >> author;
			books.records[numb - 1].set_author(author);
			break;
		}
		case 2:
		{
			string title;
			cout << "������� ����� ��������: " << endl;
			cin >> title;
			books.records[numb - 1].set_title(title);
			break;
		}
		case 3:
		{
			unsigned int year;
			year = input_number(1400, 2018, "������� ��� ������� �����: ");
			books.records[numb - 1].set_year_book(year);
			break;
		}
		case 4:
		{
			string house;
			cout << "������� �������� ������������: " << endl;
			cin >> house;
			books.records[numb - 1].set_pub_house(house);
			break;
		}
		case 5:
		{
			unsigned int pr;
			pr = input_number(1, 10000, "������� ����� ���� ����� � ������: ");
			books.records[numb - 1].set_price(pr);
			break;
		}
		default:
			break;
		}
	}
}

void librarian_change_reader(int numb, Book book_) {
	if (book_.get_available() == 0) { //���� ����� ��������
		readers.records[numb - 1].set_book(book_);

		int index = books.search_ind(readers.records[numb - 1].get_book());
		books.records[index].set_available(readers.records[numb - 1].get_card());
		//book_.set_available(readers.records[numb - 1].get_card());

		cout << "������� ���� ������: " << endl;
		Date date_get_;
		readers.records[numb - 1].set_date_get(date_get_.get_date());

	}
	else
		cout << "��������� ����� �� ��������!" << endl;
}

void librarian_delete_reader() {
	print_all_readers();
	int numb = input_number(0, readers.size(), "������� ����� ��������, �������� ������ �������,\n����� - 0:\n");
	
	if (numb) {
		int index = books.search_ind(readers.records[numb - 1].get_book());
		books.records[index].set_available(0); //����� ���������� ��������
		readers.records.erase(readers.records.begin() + numb - 1);
	}

}

void librarian_delete_book() {
	library.print_to_screen(books.records, print_record);
	int numb = input_number(0, books.size(), "������� ����� �����, ������� ���� �������,\n����� - 0:\n");
	if (numb) {
		books.records.erase(books.records.begin() + numb - 1);
	}
}

void librarian_change_vector_of_books() {
	int numb = input_number(0, 3, "1 - ��������\n2 - �������\n3 - ��������\n0 - �����\n");
	Book book;
	switch (numb)
	{
	case 1:
	{
		books.records.push_back(book.add_book());
		break;
	}
	case 2:
	{
		librarian_delete_book();
		break;
	}
	case 3:
	{
		librarian_change_book();
		break;
	}
	default:
		break;
	}
}

void librarian_change_vector_of_readers() {
	int numb = input_number(0, 3, "1 - ��������\n2 - �������\n3 - ��������\n0 - �����\n");
	Reader reader;
	Book book;
	switch (numb)
	{
	case 1:
		//readers.records.push_back(reader.add(book));
		librarian_add_reader();
		break;
	case 2:
		librarian_delete_reader();
		break;
	case 3:
		librarian_change_reader();
		break;
	default:
		break;
	}
}

void set_function(int numb, bool(*&compare)(Book, Book))
{
	switch (numb)
	{
	case 1:
		compare = search_element_title;
		break;
	case 2:
		compare = search_element_author;
		break;
	case 3:
		compare = search_element_year;
		break;
	case 4:
		compare = search_element_availability;
		break;
	}
}

int menu_reader_pos() {
	cout << "\n �------------------���� ��������-------------------� " << endl
		<< "1 - ����� �����" << endl
		<< "2 - ����� �����" << endl
		<< "0 - �����" << endl;
	int n = input_number(0, 2, "��� �����: ");
	cout << "\n";
	return n;
}
//���� �������� 
void menu_reader(int numb_read) {
	
	int n = menu_reader_pos();
	while (n != 0) {
		switch (n)
		{
		case 1:
		{

			if (numb_read && (readers.records[numb_read - 1].get_book().get_title() != ""))  {
				cout << "� ��� ��� ���� ����� �� �����! ���������� ������� ����� �� � ����������!\n";
				break; 
			}

			int numb,
				get = input_number(1, 2, "1 - ����� ����� �� ��������\n2 - ����� ���� ����\n\n");
			vector<Book> subset;
			if (get == 1) {
				bool(*compare)(Book, Book) = NULL;
				Book search_elem;
				numb = input_number(1, 4, "�������� ��� ������:\n 1 - �� ��������\n 2 - �� ������\n 3 - �� ���� �������\n 4 - �� ����������� \n��� �����: ");
				search_elem = search_type(numb);
				set_function(numb, compare);
				subset = books.LinearySearch(search_elem, compare);
				system("cls");

				if (subset.size() != 0)
					library.print_to_screen(subset, print_record);
				else
					cout << "�������� �� �������" << endl;
			}
			else
				library.print_to_screen(books.records, print_record);

			if (((get == 1) && (subset.size() == 0)) || ((get == 2) && (books.size() == 0))) //���� ��� ����
				break;

			numb = input_number(0, 1, "�� �������, ��� ������ ����� �����? 1 - ��, 0 - ���:\n");
			if (numb) {
				int num_book;
				Book choosed_book;
				if (get == 1) { 
					num_book = input_number(1, subset.size(), "������� ����� �������� �����: ");
					choosed_book = subset[num_book - 1];
				}
				else {
					num_book = input_number(1, books.records.size(), "������� ����� �������� �����: ");
					choosed_book = books.records[num_book - 1];
				}
				int index = books.search_ind(choosed_book);

				if (numb_read) {
					librarian_change_reader(numb_read, choosed_book);

					books.records[index].set_available(readers.records[numb_read - 1].get_card());

				}
				else { //���� �������� �����
					Reader r;
					r = librarian_add_reader(choosed_book);

					books.records[index].set_available(r.get_card());
					numb_read = readers.records.size()-1;

				}
			}
			break;
			system("cls");

		}
		case 2:
		{
			if (numb_read && readers.records[numb_read - 1].get_book().get_title() != "") {
				Book book;
				Date date;

				int index = books.search_ind(readers.records[numb_read - 1].get_book());
				books.records[index].set_available(0);

				//readers.records[numb_read - 1].get_book().set_available(0);
				readers.records[numb_read - 1].set_book(book);
				readers.records[numb_read - 1].set_date_get(date);
				cout << "������� ����������� ����.\n";
				date.get_date();
				readers.records[numb_read - 1].set_date_return(date);
			}
			else
				cout << "� ��� ��� �����!" << endl;
		}
		default:
			break;
		}
		n = menu_reader_pos();
	}
}

int menu_librarian_pos() {
	cout << "\n �------------------���� ������������-------------------� " << endl
		<< "1 - �������������� ������ ����" << endl
		<< "2 - �������������� ������ ���������" << endl
		<< "3 - �������� ������� ������ ����" << endl
		<< "4 - �������� ������ ����" << endl
		<< "0 - �����" << endl;
	int n = input_number(0, 4, "��� �����: ");

	return n;
}

//���� ������������ 
void menu_librarian() {

	int numb = menu_librarian_pos();

	while (numb != 0) {
		switch (numb)
		{
		case 1:
		{
			librarian_change_vector_of_books();
			break;
		}
		case 2:
		{
			librarian_change_vector_of_readers();
			break;
		}
		case 3:
		{
			
			vector<Reader> subset;
			Reader r;
			subset = readers.BinarySearch(r, sort_date_beg, search_element_date);
			if (subset.size() != 0)
				readers.print_to_screen(subset, print_book_date);
			else
				cout << "�������� �� �������" << endl;
			break;
		}
		case 4:
		{
			bool(*compare)(Book, Book) = NULL;
			bool(*sort)(Book, Book) = NULL;
			int numb = input_number(0, 2, "1 - �������� ��������� �����\n2 - �������� ����������� �����\n0 - �����\n");
			switch (numb)
			{
			case 1:
			{
				vector<Book> subset = books.BinarySearch(search_type(4), sort_availability, search_element_availability);
				if (subset.size() != 0)
					library.print_to_screen(subset, print_record);
				else
					cout << "�������� �� �������" << endl;
				break;
			}
			case 2:
			{
				vector<Book> subset = books.BinarySearch(search_type(4), sort_availability, search_non_available);/////////////////////////////////////
				if (subset.size() != 0)
					library.print_to_screen(subset, print_record);
				else
					cout << "�������� �� �������" << endl;
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		numb = menu_librarian_pos();
	}
}

void SaveFiles()
{
	books.OutputFile(Book::WriteBookToFile, out_file_name_books);
	readers.OutputFile(Reader::WriteReaderToFile, out_file_name_readers);
}

void ChangeInputData(){

	string file_name_books = "input_books.txt";
	string file_name_readers = "input_readers.txt";

	bool change;
	//change = books.load_from_file(from_string_record, file_name_books) && readers.load_from_file(from_string_reader, file_name_readers);
	change = books.ReadFromFile(Book::ReadBookFromFile, out_file_name_books) && readers.ReadFromFile(Reader::ReadReaderFromFile ,out_file_name_readers);

	if (change)
	{
		int n = Menu();
		while (n != 0)
		{
			switch (n)
			{
			case 1:
			{
				print_all_readers();
				int n = input_number(0, readers.records.size(), "������� ��� �����, ����� 0:\n");
				menu_reader(n);
				system("cls");
				SaveFiles();
				break;
			}
			case 2:
			{
				menu_librarian();
				system("cls");
				SaveFiles();
				break;
			}
			default:
				SaveFiles();
				exit(0);
				break;
			}
			//system("cls");
			n = Menu();
		}
	}
}

int main()
{
	
	setlocale(LC_ALL, "Russian");
	ChangeInputData();

	system("pause");
	return 0;
}
