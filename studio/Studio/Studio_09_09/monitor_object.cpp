
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
		int n;
		cout << list.pop_front(n) << " ";
	}

	cout << endl;
	//*/


	int numbers[200];

	for (int i = 0; i < 200; i++) {
		numbers[i] = rand() % 100 + 1;
		cout << numbers[i] << " ";
	}
		
	cout << endl;

	/*
	for (int i = 0; i < 20; i++) {
		list.push_back(numbers[i]);
	}

	cout << "List: \n";

	for (int i = 0; i < 20; i++) {
		int n;
		list.pop_front(n);
	}

	cout << endl;

	//*/

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
		int n;
		list.pop_back(n);
	}
	//*/


	/*
	cout << "List: " << endl;

	vector<thread> th;

	for (int i = 0; i < 20; i++) {
		//th.push_back(thread(&SyncList<int>::push_front, &list, ref(numbers[i])));	

		th.push_back(thread([&, i]() {
			list.push_front(numbers[i]);
		}));
	}

	for (auto& t : th) {
		t.join();
	}

	cout << endl;

	th.resize(0);
	
	for (int i = 0; i < 20; i++) {
		int n;
		// th.push_back(thread(&SyncList<int>::pop_back, &list, ref(n)));

		th.push_back(thread([&, i]() {
			int n;
			list.pop_back(n);
		}));
	}

	for (auto& t : th) {
		t.join();
	}
	//*/


	SyncList<int> marked_list(1, 5);

	cout << "List: " << endl;

	vector<thread> th;

	for (int i = 0; i < 50; i++) {
		int n = rand() % 100 + 1;
		int ref_store;
		if (n % 2 == 0) {
			if (n >= 50) {
				th.push_back(thread(&SyncList<int>::push_front, &marked_list, ref(numbers[i])));
			}
			else {
				th.push_back(thread(&SyncList<int>::push_back, &marked_list, ref(numbers[i])));
			}
		}
		else {
			if (n > 50) {
				th.push_back(thread(&SyncList<int>::pop_front, &marked_list, ref(ref_store)));
			}
			else {
				th.push_back(thread(&SyncList<int>::pop_back, &marked_list, ref(ref_store)));
			}
		}
	}

	for (auto& t : th) {
		t.join();
	}

	cout << endl;

	//*/






	return EXIT_SUCCESS;
}