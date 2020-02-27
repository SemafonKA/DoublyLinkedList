#include <cstdlib>
#include <iostream>
using namespace std;

template<typename T>
class dList {
private:
	class Node {
	public:
		T data;
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
		}
		if (pos < 0)				return nullptr;
		if (pos == 0)				return m_front;
		if (pos == m_listSize - 1)	return m_back;

		if (pos <= m_listSize / 2) {
			Node* member = m_front;

			for (int i = 0; i < pos; ++i) {
				member = member->next;
			}
		}
		else {
			Node* member = m_back;

			for (int i = m_listSize - 1; i > pos; --i) {
				member = member->prev;
			}
		}

		return member;
	}

public:
	List() {

	}
	List(unsigned int listSize) {
		resize(listSize);
	}
	~List() {
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

	/* Изменить полный размер списка */
	void resize(int newListSize) {
		m_listSize = newListSize;

		if (!isEmpty()) {
			if (m_front == nullptr) { m_front = new Node; }

			Node* member = m_front;
			Node* nextMember = m_front->next;
			for (int i = 1; i < m_listSize; i++) {
				if (nextMember == nullptr) {
					member->next = new Node;
					nextMember = member->next;
				}
				member = nextMember;
				nextMember = member->next;
			}
			m_back = member;

			while (nextMember != nullptr) {
				member = nextMember;
				nextMember = member->next;
				delete member;
			}

			listCheck();
		}
	}

	/* Вернуть целочисленное значение списка в позиции pos */
	int pos_back(int pos) const {
		Node* member = listSearch(pos);
		return member->date;
	}

	/* Установить целочисленное значение списка в позиции pos */
	List& set(int pos, int date) {
		Node* member = listSearch(pos);
		member->date = date;
		return (*this);
	}

	/* Вставить новый член списка после позиции pos */
	List& push(int pos, int date = 0) {
		Node tmpNode{ 0, m_front };									// Звено, предшествующее первому звену 
		Node* member = (pos == -1) ? &tmpNode : listSearch(pos);	// Звено, предшествующее новому звену	
		Node* nextMember = member->next;

		member->next = new Node;
		member->next->date = date;

		member->next->next = nextMember;
		if (nextMember == nullptr) { m_back = member->next; }
		if (pos < 0) { m_front = member->next; }
		++m_listSize;

		return (*this);
	}

	/* Удалить член списка из заданной позиции pos */
	int remove(int pos) {
		if (isEmpty()) {
			throw logic_error("ERR list is empty!");
			return 0;
		}
		Node* prevMember = listSearch(pos - 1);
		if (prevMember != nullptr) {				// Если нужное звено находится не в начале
			Node* member = prevMember->next;
			int date = member->date;

			prevMember->next = member->next;
			delete member;

			if (pos == m_listSize - 1) m_back = prevMember;
			--m_listSize;

			return date;
		}
		else {										//	if (prevMember != nullptr)									
			int date = m_front->date;
			Node* nextMember = m_front->next;
			delete m_front;

			m_front = nextMember;
			--m_listSize;

			return date;
		}
	}

	/* Возвращает размер списка */
	unsigned int size() const { return m_listSize; }

	/* Возвращает, пустой ли список или нет */
	bool isEmpty() const { return m_listSize == 0; }

	/* Добавляет новое звено в начало списка */
	List& push_front(int date = 0) { return push(-1, date); }

	/* Добавляет новое звено в конец списка */
	List& push_back(int date = 0) { return push(m_listSize - 1, date); }

	/* Возвращает значение в последнем звене списка */
	int back() const { return pos_back(m_listSize - 1); }

	/* Возвращает значение в первом звене списка */
	int front() const { return pos_back(0); }

	/* Удаляет последнее звено списка */
	int pop_back() { return remove(m_listSize - 1); }

	/* Удаляет первое звено списка */
	int pop_front() { return remove(0); }
};


int main() {
	system("chcp 65001"); system("cls");

	cin.get();
	return 0;
}