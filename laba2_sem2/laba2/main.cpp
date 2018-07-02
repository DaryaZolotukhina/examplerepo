#include<iostream>
#include"Library.cpp"
//возмоность вводить имя файла в 3 задаче

using namespace std;

int Menu()
{
	cout << " —------------------Меню-------------------— " << endl;
	cout << "1 - Добавить элемент" << endl;
	cout << "2 - Удалить элемент" << endl;
	cout << "3 - Изменить элемент" << endl;
	cout << "4 - Вывод на экран" << endl;
	cout << "5 - Сохранить в файл " << endl;
	cout << "6 - Линейный поиск" << endl;
	cout << "7 - Двоичный поиск" << endl;
	cout << "8 - Вывести подможество на экран" << endl;
	cout << "9 - Сохранить подмножество в файл" << endl;
	cout << "0 - Выход" << endl;
	int n = input_number(0, 9, "Ваш выбор (0-9). ");
	cout << "\n";
	return n;
}

void setFunction(int numb, bool(*&compare)(Record, Record))
{
	switch (numb)
	{
	case 1:
		compare = search_element_card;
		break;
	case 2:
		compare = search_element_author;
		break;
	case 3:
		compare = search_element_pub_house;
		break;
	case 4:
		compare = search_element_date_return;
		break;
	}
}

void setFunction(int numb, bool(*&compare)(Record, Record), bool(*&sort)(Record, Record))
{
	switch (numb)
	{
	case 1:
		compare = search_element_card;
		sort = sorte_card;
		break;
	case 2:
		compare = search_element_author;
		sort = sorte_author;
		break;
	case 3:
		compare = search_element_pub_house;
		sort = sorte_pub_house;
		break;
	case 4:
		compare = search_element_date_return;
		sort = sorte_date_return;
		break;
	}
}

void ChangeInputData()
{
	Library<Record> library;
	bool change = true;
	cout << " —------------------Меню-------------------— " << endl;
	cout << "1 - Заполнение контейнера с консоли" << endl;
	cout << "2 - Заполнение контейнера из файла " << endl;
	cout << "0 - Выход" << endl;
	int changemenu = input_number(0, 2, "Ваш выбор (0-2). ");
	switch (changemenu)
	{
	case 1:
		library.read_from_console(add_record);
		break;

	case 2:
		change = library.load_from_file(from_string_record, "input.txt");
		break;

	default:
		change = false;
		break;
	}
	if (change)
	{
		bool(*compare)(Record, Record) = NULL;
		bool(*sort)(Record, Record) = NULL;
		Record elem;
		vector<Record> subset;
		Record search_elem;
		int numb;
		while (1)
		{
			int n = Menu();
			switch (n)
			{
			case 1:
				library.add(add_record());
				system("cls");
				break;

			case 2:
				library.print_to_screen(library.get_vector(), print_record);
				library.remove(input_number(1, library.get_vector().size(), "Введите номер читателя, которого вы хотите удалить. "));
				system("cls");
				break;

			case 3:
			{
				library.print_to_screen(library.get_vector(), print_record);
				numb = input_number(1, library.get_vector().size(), "Введите номер читателя, инфомацию которого хотите изменить.");
				if (numb) {
					((library.get_vector())[numb - 1]) = library.change(library.get_vector()[numb - 1]);
				}
				system("cls");
				break;
			}
			case 4:
				system("cls");
				if (library.get_vector().size() == 0)
					cout << "Записей нет!\n";
				else
					library.print_to_screen(library.get_vector(), print_record);
				break;

			case 5:
				//library.print_to_file(library.get_vector(), to_string_record, "output_all_file.txt");
				library.print_to_file(library.get_vector(), to_string_record, "input.txt");
				cout << "Файл сохранен!\n" << endl;
				break;

			case 6:
				numb = input_number(1, 4, "Выберите тип поиска:\n 1 - по номеру читательского билета\n 2 - по автору\n 3 - по издательству\n 4 - по дате возврата (просроченные) \nВаш выбор: ");
				search_elem = search_type(numb);
				setFunction(numb, compare);

				subset = library.LinearySearch(search_elem, compare);
				system("cls");
				if (subset.size() != 0)
					library.print_to_screen(subset, print_record);
				else
					cout << "Элементы не найдены\n" << endl;
				break;

			case 7:
				numb = input_number(1, 4, "Выберите тип поиска:\n 1 - по номеру читательского билета\n 2 - по автору\n 3 - по издательству\n 4 - по дате возврата (просроченные) \nВаш выбор: ");
				search_elem = search_type(numb);
				setFunction(numb, compare, sort);

				subset = library.BinarySearch(search_elem, sort, compare);
				system("cls");
				if (subset.size() != 0)
					library.print_to_screen(subset, print_record);
				else
					cout << "Элементы не найдены" << endl;
				break;


			case 8:
				system("cls");
				if (subset.size() == 0)
					cout << "Подмножество пусто!\n";
				else
					library.print_to_screen(subset, print_record);
				break;

			case 9:
				library.print_to_file(subset, to_string_record, "output_subset.txt");
				system("cls");
				break;


			default:
				system("cls");
				exit(0);
				break;
			}
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
