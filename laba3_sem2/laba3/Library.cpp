#include "Library.h"

template<class T>
void Library<T>::add(T& rec) {
	records.push_back(rec);
}

template<class T>
Record Library<T>::change(T& person) {
	unsigned short int choose;
	cout << "��� �� ������ ��������?" << endl
		<< "1 - ����� ������������� ������;" << endl
		<< "2 - ������� ��������;" << endl
		<< "3 - ���� ��������� �����;" << endl
		<< "4 - ���� �������� �����;" << endl
		<< "5 - ������ �����;" << endl
		<< "6 - �������� �����;" << endl
		<< "7 - ��� ������� �����;" << endl
		<< "8 - ����������� �����;" << endl
		<< "9 - ���� �����." << endl;
	cin >> choose;
	system("cls");
	switch (choose)
	{
	case 1:
	{
		unsigned int card_;
		card_ = input_number(1, 999999, "������� ����� ����� ������������� ������: ");
		person.set_card(card_);
		break;
	}
	case 2:
	{
		string surname_;
		cout << "������� ����� �������:" << endl;
		cin >> surname_;
		person.set_surname(surname_);
		break;
	}
	case 3:
	{
		cout << "������� ����� ���� ������: " << endl;
		Date date_;
		person.set_date_get(date_.get_date());
		break;
	}
	case 4:
	{
		cout << "������� ����� ���� ��������:" << endl;
		Date date_;
		person.set_date_return(date_.get_date());
		break;
	}
	case 5:
	{
		string author;
		cout << "������� ������ ������: " << endl;
		cin >> author;
		person.set_author(author);
		break;
	}
	case 6:
	{
		string title;
		cout << "������� ����� ��������: " << endl;
		cin >> title;
		person.set_title(title);
		break;
	}
	case 7:
	{
		unsigned int year;
		year = input_number(1400, 2018, "������� ��� ������� �����: ");
		person.set_year_book(year);
		break;
	}
	case 8:
	{
		string house;
		cout << "������� �������� ������������: " << endl;
		cin >> house;
		person.set_pub_house(house);
		break;
	}
	case 9:
	{
		unsigned int pr;
		pr = input_number(1, 10000, "������� ����� ���� ����� � ������: ");
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

// ���� �� ����� 
// Type(*f)(ifstream&) - ��������� �� �������, ������� ��������� ���� ��������� �� ����� 
template<class T>
bool Library<T>::load_from_file(T(*f)(ifstream&), string file_name)
{
	ifstream input(file_name);

	if (!input)
	{
		cout << "������!" << endl;
		return false;
	}
	else
	{
		while (!input.eof())
			records.push_back(f(input));
		//vect.erase(vect.begin() + vect.size() - 1);

		input.close();
		return true;
	}
}

// ���� � ������ 
//Type(*f)() - ��������� �� �������, ������� ������ ���� ��������� � ������� 
template<class T>
void Library<T>::read_from_console(T(*f)())
{
	int n;
	T elem;
	do
	{
		records.push_back(f());
		n = input_number(0, 1, "�� ������ �������� ����� �������? (1 - ��, 0 - ���)\n��� �����: ");
	} while (n != 0);
}

// �������� ����� 
// bool(*Equal)(Type, Type) - ��������� �� �������, ������� ��������� ��������� �������� ��-�� � ������� 
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

// �������� ����� 
// int(*Compare)(Type, Type) - ��������� �� �������, ������� ���������� ������� ��-� � ������� 
// bool(*Equal)(Type, Type) - ��������� �� �������, ������� ��������� ��������� �������� ��-�� � ������� 
template<class T>
vector<T> Library<T>::BinarySearch(T find_element, bool(*Compare)(T, T), bool(*Equal)(T, T)){
	vector<T> NewVect;

	sort(records.begin(), records.end(), Compare);
	auto index = lower_bound(records.begin(), records.end(), find_element, Compare);
	
		while ((index != records.end()) && Equal(*index, find_element)){
			NewVect.push_back(*index);
			++index;
		}
	return NewVect;
}

template<class T>
Library<T>::Library(){
	FileName = "binfile.bin";
	LoadFromFile();
}

template<class T>
Library<T>::~Library()
{
	SaveToFile();
}

// ����� � ���� 
// void(*f) (Type) - ��������� �� �������, ������� ���������� ���� ��������� � ���� 
template<class T>
void Library<T>::print_to_file(vector<T> items, string (*f)(T, int), string file_name)
{
	ofstream fout(file_name);
	if (fout)
	{
		vector<T>::const_iterator pos;
		for (pos = items.begin(); pos != items.end(); ++pos) {

			fout << f(*pos, count) << ' ';
		}
		cout << endl;
		fout.close();
	}
	else
		cout << "������!" << endl;
}

// ����� �� ����� 
// void(*f) (Type) - ��������� �� �������, ������� ��������� ���� ��������� �� ����� 
template<class T>
void Library<T>::print_to_screen(vector<T> items, void(*f) (T))
{
	vector<T>::const_iterator pos;
	int count = 1;
	for (pos = items.begin(); pos != items.end(); ++pos) {
		cout << "������ �" << count << endl;
		f(*pos);
		count++;
	}
}

template <class T>
void Library<T>::LoadFromFile() {
	records.clear();
	ifstream fin(FileName, ios::binary);
	Book b;
	Reader r;
	if (fin) {
		size_t len;
		while (
			fin.read((char *)(&b.author), sizeof(_int32)) &&
			fin.read((char *)(&b.history_get_book), sizeof(_int32)) &&
			fin.read((char *)(&b.is_available), sizeof(Date)) &&
			fin.read((char *)(&p.Life), sizeof(_int32)) &&
			fin.read((char *)(&p.NumOfStock), sizeof(_int32)) &&
			fin.read((char *)(&p.OutPutDate), sizeof(Date)) &&
			fin.read((char *)(&len), sizeof(len))) {
			char * buf = new char[len];
			if (fin.read((char *)(buf), len) &&
				fin.read((char *)(&p.Price), sizeof(_int32)))
			{
				p.Name = buf;
				base.push_back(p);
			}
			delete[] buf;
		}
	}
	fin.close();
}

template <class T>
void Library<T>::SaveToFile() {
	ofstream fout(FileName, ios::binary);
	for (Product p : base) {
		size_t len = p.Name.length() + 1;
		fout.write((char *)(&p.Code), sizeof(_int32));
		fout.write((char *)(&p.Count), sizeof(_int32));
		fout.write((char *)(&p.InputDate), sizeof(Date));
		fout.write((char *)(&p.Life), sizeof(_int32));
		fout.write((char *)(&p.NumOfStock), sizeof(_int32));
		fout.write((char *)(&p.OutPutDate), sizeof(Date));
		fout.write((char *)(&len), sizeof(len));
		const char * buf = p.Name.c_str();
		fout.write((char *)(buf), len);
		fout.write((char *)(&p.Price), sizeof(_int32));
	}
	fout.close();
}


