#include <cstdlib>
#include <iostream>
using namespace std;

template<typename T>
inline void swap(T& first, T& second) {
	T tmp = first;
	first = second;
	second = tmp;
}

template<typename T>
class Dlist {
private:
	class Node {
	public:
		T data{};
		Node* next{};
		Node* prev{};
	};

	Node* m_front{};
	Node* m_back{};

	int m_listSize{};

	void listCheck() const {
		Node* member = m_front;
		for (int i = 0; i < m_listSize; ++i) {
			if (member == nullptr) {
				cerr << "ERR: error in resize list";
				throw logic_error("ERR: error in resize list");
			}
			member = member->next;
		}
	}

	Node* listSearch(int pos) const {
		if (pos >= m_listSize) {
			cerr << "ERR: out of range";
			throw logic_error("ERR: out of range");
			return nullptr;
		}
		if (pos < 0)				return nullptr;
		if (pos == 0)				return m_front;
		if (pos == m_listSize - 1)	return m_back;

		Node* member{};
		if (pos <= m_listSize / 2) {
			member = m_front;

			for (int i = 0; i < pos; ++i) {
				member = member->next;
			}
		}
		else {
			member = m_back;

			for (int i = m_listSize - 1; i > pos; --i) {
				member = member->prev;
			}
		}

		return member;
	}

public:
	Dlist() {

	}
	~Dlist() {
		clear();
	}

	/* Удаляет все члены списка */
	void clear() {
		if (!isEmpty()) {
			Node* member = m_front;
			Node* nextMember;
			for (int i = 0; i < m_listSize; i++) {
				nextMember = member->next;
				delete member;
				member = nextMember;
			}
			m_front = nullptr;
			m_back = nullptr;
			m_listSize = 0;
		}
	}
	
	/* Вернуть значение списка в позиции pos */
	T pos_back(T pos) const {
		Node* member = listSearch(pos);
		return member->data;
	}

	/* Установить целочисленное значение списка в позиции pos */
	Dlist& set(int pos, T data) {
		Node* member = listSearch(pos);
		member->data = data;
		return (*this);
	}

	/* Вставить новый член списка после позиции pos */
	Dlist& push(int pos, T data = 0) {
		Node tmpNode{ 0, m_front };									// Звено, предшествующее первому звену 
		Node* member = (pos == -1) ? &tmpNode : listSearch(pos);	// Звено, предшествующее новому звену	
		Node* nextMember = member->next;

		member->next = new Node;
		member->next->prev = (pos == -1) ? (nullptr) : (member);
		member->next->data = data;

		member->next->next = nextMember;
		if (nextMember == nullptr) { m_back = member->next; }
		if (pos < 0) { m_front = member->next; }
		++m_listSize;

		return (*this);
	}

	/* Удалить член списка из заданной позиции pos */
	T remove(int pos) {
		if (isEmpty()) {
			throw logic_error("ERR: list is empty!");
			return 0;
		}
		Node* prevMember = listSearch(pos - 1);
		if (prevMember != nullptr) {				// Если нужное звено находится не в начале
			Node* member = prevMember->next;
			T data = member->data;

			prevMember->next = member->next;
			if (pos != m_listSize - 1) member->next->prev = member->prev;
			delete member;

			if (pos == m_listSize - 1) m_back = prevMember;
			--m_listSize;

			return data;
		}
		else {										//	if (prevMember != nullptr)									
			T data = m_front->data;
			Node* nextMember = m_front->next;
			delete m_front;

			m_front = nextMember;
			if(m_listSize > 1) m_front->prev = nullptr;
			--m_listSize;

			return data;
		}
	}

	/* Возвращает размер списка */
	unsigned int size() const { return m_listSize; }

	/* Возвращает, пустой ли список или нет */
	bool isEmpty() const { return m_listSize == 0; }

	/* Добавляет новое звено в начало списка */
	Dlist& push_front(int data = 0) { return push(-1, data); }

	/* Добавляет новое звено в конец списка */
	Dlist& push_back(int data = 0) { return push(m_listSize - 1, data); }

	/* Возвращает значение в последнем звене списка */
	T back() const { return pos_back(m_listSize - 1); }

	/* Возвращает значение в первом звене списка */
	T front() const { return pos_back(0); }

	/* Удаляет последнее звено списка */
	T pop_back() { return remove(m_listSize - 1); }

	/* Удаляет первое звено списка */
	T pop_front() { return remove(0); }

	/* Меняет два звена списка местами (без копирования) */
	bool swap(int pos1, int pos2) {
		if (pos1 == pos2)			return true;
		if (pos1 > pos2)			swap(pos1, pos2); 
		if (pos2 >= m_listSize)		return false;

		Node* elem1 = listSearch(pos1);
		Node* elem2 = listSearch(pos2);
		Node* prev1 = elem1->prev;
		Node* next1 = elem1->next;
		Node* prev2 = elem2->prev;
		Node* next2 = elem2->next;

		elem1->next				= next2;
		elem1->prev				= prev2;

		elem2->next				= next1;
		elem2->prev				= prev1;

		if (prev1) prev1->next	= elem2;
		else m_front			= elem2;
		next1->prev				= elem2;

		if (next2) next2->prev	= elem1;
		else m_back				= elem1;
		prev2->next				= elem1;

		return true;
	}

	bool out(void) const {
		Node* currentMember = m_front;
		for (int i = 0; i < m_listSize; ++i) {
			std::cout << currentMember->data << "\t";
			if ((i + 1) % 50 == 0) std::cout << std::endl;
			currentMember = currentMember->next;
		}
		std::cout << std::endl;
		return true;
	}
};

int main() {
	system("chcp 65001"); system("cls");

	Dlist<int> list;
	list.push_back(25).push_back(125).push_back(15).push_back(835).push_back(9).push_back(-234);
	cout << "Начальный список:" << endl;
	list.out();

	cout << endl << "Свап элементов (1, 3) из середины:" << endl;
	list.swap(1, 3);
	list.out();

	cout << endl << "Свап элементов (0, 3) левый крайний:" << endl;
	list.swap(0, 3);
	list.out();

	cout << endl << "Свап элементов (2, 5) правый крайний:" << endl;
	list.swap(2, 5);
	list.out();

	cout << endl << "Свап элементов (0, 5) оба крайних:" << endl;
	list.swap(0, 5);
	list.out();

	cout << "\nНажмите ввод чтобы закрыть" << endl;
	cin.get();
	return 0;
}