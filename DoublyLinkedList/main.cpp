#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include "Dlist/Dlist.h"

using namespace std;

void list_out(Dlist<std::pair<int, int>>& list)
{
	for (int i = 0; i < list.size(); ++i) {
		cout << list.at(i).first << "    " << list.at(i).second << endl;
	}
	cout << endl;
}

Dlist<int> listCreater(int a, int b, int c) {
	Dlist<int> tmpObj;
	tmpObj.push_back(a).push_back(b).push_back(c);
	cout << "Temp object:";
	tmpObj.out();
	cout << endl;
	Dlist<int> obj;
	obj = tmpObj;
	return obj;
}

int main() {
	system("chcp 65001"); system("cls");
	random_device rd;

	Dlist<int> mas(listCreater(2, 4, 8));
	mas.out();

	cout << "\nНажмите ввод чтобы закрыть" << endl;
	cin.get();
	return 0;
}