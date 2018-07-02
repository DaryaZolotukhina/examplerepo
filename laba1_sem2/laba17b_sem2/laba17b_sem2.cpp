// laba17b_sem2.cpp : Defines the entry point for the console application.
//

/*�������� ���������, ���������� ��������� �������:

1. ������� ���������� ���������� ����� N ������ ���������� ������� �
��������� �� -M �� M. ��� �����, N � M ��������� �� ���� �������, ����
������������ �������� ��� ��������� (������������ ������ �����-������).
����������� ��� �������� ��������� ����� � � ����� � � ��������������
��������� std::generate.
2. �������, ���������� ���� �� ����, � ������������ ����������������
���������, ����������� ������� �� �����.
3. ������� modify, ����������� �������������� ����������� ����������. �� ����
������� ������ ��������� ���������, � �������� ���������� ������� ������
���������� ���������������� ���������.
4. ������������� ������� modify, ����������� �� ���� ��������� ������ � �����
�������������� ����� ����������.
5. �������, ����������� ��������� �������������� � �������������� ���������
std::transform ������ ������� modify.
6. �������, ����������� ��������� �������������� � �������������� ���������
std::for_each ������ ������� modify.
7. �������, ����������� ����� � ������� �������������� �����, ������������ �
����������.
8. ������� ������ ���������� � ���� � �� ����� (�����������).

��������������: �������� ��� ������������� ����� ������������ �� �����.
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

//���������� ���������� ����� N ������ ���������� ������� � ��������� �� -M �� M
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

//���������� ����� ���������� ������� ����� generate
ofstream createFileGenerate(string filename, int N, int M)
{
    ofstream file(filename);
	generate_n(ostream_iterator<int>(file, " "), N, [M]() { return random(M); });
	file.close();
	return file;
}

//���������� ���������� �� �����
deque<int> loadFromFile(string fileName) {
	deque<int> dec;

	ifstream file(fileName);
	if (file.fail())
	{
		throw "�� ������� ������� ����";
	}

	copy(istream_iterator<int>(file), istream_iterator<int>(), back_inserter(dec));
	return dec;
}

//�������������� ���� (�������� ������������� �������� ������������ �� �����) � �����������
void modify(deque<int>::iterator begin, deque<int>::iterator end) {
	int max = 0;
	for (deque<int>::iterator i = begin; i != end; i++) {
		if (*i > max) max = *i;
	}

	for (deque<int>::iterator i = begin; i != end; i++) {
		if (*i > 0) *i=max;
	}
}

//�������������� ���� (�������� ������������� �������� ������������ �� �����) � ������ for
void modify(deque<int> &dec) {
	modify(dec.begin(), dec.end());
}

//�������������� ���� (�������� ������������� �������� ������������ �� �����) � transform
void modifyTransform(deque<int>::iterator &begin, deque<int>::iterator end) {
	int max = 0;
	transform(begin, end, begin, [&max](int i) { if (i > max) max = i;	return i; });
	transform(begin, end, begin, [max](int i) {return i > 0 ? max : i; });
}

//�������������� ���� (�������� ������������� �������� ������������ �� �����) � for_each
void modifyForEach(deque<int>::iterator begin, deque<int>::iterator end) {
	int max;
	for_each(begin, end, [&max](int i) { if (i > max) max = i; });
	for_each(begin, end, [max](int &i) { i = i > 0 ? max : i; });
}

//������� ����� ���������
int summ(deque<int> dec) {
	int sum = 0;
	for_each(dec.begin(), dec.end(), [&sum](int i) {sum += i; });
	return sum;
}

//������� �������� ���������������
double average(deque<int> dec) {
	return (double)summ(dec) / dec.size();
}

//������ � ����
void  print(fstream &st,deque<int> &dec) {
	for_each(dec.begin(), dec.end(), [&st](int i) {st << i << " "; });
}

//������ � �������
void  print(ostream &st, deque<int> dec) {
	for_each(dec.begin(), dec.end(), [&st](int i) {st << i << " "; });
	st << endl;
}

//����
int menu(int flag) {
	cout << ">>> ����:" << endl;
	cout << 1 << " ������� ����� ���� �� ���������� �������" << endl;
	cout << 2 << " ��������� ������������������ �� �����" << endl;
	if (flag > 0) { //���� ��������� �� ����
		cout << 3 << " �������� ��� ������������� ����� ������������������ ����������" << endl;
		cout << 4 << " ��������� ����� ������ ������������������" << endl;
		cout << 5 << " ��������� ������� ��������������" << endl;
		cout << 6 << " �������� ������������������ � ����" << endl;
		cout << 7 << " ���������� ������������������" << endl;
	}
	cout << 0 << " �����" << endl<<endl;
	int res;
	while (!(cin >> res) || flag <= 0 && (res > 2) || (flag > 0) && (res > 7));	
	return res;
}

//���� ������ ��/���
bool inputQuery(string quest) {
	cout << quest << endl;
	cout << 1 << " ��" << endl;
	cout << 0 << " ���" << endl;
	int res;
	while (!(cin >> res) || res != 0 && res != 1);
	return res == 1;
}

//���� ����� �����
string inputFileName() {
	string name;
	cout << "������� ��� �����" << endl;
	cin >> name;
	cout << endl;
	return name;
}

//���� �����
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
			N = inputNum("������� ���������� ���������:");
			M = inputNum("������� M, ����� �� ��������� �� -� �� � ����� ��������:");
			FileName = inputFileName();
			//ofs = createRandomFile(FileName,N,M);
			ofs = createFileGenerate(FileName, N, M);
			break;
		case 2:
			if (FileName == "") FileName = inputFileName();
			else if (!inputQuery("������������ ������� ����?")) {
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
			cout << "����� ��������� ����� " << summ(dec) << endl;
			break;
		case 5:
			cout << "������� �������������� ��������� ����� " << average(dec) << endl;
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
