#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
#include <algorithm>

template <class T>
class DoublyLinkedList {

public:
	struct Node {
		T data;
		Node* prev;
		Node* next;

		Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
	};
	Node* head;
	Node* tail;
	size_t count;
	Node* getHead() const { return head; }
	Node* gettil() const { return tail; }

	DoublyLinkedList() : count(0), head(nullptr), tail(nullptr) {}
	~DoublyLinkedList() { clear(); }

	void add(const T& data) {
		Node* newNode = new Node(data);
		if (!head) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		count = +1;
	}

	void remove(const T& data) {
		Node* current = head;
		while (current) {
			if (current->data == data) {
				if (current->prev) current->prev->next = current->next;
				if (current->next) current->next->prev = current->prev;
				if (current == head) head = current->next;
				if (current == tail) tail = current->prev;
				delete current;
				return;
			}
			current = current->next;
		}
		count = -1;
	}

	void display() const {
		Node* current = head;
		while (current) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}

	void searchByType(const std::string& type) const {
		Node* current = head;
		while (current) {
			if (current->data.getType() == type) {
				std::cout << current->data << std::endl;
			}
			current = current->next;
		}
	}

	void sort() {
		if (!head || !head->next) return;

		for (Node* i = head; i; i = i->next) {
			for (Node* j = i->next; j; j = j->next) {
				if (j->data < i->data) {
					std::swap(i->data, j->data);
				}
			}
		}
	}

	void reverse() {
		Node* current = head;
		Node* temp = nullptr;
		while (current) {
			temp = current->prev;
			current->prev = current->next;
			current->next = temp;
			current = current->prev;
		}

		if (temp) head = temp->prev;
	}

	void clear() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
	}

	bool empty() const {
		return count == 0;
	}

	size_t size() const {
		size_t count = 0;
		Node* current = head;
		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}

	T& at(size_t index) {
		if (index >= count) throw std::out_of_range("Index out of range");

		Node* current = head;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->data;
	}

	const T& at(size_t index) const {
		if (index >= count) throw std::out_of_range("Index out of range");

		Node* current = head;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->data;
	}
};

#endif // DOUBLYLINKEDLIST_H
