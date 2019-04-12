//Сначала по году рождения, потом
//по стажу работы с помощью сортировки расческой
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct date { //Структура для даты рождения
	int dd, mm, yy;
};

struct people {
	string Surname; //Фамилия
	string Position; //Должность
	date DateOfBith; //Дата рождения
	int Experience; //Стаж
	int Salary; //Зарплата
};

date Str_to_Date(string str) { //Перевод строки в дату
	date x;
	string temp = str.substr(0, 2);
	x.dd = atoi(temp.c_str());
	temp = str.substr(3, 2);
	x.mm = atoi(temp.c_str());
	temp = str.substr(6, 4);
	x.yy = atoi(temp.c_str());
	return x;
}

vector<people> inFile() {//Считывание данных с файла
	vector<people> x;
	people temp;
	string tmp;
	while (in >> temp.Surname && in >> temp.Position && in >> tmp
		&& in >> temp.Experience && in >> temp.Salary)
	{
		temp.DateOfBith = Str_to_Date(tmp);
		x.push_back(temp);
	}
	return x;
}

bool operator < (people a, people b) {  //Переопределение операторов < и >
	if (a.DateOfBith.yy < b.DateOfBith.yy) return true;
	if (a.DateOfBith.yy == b.DateOfBith.yy && a.Experience < b.Experience) return true;
	return false;
}

bool operator > (people a, people b) {
	if (a.DateOfBith.yy > b.DateOfBith.yy) return true;
	if (a.DateOfBith.yy == b.DateOfBith.yy && a.Experience > b.Experience) return true;
	return false;
}

void combsort(vector<people> &x,int N) { // Сортировка расчёской
	int gap = N / 1.247; //Расстояние между эл-тами
	while (gap >= 1) { 
		if (gap < 1)
			gap = 1;
		for (int j = 0; j < N - gap; j++)
			if (x[j] > x[j + gap]) //сравнение
				swap(x[j], x[j + gap]); //замена эл-тов
		gap /= 1.247; //уменьшаем расстояние

	}
}

void print(people x) { //Запись данных файл
	out << setw(11) << left << x.Surname;
	out << setw(20) << left << x.Position;
	if (x.DateOfBith.dd < 10) out << left << '0' << x.DateOfBith.dd << '.';
	else out << left << x.DateOfBith.dd << '.';
	if (x.DateOfBith.mm < 10) out << '0' << x.DateOfBith.mm << '.';
	else out << x.DateOfBith.mm << '.';
	out << left << setw(6) << x.DateOfBith.yy;
	out << left << setw(3) << x.Experience;
	out << left << setw(6) << x.Salary << endl;
}

int main() {
	vector<people> x; //Создание вектора для данных
	x = inFile(); //считывание
	int N = x.size();
	combsort(x, N);
	for (int i = 0; i < x.size(); i++)
		print(x[i]); //запись
	return 0;
}