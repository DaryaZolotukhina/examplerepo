// try.cpp : Defines the entry point for the console application.
//
/*
���� N ������� � �������� ���������� ����� ����. �� ��� ������ ������� ���� � ������ �������. 
���������� ����� ������� � ����� �������� ������� ��� ������ A � B(�� � ���� ����� ������ �������� ������).
���������� �. 
*/
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <iomanip>

using namespace std;

const int MaxN = 50;

int road[MaxN]; 
bool visited[MaxN]; 
bool found;
int finish;

struct Way {
	int pathWay[MaxN];
	int pathVertex;		//���������� ������ � ��������
	int pathLen;
};

struct Way minW, maxW;

void Init (Way &path)
{
	for (int i=0; i<MaxN; i++)
	{
		path.pathWay[i] = 0;
	}
	path.pathVertex = 0;
	path.pathLen = 0;	
}

void PrintWay (Way &path)
{
	int pathLen = path.pathVertex;

	for (int i=0; i<pathLen; i++) 
		cout << path.pathWay[i] + 1 << " ";
	cout << "����� ����� " << path.pathLen << endl;
}

void step (int Matr[MaxN][MaxN], int size, int cur, int p, int cLen) {

	int next;
	if (cur == finish-1) {	//finish - 1 �� ��������� � ����
		
		if (cLen < minW.pathLen || !found ) 
		{
			minW.pathLen = cLen;
			minW.pathVertex = p;		//��������� ����� ���� (���������� �����)
			for (int i=0; i < p; i++)	 
				minW.pathWay[i] = road[i];
		}
		if (cLen > maxW.pathLen) 
		{
			maxW.pathLen = cLen;
			maxW.pathVertex = p;							
			for (int i = 0; i < p; i++) 
				maxW.pathWay[i] = road[i];
		}
		found = true; //��������� ������ "�������"
	}
	else {										//����� ��������� �����
		for (next = 0; next < size; next++) {									
			int w = Matr[cur][next];
			if (w > 0 && !visited[next]) {	
				road[p] = next;					
				visited[next] = true;									
				step (Matr, size, next, p+1, cLen+w);	//������� ���� ��� ������ ��������� �����
				road[p] = 0;							//������� �� ��� ����
				visited[next] = false;
			}
		}
	}
}

int main () {
	setlocale(LC_ALL, "Rus");
	srand (time(0));

	int map[MaxN][MaxN] = {
						 {0, 7, 9, 0, 0, 14},
						 {7, 0, 10, 15, 0, 0},
						 {9, 10, 0, 11, 0, 2},
						 {0, 15, 11, 0, 6, 0},
						 {0, 0, 0, 6, 0, 9},
						 {14, 0, 2, 0, 9, 0}
						 };						//��� ����� ����� ��� ���� �� 1 ������� � 5 - 20, ���� - 47
						 
	int n=6; //���������� �������

	/*
	cout << "��� �� ������ ������ ���������� � �����? \n1 - ��������� �������,\n2 - � ����������. \n0 - �����.\n" << endl;
	int ans;
	cin >> ans;
	while (ans < 0 || ans > 2) //�������� �� ������������ ������ ������ ����
	{
		cout << "������. ������� ���������� ����� ����. ������ ����\n1 - ��������� �������,\n2 - � ����������. \n0 - �����.\n" << endl;
		cin >> ans;
	} 

	if (ans != 0)
	{
		cout << "������� ���������� ������" << endl;
		cin >> n;
		for (int i = 0; i < n; i++)
			map[i][i] = 0;				//��� ������

		if (ans == 1)
		{
			int a;
			for (int i = 0; i < n - 1; i++) 
				for (int j = i + 1; j < n; j++) 
				{
					a = rand() % 10;
					map[i][j] = a; 
					map[j][i] = a;
				}
		}
		else if (ans == 2) 
		{
			cout << "������� ����� ������ ����� ��������, ���� ������ ���, ������� 0:" << endl;
			for (int i = 0; i < n - 1; i++) 
			{
				for (int j = i + 1; j < n; j++) 
				{
					int a;
					cout << i + 1 << " � " << j + 1 << ": " << endl;
					do {
						cin >> a; 
					} while (a < 0);
					map[i][j] = a;
					map[j][i] = a;
				}
			}
		}
	}
	else exit(0);
	*/
	//����� �����
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(4) << map[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++) {
		road[i] = 0; visited[i] = false;
	}

	Init(minW);
	Init(maxW);

	int start;
	cout << "������� ������ �������, ����� �������� ����� ����������: " << endl;
	cin >> start >> finish;
	cout << endl;

	road[0] = start-1;			//������ ����� ������ � �������
	visited[start-1] = true;	//� �������� ��� ����������
	found = false;				//�� ���� ���� �� ������
	step (map, n, start-1, 1, 0); //���� ������ �����
	if (found) {
		if (minW.pathLen == maxW.pathLen) 
		{
			cout << "����� ������������� � ���������� ����� �� " << start << " � " << finish << " ���������:"<< endl;
			PrintWay(minW);		
		}
		else 
		{
			cout << "����������� ���� �� "<< start << " � " << finish << ":"<< endl;
			PrintWay(minW);		
			cout << endl;
			cout << "������������ ���� �� "<< start << " � " << finish << ":"<< endl;
			PrintWay(maxW);		
		}
	}
	else cout << "���� �� ������!";

	cin.get(); cin.get();
	return 0;
}