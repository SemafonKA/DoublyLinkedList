#include <cstdlib>
#include <iostream>
using namespace std;

template<typename T>
class Dlist {
private:
	class Node {
	public:
		T date{};
		Node* next{};
		Node* prev{};
	};

	Node* m_front{};
	Node* m_back{};

	int m_listSize{};

	void listCheck() {
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
	Dlist(unsigned int listSize) {
		//resize(listSize);
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
		return member->date;
	}

	/* Установить целочисленное значение списка в позиции pos */
	Dlist& set(int pos, T date) {
		Node* member = listSearch(pos);
		member->date = date;
		return (*this);
	}

	/* Вставить новый член списка после позиции pos */
	Dlist& push(int pos, T date = 0) {
		Node tmpNode{ 0, m_front };									// Звено, предшествующее первому звену 
		Node* member = (pos == -1) ? &tmpNode : listSearch(pos);	// Звено, предшествующее новому звену	
		Node* nextMember = member->next;

		member->next = new Node;
		member->next->prev = (pos == -1) ? (nullptr) : (member);
		member->next->date = date;

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
			T date = member->date;

			prevMember->next = member->next;
			if (pos != m_listSize - 1) member->next->prev = member->prev;
			delete member;

			if (pos == m_listSize - 1) m_back = prevMember;
			--m_listSize;

			return date;
		}
		else {										//	if (prevMember != nullptr)									
			T date = m_front->date;
			Node* nextMember = m_front->next;
			delete m_front;

			m_front = nextMember;
			if(m_listSize > 1) m_front->prev = nullptr;
			--m_listSize;

			return date;
		}
	}

	/* Возвращает размер списка */
	unsigned int size() const { return m_listSize; }

	/* Возвращает, пустой ли список или нет */
	bool isEmpty() const { return m_listSize == 0; }

	/* Добавляет новое звено в начало списка */
	Dlist& push_front(int date = 0) { return push(-1, date); }

	/* Добавляет новое звено в конец списка */
	Dlist& push_back(int date = 0) { return push(m_listSize - 1, date); }

	/* Возвращает значение в последнем звене списка */
	T back() const { return pos_back(m_listSize - 1); }

	/* Возвращает значение в первом звене списка */
	T front() const { return pos_back(0); }

	/* Удаляет последнее звено списка */
	T pop_back() { return remove(m_listSize - 1); }

	/* Удаляет первое звено списка */
	T pop_front() { return remove(0); }
};

	//todo: Сделать swap

int main() {
	system("chcp 65001"); system("cls");

	Dlist<int> list;

	/*constexpr auto SIZE2 = 40'000'000;
	constexpr auto SIZE3 = 2'000'000;
	cout << "All: ";
	for (int i = 0; i < SIZE2; i += SIZE3) {
		cout << "[  ]";
	}
	cout << endl << "     ";

	for (int i = 0; i < SIZE2; ++i) {
		list.push_back(i);
		if (i % SIZE3 == 0) cout << " || ";
	}
	cout << endl;
	list.clear();

	if (list.isEmpty()) cout << "Лист пустой!!";
	else cout << "Лист не пустой((";
	cout << endl;*/

	cout << "\nНажмите ввод чтобы закрыть";
	cin.get();
	return 0;
}