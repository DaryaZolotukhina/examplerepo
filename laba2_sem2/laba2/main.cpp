#include<iostream>
#include"Library.cpp"
//���������� ������� ��� ����� � 3 ������

using namespace std;

int Menu()
{
	cout << " �------------------����-------------------� " << endl;
	cout << "1 - �������� �������" << endl;
	cout << "2 - ������� �������" << endl;
	cout << "3 - �������� �������" << endl;
	cout << "4 - ����� �� �����" << endl;
	cout << "5 - ��������� � ���� " << endl;
	cout << "6 - �������� �����" << endl;
	cout << "7 - �������� �����" << endl;
	cout << "8 - ������� ����������� �� �����" << endl;
	cout << "9 - ��������� ������������ � ����" << endl;
	cout << "0 - �����" << endl;
	int n = input_number(0, 9, "��� ����� (0-9). ");
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
	cout << " �------------------����-------------------� " << endl;
	cout << "1 - ���������� ���������� � �������" << endl;
	cout << "2 - ���������� ���������� �� ����� " << endl;
	cout << "0 - �����" << endl;
	int changemenu = input_number(0, 2, "��� ����� (0-2). ");
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
				library.remove(input_number(1, library.get_vector().size(), "������� ����� ��������, �������� �� ������ �������. "));
				system("cls");
				break;

			case 3:
			{
				library.print_to_screen(library.get_vector(), print_record);
				numb = input_number(1, library.get_vector().size(), "������� ����� ��������, ��������� �������� ������ ��������.");
				if (numb) {
					((library.get_vector())[numb - 1]) = library.change(library.get_vector()[numb - 1]);
				}
				system("cls");
				break;
			}
			case 4:
				system("cls");
				if (library.get_vector().size() == 0)
					cout << "������� ���!\n";
				else
					library.print_to_screen(library.get_vector(), print_record);
				break;

			case 5:
				//library.print_to_file(library.get_vector(), to_string_record, "output_all_file.txt");
				library.print_to_file(library.get_vector(), to_string_record, "input.txt");
				cout << "���� ��������!\n" << endl;
				break;

			case 6:
				numb = input_number(1, 4, "�������� ��� ������:\n 1 - �� ������ ������������� ������\n 2 - �� ������\n 3 - �� ������������\n 4 - �� ���� �������� (������������) \n��� �����: ");
				search_elem = search_type(numb);
				setFunction(numb, compare);

				subset = library.LinearySearch(search_elem, compare);
				system("cls");
				if (subset.size() != 0)
					library.print_to_screen(subset, print_record);
				else
					cout << "�������� �� �������\n" << endl;
				break;

			case 7:
				numb = input_number(1, 4, "�������� ��� ������:\n 1 - �� ������ ������������� ������\n 2 - �� ������\n 3 - �� ������������\n 4 - �� ���� �������� (������������) \n��� �����: ");
				search_elem = search_type(numb);
				setFunction(numb, compare, sort);

				subset = library.BinarySearch(search_elem, sort, compare);
				system("cls");
				if (subset.size() != 0)
					library.print_to_screen(subset, print_record);
				else
					cout << "�������� �� �������" << endl;
				break;


			case 8:
				system("cls");
				if (subset.size() == 0)
					cout << "������������ �����!\n";
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
