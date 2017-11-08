// try.cpp : Defines the entry point for the console application.
//
/*
Даны N городов и известны расстояния между ними. Не все города связаны друг с другом дорогой. 
Определить самый длинный и самый короткий маршрут изз города A в B(ни в один город нельзя заходить дважды).
Здоровцова Е. 
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
	int pathVertex;		//количество вершин в маршруте
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
	cout << "длина равна " << path.pathLen << endl;
}

void step (int Matr[MaxN][MaxN], int size, int cur, int p, int cLen) {

	int next;
	if (cur == finish-1) {	//finish - 1 тк нумерация с нуля
		
		if (cLen < minW.pathLen || !found ) 
		{
			minW.pathLen = cLen;
			minW.pathVertex = p;		//запомнить длину пути (количество узлов)
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
		found = true; //поставить флажок "найдено"
	}
	else {										//выбор очередной точки
		for (next = 0; next < size; next++) {									
			int w = Matr[cur][next];
			if (w > 0 && !visited[next]) {	
				road[p] = next;					
				visited[next] = true;									
				step (Matr, size, next, p+1, cLen+w);	//вызвать себя для поиска следующей точки
				road[p] = 0;							//вернуть всё как было
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
						 };						//для этого графа мин путь из 1 вершины в 5 - 20, макс - 47
						 
	int n=6; //количество городов

	/*
	cout << "Как вы хотите ввести информацию о графе? \n1 - случайным образом,\n2 - с клавиатуры. \n0 - выход.\n" << endl;
	int ans;
	cin >> ans;
	while (ans < 0 || ans > 2) //проверка на правильность выбора пункта меню
	{
		cout << "Ошибка. Введите корректный пункт меню. Задать граф\n1 - случайным образом,\n2 - с клавиатуры. \n0 - выход.\n" << endl;
		cin >> ans;
	} 

	if (ans != 0)
	{
		cout << "Введите количество вершин" << endl;
		cin >> n;
		for (int i = 0; i < n; i++)
			map[i][i] = 0;				//нет петель

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
			cout << "Введите длину дороги между городами, если дороги нет, введите 0:" << endl;
			for (int i = 0; i < n - 1; i++) 
			{
				for (int j = i + 1; j < n; j++) 
				{
					int a;
					cout << i + 1 << " и " << j + 1 << ": " << endl;
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
	//вывод графа
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
	cout << "Введите номера городов, между которыми найти расстояние: " << endl;
	cin >> start >> finish;
	cout << endl;

	road[0] = start-1;			//первую точку внесли в маршрут
	visited[start-1] = true;	//и пометили как включённую
	found = false;				//но путь пока не найден
	step (map, n, start-1, 1, 0); //ищем вторую точку
	if (found) {
		if (minW.pathLen == maxW.pathLen) 
		{
			cout << "Длины максимального и минимально путей из " << start << " в " << finish << " совпадают:"<< endl;
			PrintWay(minW);		
		}
		else 
		{
			cout << "Минимальный путь из "<< start << " в " << finish << ":"<< endl;
			PrintWay(minW);		
			cout << endl;
			cout << "Максимальный путь из "<< start << " в " << finish << ":"<< endl;
			PrintWay(maxW);		
		}
	}
	else cout << "Путь не найден!";

	cin.get(); cin.get();
	return 0;
}