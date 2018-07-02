//#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <fstream>
#include <istream>
#include <iostream>
#include <string>
using namespace std;

// ���� ����������
string InputInfo(string info);

// �������� ������� �� ������������ � ����� �����
bool CorrectSymbol(char c);

// �������� ����� ����� �� �����������
bool CorrectName(string name);

// ���� ����� �����
string InputFileName();

// ������ ������ �� ��������� �����
string StringFromBinFile(ifstream& in);

// ������ ������ � �������� ����
void StringInBinFile(ofstream& os, string str);
