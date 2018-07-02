#define _CRT_SECURE_NO_WARNINGS
#include "HelpUtils.h"


string InputInfo(string info)
{
	string a;
	cout << info;
	cin >> a;
	return a;
}

bool CorrectSymbol(char c)
{
	switch (c)
	{

	case '*':
	case '?':
	case '<':
	case '>':
	case ':':
	case '|':
	case '/':
		return false;
	default:
		return true;
	}
}

bool CorrectName(string name)
{
	int i = 0, l = name.length();
	bool goodsm = true;
	for (int i = 0; (i < l && goodsm); i++)
		goodsm = CorrectSymbol(name[i]);
	return goodsm;
}

string InputFileName()
{

	string filename;
	do
	{
		cout << "Введите имя файла:  ";
		cin >> filename;

		if (CorrectName(filename))
		{

			break;
		}
		else
			cout << "Имя файла задано некорректно\n";
	} while (true);

	return filename;
}

string StringFromBinFile(ifstream & in)
{
	string result;
	__int64 len_name;
		in.read((char*)&len_name, sizeof(len_name)); 
	char * buf = new char[(unsigned int)len_name];         
	in.read(buf, len_name); 
	result = buf;                      
	delete[]buf;               

	return result;
}

void StringInBinFile(ofstream & os, string str)
{

	__int64 len_name = str.length() + 1;  
	os.write((char*)&len_name, sizeof(__int64)); 
	os.write(str.c_str(), len_name);  
}
