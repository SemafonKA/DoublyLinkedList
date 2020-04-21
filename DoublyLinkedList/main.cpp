#include <cstdlib>
#include <iostream>
#include <string>
#include "Dlist/Dlist.h"

using namespace std;


int main() {
	system("chcp 65001"); system("cls");

	Dlist<int> list;
	list.out.mode(Mode::LIST_NUM_ADR_FULL);
	list.push_front(25).push_front(125).push_front(15).push_front(835).push_front(9).push_front(-234);
	cout << "Начальный список:" << endl;
	list.out();	
	cout << list.pop(5) << endl;
	list.push_back(112).push_back(861).push_back(134).push_back(94);
	list.out();
	cout << list.pop_front() << endl;
	cout << "\nНажмите ввод чтобы закрыть" << endl;
	cin.get();
	return 0;
}