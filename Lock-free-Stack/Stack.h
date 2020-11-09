#pragma once
#include <iostream>
#include <atomic>
#include "Node.h"

using namespace std;

template<class T>
class Stack {
private:
	atomic<Node<T> *> head;	//언제나 ptrWithCnt 상태 유지
public:
	Stack() {
		head = nullptr;
	}
	void push(Node<T> *newNode) {
		while (true) {
			Node<T> *t = head;
			newNode->cnt += 1;
			newNode->next = t->ptrWithoutCnt(t);	//next에는 정상 주소 ok
			//체크할 땐 cnt와 함께 ok
			if (atomic_compare_exchange_strong(&head, &t, newNode->ptrWithCnt(newNode))) {
				break;
			}
		}
	}
	Node<T>* pop() {
		while (true) {
			Node<T>* t = head;
			if (t == nullptr)
				return nullptr;	//continue;
			//체크할 땐 cnt와 함께 ok
			Node<T>* pt = t->ptrWithoutCnt(t);

			if (atomic_compare_exchange_strong(&head, &t, pt->next->ptrWithCnt(pt->next))) {
				pt->cnt += 1;
				return pt;
			}
		}
	}
	int size() {
		int rtn = 0;
		Node<T> *p = head;
		for (p = p->ptrWithoutCnt(p); p != nullptr; p = p->next)
			rtn++;
		return rtn;
	}
	void print() {
		Node<T> *p = head;
		for (p = p->ptrWithoutCnt(p); p != nullptr; p = p->next)
			cout << p->data << " ";
		cout << "\n";
	}
};