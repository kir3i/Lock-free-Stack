//2016920029 ���ÿ�
#include <iostream>
#include <thread>
#include <chrono>
#include "Node.h"
#include "Stack.h"

using namespace std;

Stack<int> s1;
Stack<int> s2;
const int N = 30;
const int M = 5;
const int REPEAT = 30000;
const int INITNODE = 10000000;
const int THREADNUM = 9;

void threadBody() {
	//do task
	for (int i = 0; i < REPEAT; i++) {
		for (int j = 0; j < N; j++) {
			Node<int> *p = nullptr;
			while (p == nullptr)
				p = s2.pop();
			s1.push(p);
		}
		for (int j = 0; j < M; j++) {
			Node<int> *p = nullptr;
			while (p == nullptr)
				p = s1.pop();
			s2.push(p);
		}
	}
}

int main(void) {
	//set timer
	chrono::time_point<chrono::system_clock> startTime, endTime;
	startTime = chrono::system_clock::now();

	//create Nodes
	for (int i = 0; i < INITNODE; i++)
		s2.push(new Node<int>(i));

	//make threads
	thread* threads;
	if (THREADNUM)
	{
		threads = new thread[THREADNUM];
		for (int i = 0; i < THREADNUM; i++)
			threads[i] = thread(threadBody);
	}

	//do task
	for (int i = 0; i < REPEAT; i++) {
		for (int j = 0; j < N; j++) {
			Node<int> *p = nullptr;
			while (p == nullptr)
				p = s2.pop();
			s1.push(p);
		}
		for (int j = 0; j < M; j++) {
			Node<int> *p = nullptr;
			while (p == nullptr)
				p = s1.pop();
			s2.push(p);
		}
	}

	//wait other threads
	for (int i = 0; THREADNUM && i < THREADNUM; i++)
		threads[i].join();

	//check
	cout << "2016920029 ���ÿ�\n";
	cout << "�ʱ⿡ s2�� ���� ����� ��: " << INITNODE << "\n";
	cout << "Thread�� ����: " << (THREADNUM + 1) << "\n";
	cout << "�ݺ� Ƚ��: " << REPEAT << "\n";
	cout << "N: " << N << ", M: " << M << "\n";
	cout << "s1 Size: " << s1.size() << " ����: " << ((THREADNUM + 1)*(N - M)*REPEAT) << "\n";
	cout << "s2 Size: " << s2.size() << " ����: " << (INITNODE - ((THREADNUM + 1)*(N - M)*REPEAT)) << "\n";

	endTime = chrono::system_clock::now();
	cout << "�ɸ� �ð�: " << (chrono::duration_cast<chrono::milliseconds>(endTime - startTime)).count() << "ms\n";
	return 0;
}