// laba17b_sem2.cpp : Defines the entry point for the console application.
//

/*Написать программу, содержащую следующие функции:

1. Функцию заполнения текстового файла N целыми случайными числами в
диапазоне от -M до M. Имя файла, N и M поступают на вход функции, файл
возвращается функцией как результат (использовать потоки ввода-вывода).
Реализовать два варианта генерации чисел — в цикле и с использованием
алгоритма std::generate.
2. Функцию, получающую файл на вход, и возвращающую последовательный
контейнер, заполненный числами из файла.
3. Функцию modify, выполняющую преобразование полученного контейнера. На вход
функции должен поступать контейнер, в качестве результата функция должна
возвращать модифицированный контейнер.
4. Перегруженную функцию modify, принимающую на вход итераторы начала и конца
обрабатываемой части контейнера.
5. Функцию, реализующую требуемое преобразование с использованием алгоритма
std::transform вместо функции modify.
6. Функцию, реализующую требуемое преобразование с использованием алгоритма
std::for_each вместо функции modify.
7. Функции, вычисляющие сумму и среднее арифметическое чисел, содержащихся в
контейнере.
8. Функцию вывода результата в файл и на экран (опционально).

Преобразование: Заменить все положительные числа максимальным из чисел.
*/

#include "stdafx.h"
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <iterator>
using namespace std;

int random (int M)
{
	return rand() % (2 * M + 1) - M;
}

//заполнения текстового файла N целыми случайными числами в диапазоне от -M до M
ofstream createRandomFile(string filename, int N, int M)
{
    ofstream file(filename);
	for(int i = 0; i < N ; ++i) 
	{
		int r = random(M);
		file << r << " ";
	}
	file.close();
	return file;   
}

//заполнение файла случайными числами через generate
ofstream createFileGenerate(string filename, int N, int M)
{
    ofstream file(filename);
	generate_n(ostream_iterator<int>(file, " "), N, [M]() { return random(M); });
	file.close();
	return file;
}

//заполнение контейнера из файла
deque<int> loadFromFile(string fileName) {
	deque<int> dec;

	ifstream file(fileName);
	if (file.fail())
	{
		throw "Не удалось открыть файл";
	}

	copy(istream_iterator<int>(file), istream_iterator<int>(), back_inserter(dec));
	return dec;
}

//преобразование дека (заменяем положительные элементы максимальным из чисел) с итераторами
void modify(deque<int>::iterator begin, deque<int>::iterator end) {
	int max = 0;
	for (deque<int>::iterator i = begin; i != end; i++) {
		if (*i > max) max = *i;
	}

	for (deque<int>::iterator i = begin; i != end; i++) {
		if (*i > 0) *i=max;
	}
}

//преобразование дека (заменяем положительные элементы максимальным из чисел) с циклом for
void modify(deque<int> &dec) {
	modify(dec.begin(), dec.end());
}

//преобразование дека (заменяем положительные элементы максимальным из чисел) с transform
void modifyTransform(deque<int>::iterator &begin, deque<int>::iterator end) {
	int max = 0;
	transform(begin, end, begin, [&max](int i) { if (i > max) max = i;	return i; });
	transform(begin, end, begin, [max](int i) {return i > 0 ? max : i; });
}

//преобразование дека (заменяем положительные элементы максимальным из чисел) с for_each
void modifyForEach(deque<int>::iterator begin, deque<int>::iterator end) {
	int max;
	for_each(begin, end, [&max](int i) { if (i > max) max = i; });
	for_each(begin, end, [max](int &i) { i = i > 0 ? max : i; });
}

//подсчет суммы элементов
int summ(deque<int> dec) {
	int sum = 0;
	for_each(dec.begin(), dec.end(), [&sum](int i) {sum += i; });
	return sum;
}

//подсчет среднего арифметического
double average(deque<int> dec) {
	return (double)summ(dec) / dec.size();
}

//печать в файл
void  print(fstream &st,deque<int> &dec) {
	for_each(dec.begin(), dec.end(), [&st](int i) {st << i << " "; });
}

//печать в консоль
void  print(ostream &st, deque<int> dec) {
	for_each(dec.begin(), dec.end(), [&st](int i) {st << i << " "; });
	st << endl;
}

//меню
int menu(int flag) {
	cout << ">>> Меню:" << endl;
	cout << 1 << " Создать новый файл со случайными числами" << endl;
	cout << 2 << " Загрузить последовательность из файла" << endl;
	if (flag > 0) { //если контейнер не пуст
		cout << 3 << " Заменить все положительные члены последовательности максимумом" << endl;
		cout << 4 << " Вычислить сумму членов последовательности" << endl;
		cout << 5 << " Вычислить среднее арифметическое" << endl;
		cout << 6 << " Записать последовательность в файл" << endl;
		cout << 7 << " Напечатать последовательность" << endl;
	}
	cout << 0 << " Выход" << endl<<endl;
	int res;
	while (!(cin >> res) || flag <= 0 && (res > 2) || (flag > 0) && (res > 7));	
	return res;
}

//ввод ответа да/нет
bool inputQuery(string quest) {
	cout << quest << endl;
	cout << 1 << " Да" << endl;
	cout << 0 << " Нет" << endl;
	int res;
	while (!(cin >> res) || res != 0 && res != 1);
	return res == 1;
}

//ввод имени файла
string inputFileName() {
	string name;
	cout << "Введите имя файла" << endl;
	cin >> name;
	cout << endl;
	return name;
}

//ввод числа
int inputNum(string str) {
	int Num;
	cout << str << endl;
	while (!(cin >> Num) || Num <= 0);
	return Num;
}

int main() {
	setlocale(LC_ALL, "Russian");

	bool exit = false;
	deque<int> dec;
	string FileName="";
	int N;
	int M;
	ofstream ofs;
	ifstream ifs;
	
	do {
		switch (menu(dec.size())) {
		case 1: 
			N = inputNum("Введите количество элементов:");
			M = inputNum("Введите M, числа из диапазона от -М до М будут записаны:");
			FileName = inputFileName();
			//ofs = createRandomFile(FileName,N,M);
			ofs = createFileGenerate(FileName, N, M);
			break;
		case 2:
			if (FileName == "") FileName = inputFileName();
			else if (!inputQuery("Использовать текущий файл?")) {
				FileName = inputFileName();
			}
			ifs.open(FileName);
			dec = loadFromFile(FileName);
			ifs.close();
			break;
		case 3:
			//modify(dec);
			modify(dec.begin(), dec.end());
			//modifyTransform(dec.begin(), dec.end());
			//modifyForEach(dec.begin(), dec.end());
			break;
		case 4:
			cout << "Сумма элементов равна " << summ(dec) << endl;
			break;
		case 5:
			cout << "Среднее арифметическое элементов равно " << average(dec) << endl;
			break;
		case 6:
			FileName = inputFileName();
			ofs.open(FileName);
			print(ofs, dec);
			ofs.close();
			break;
		case 7:
			print(cout, dec);
			break;
		default:
			return 0;
		}
	} while (1);
}
