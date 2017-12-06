#ifndef GOODS_H_
#define GOODS_H_

#include<iostream>
#include<string>
using namespace std;

class Goods
{
private:
	string name;
	string date;
	int price;
	int quantity; //���������� ������ ������
	int consNum; //����� ���������
public:
	Goods();

	void read(); // ���� ������ � ������
	void display(); // ������ ������ � ������ 
	void priceChange(const int&); //��������� ���� ������
	void quantityChange(const int&); //��������� ���������� ������
	int countCost(); //���������� ��������� ������
	string costToString(); //�������������� ��������� ������ � ������
};

#endif