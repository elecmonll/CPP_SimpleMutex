Модель взаимодействия потребителя и производителя, используя Мьютекс
#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>
#include <mutex>

#define THREADCOUNT 1
#define TIME_OUT 10
#define RESOURCE 5
using namespace std;
mutex mtx;
void Producer(int& buf) {
	int count = 0;
	int value;
	while (count < 20) {
		mtx.lock();
		if (buf > 0) {
			buf -= RESOURCE;
		}
		cout << "Production #" << GetCurrentThreadId() << " and Buf = " << buf << endl;
		mtx.unlock();
		Sleep(TIME_OUT);
		count++;
	}
}
void Consumer(int& buf) {
	int count = 0;
	while (count < 20) {
		mtx.lock();
		buf += RESOURCE;
		cout << "Consumer #" << GetCurrentThreadId() << " and Buf = " << buf << endl;
		mtx.unlock();
		Sleep(TIME_OUT);
		count++;
	}
}

class Synchronization {
public:
	vector<thread> aThreadProducer;
	vector<thread> aThreadConsumer;
	int buf = 0;

public:
	void Mutex();
	//void Semaphore();
};
void Synchronization::Mutex() {
	aThreadProducer.reserve(THREADCOUNT);
	aThreadConsumer.reserve(THREADCOUNT);
	for (int i = 0; i < THREADCOUNT; i++) {
		aThreadProducer.push_back(thread(Producer, ref(buf)));
		aThreadConsumer.push_back(thread(Consumer, ref(buf)));
	}
	for (auto&thd : aThreadProducer) {
		thd.join();
	}
	for (auto& thd : aThreadConsumer) {
		thd.join();
	}
}
int main() {
	setlocale(LC_ALL, "rus");
	int valueInt;
	bool valueBool = true;
	
	Synchronization synchron;
	while (valueBool) {
		cout << "1. Mutex\n0. End.\nВыберите режим работы: ";
		cin >> valueInt;
		cout << "=======================================================\n";

		switch (valueInt) {
		case 1:
			synchron.Mutex();
			cout << "=======================================================\n";
			cout << endl;
			break;

		case 0:
			valueBool = false;
			break;
		}
	}
	return 0;
}