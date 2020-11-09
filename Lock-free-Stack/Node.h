#pragma once
template<class T>
struct Node {
	T data;
	Node *next;
	long long cnt;
	Node(const T& data) {
		this->data = data;
		next = nullptr;
		cnt = 0;
	}
	Node<T>* ptrWithCnt(Node<T>* ptr) {
		return (Node<T> *)((long long)ptr | ((cnt % 4096) << 52));	//���� 12bit�� cnt ����
	}
	Node<T>* ptrWithoutCnt(Node<T>* ptr) {
		return (Node<T> *)((long long)ptr & (0xFFFFFFFFFFFFF));	//���� 52bit��
	}
};

