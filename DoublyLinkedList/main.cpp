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

int main() {
	system("chcp 65001"); system("cls");
	random_device rd;

	Dlist<pair<int, int>> list;
	list.resize(4);
	list.at(0).first = 1;
	list.at(1).first = 4;
	list.at(2).first = 2;
	list.at(3).first = 3;

	for (int i = 0; i < list.size(); ++i) {
		list.at(i).second = rd() % 4;
	}
	
	list_out(list);

	sort(list);
	list_out(list);

	cout << "\nНажмите ввод чтобы закрыть" << endl;
	cin.get();
	return 0;
}