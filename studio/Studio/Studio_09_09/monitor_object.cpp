
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <random>
#include <chrono>
#include "synchronized_list.h";


int main(int argc, char* argv[])
{
	SyncList<int> list;
	srand(time(NULL));

	/*
	for (int i = 1; i < argc; i++) {
		list.push_back(atoi(argv[i]));
	}

	cout << "List: ";

	for (int i = 1; i < argc; i++) {
		cout << list.pop_front() << " ";
	}

	cout << endl;
	//*/


	int numbers[20];

	for (int i = 0; i < 20; i++) {
		numbers[i] = rand() % 100 + 1;
	//	cout << numbers[i] << " ";
	}


	/*
	vector<thread> th;

	for (int i = 0; i < 20; i++) {
		th.push_back(thread([&]() {
			list.push_front(numbers[i]); 
		}));
	}

	cout << "List: ";

	for (auto& t : th) { 
		t.join(); 
	}

	cout << endl;

	for (int i = 0; i < 20; i++) {
		list.pop_back();
	}
	//*/


	//*
	vector<thread> th;

	for (int i = 0; i < 20; i++) {
		th.push_back(thread([&]() {
			list.push_front(numbers[i]);
		}));
	}

	cout << "List: ";

	for (auto& t : th) {
		t.join();
	}

	cout << endl;

	for (int i = 0; i < 20; i++) {
		th.push_back(thread([&]() {
			list.pop_back();
		}));
	}

	for (auto& t : th) {
		t.join();
	}
	//*/

	return EXIT_SUCCESS;
}