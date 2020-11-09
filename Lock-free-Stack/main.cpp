//2016920029 유시온
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
	cout << "2016920029 유시온\n";
	cout << "초기에 s2에 넣은 노드의 수: " << INITNODE << "\n";
	cout << "Thread의 개수: " << (THREADNUM + 1) << "\n";
	cout << "반복 횟수: " << REPEAT << "\n";
	cout << "N: " << N << ", M: " << M << "\n";
	cout << "s1 Size: " << s1.size() << " 참값: " << ((THREADNUM + 1)*(N - M)*REPEAT) << "\n";
	cout << "s2 Size: " << s2.size() << " 참값: " << (INITNODE - ((THREADNUM + 1)*(N - M)*REPEAT)) << "\n";

	endTime = chrono::system_clock::now();
	cout << "걸린 시간: " << (chrono::duration_cast<chrono::milliseconds>(endTime - startTime)).count() << "ms\n";
	return 0;
}