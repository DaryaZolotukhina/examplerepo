#include"goods.h"


Goods::Goods() 
{
	name = "";
	date="";
	price = 0; 
	quantity = 0; 
	consNum = 0; 
};

bool IsValid(int& day, int& month, int& year)
{
	bool isLeap = false;
	bool isOk = true;

	if (year % 4 == 0 && year % 100 != 0 ||  year % 400 == 0) { //todoo 100/400
		isLeap = true;
	}

	if (day < 1 || day > 31) {
		isOk = false;
	}

	if (month < 1 || month > 12) {
		isOk = false;
	}

	if (month == 2 && day > 29 && isLeap == true) {
		isOk = false;
	}
	if (month == 2 && day > 28 && isLeap == false) {
		isOk = false;
	}

	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) {
			isOk = false;
		}
	}
	return isOk;

}

string InputDate()
{
	string date;
	int index = 0;
	int day, month, year;

	cin >> date;

	int k = 0; // номер выделенного числа из строки 0 - день, 1 - мес, 2 - год 

	while(date[index] != '\0' && date[index] != '.')
	{
		int dig = 0;
		while(date[index] >= '0' && date[index] <= '9')
		{
			dig = dig * 10 + (date[index]  - '0');
			index++;
		}

		if (k == 0) day = dig;
		else if (k == 1) month = dig;
			else if (k == 2) year = dig;
				else throw runtime_error("Incorrect date!"); //в строке больше , чем 3 числа
		k++;
		if (date[index] == '.') index++; //пропустили точку
	}
	
	if (!IsValid(day, month, year)) 
		throw runtime_error("Date is not valid!");
	else
		return date;
		//return (to_string(day)+"."+to_string(month)+"."+to_string(year));
}

//ввод товара
void Goods::read()
{
	cout << "Enter the name of a product " << endl;
	cin >> name;

	cout << "Enter the date of registration " << endl;
	date = InputDate();

	cout << "Enter the price " << endl;
	cin >> price;

	cout << "Enter the quantity " << endl;
	cin >> quantity;

	cout << "Enter the invoice number " << endl;
	cin >> consNum;
	cout << endl;
}

//печать товара
void Goods::display()
{
	cout << "Name: " << name << endl;
	cout << "Date: " << date << endl;
	cout << "Price: " << price << endl;
	cout << "Number of items: " << quantity << endl;
	cout << "Invoice number: " << consNum << endl;

	cout << endl;
}

//»зменение цены товара
void Goods::priceChange(const int& pr)
{
	price = pr;
}

//»зменение количества единиц товара
void Goods::quantityChange(const int& qu)
{
	quantity = qu;
}

//¬ычисление стоимости товара
int Goods::countCost()
{
	return this->price*this->quantity;
}

//ѕреобразование стоимости товара в строку
string Goods::costToString()
{
	return to_string(countCost());
}