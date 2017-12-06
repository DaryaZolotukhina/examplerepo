/*
Здоровцова Елена
17. Создать класс Goods (товар). В классе должны быть представлены поля:
наименование товара, дата оформления, цена товара, количество единиц товара, номер накладной, по которой товар поступил на склад. 
Реализовать методы изменения цены товара, изменения количества товара, вычисления стоимости товара. 
Метод toString() должен выдавать в виде строки стоимость товара.

Во всех упражнениях, помимо указанных методов, обязательно должны быть
реализованы метод инициализации Init(), метод ввода данных с клавиатуры Read(),
метод вывода данных на экран Display().
*/

#include<iostream>
#include<locale>
#include<string>
#include"goods.h"

int enterNum()
{
	cout << "Enter a new number to change previuos value " << endl;
	int x;
	cin >> x;
	while (x < 0)
	{
		cout << "Enter correct number ";
		cin >> x;
		cout << endl;
	}
	return x;
}

int main()
{
	Goods gd;
	int number;

	do
	{
		cout << "Menu" << endl;
		cout << "1 - Enter product's data" << endl;
		cout << "2 - Print product's data" << endl;
		cout << "3 - Change the price" << endl;
		cout << "4 - Change the quantity" << endl;
		cout << "5 - Calculate the cost of product " << endl;
		cout << "6 - Convert int cost to string " << endl;
		cout << "7 - Exit" << endl << endl;
		cout << "Select a required action" << endl << endl;
		cin >> number;
		
		switch (number)
		{
		case 1: gd.read(); break;
		case 2: gd.display(); break;
		case 3:	{ gd.priceChange(enterNum()); cout << endl; } break;
		case 4: { gd.quantityChange(enterNum()); cout << endl; } break;
		case 5: cout << "Cost of the product: " << gd.countCost() << endl << endl;	break;
		case 6: cout << gd.costToString() << endl; break;
		default: cout << "Invalid entry" << endl << endl; break;
		}
		getchar();

	} while(number != 7);

	return 0;
}