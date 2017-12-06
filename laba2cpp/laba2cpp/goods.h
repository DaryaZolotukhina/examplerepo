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
	int quantity; //количество единиц товара
	int consNum; //номер накладной
public:
	Goods();

	void read(); // ввод данных о товаре
	void display(); // печать данных о товаре 
	void priceChange(const int&); //изменение цены товара
	void quantityChange(const int&); //изменение количества товара
	int countCost(); //вычисление стоимости товара
	string costToString(); //преобразование стоимости товара в строку
};

#endif