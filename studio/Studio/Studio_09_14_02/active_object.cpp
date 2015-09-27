
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <random>
#include <chrono>
#include "active_object.h"


int numbers[500];

template <class T>
void pushFifty(ActiveObj<T>& obj) {
	for (int i = 0; i < 500; i++) {
		obj.enque(numbers[i]);
	}
}

template <class T>
void pushTwenty(ActiveObj<T>& obj) {
	for (int i = 0; i < 20; i++) {
		obj.enque(numbers[i]);
	}
}

/*
template <class T>
void popFifty(ActiveObj<T>& obj) {
	int ref_store;
	for (int i = 0; i < 50; i++) {
		obj.run_service(ref_store);
	}
}
//*/


int main(int argc, char* argv[])
{
	ActiveObj<int> obj;
	srand(time(NULL));


	for (int i = 0; i < 500; i++) {
		numbers[i] = rand() % 500 + 1;
		cout << numbers[i] << " ";
	}

	cout << endl;

	/*
	cout << "List: " << endl;
	
	vector<thread> th;

	th.push_back(thread(pushFifty<int>, ref(obj)));
	th.push_back(thread(popFifty<int>, ref(obj)));


	for (auto& t : th) {
		t.join();
	}

	cout << endl;
	//*/

	/*
	cout << "Starting pushing" << endl;
	pushFifty(obj);

	cout << "Active now" << endl;
	obj.active();
	
	this_thread::sleep_for(chrono::seconds(3));
	cout << "Pushing again" << endl;
	pushFifty(obj);
	//*/

	/*
	cout << "Starting pushing" << endl;
	pushFifty(obj);

	cout << "Active now" << endl;
	obj.active();
	
	cout << "Sleep 3 seconds" << endl;
	this_thread::sleep_for(chrono::seconds(3));
	
	cout << "Pushing again" << endl;
	pushFifty(obj);
	
	cout << "Starting Deactiving" << endl;
	obj.deactive();

	cout << "Active again" << endl;
	obj.active();

	cout << endl;
	//*/


	//*

	ActiveObj<int> obj2;
	ActiveObj<int> obj1(&obj2);	
	
	pushTwenty(obj1);


	cout << "Active obj1 now" << endl;
	future<void> f1 = obj1.active();
	
	cout << "Pushing to obj1" << endl;
	pushTwenty(obj1);

	cout << endl;
	//*/
		
	cout << "Sleep 5 seconds to wait threads" << endl;
	this_thread::sleep_for(chrono::seconds(5));

	cout << "Active obj2" << endl;
	future<void> f2 = obj2.active();

	f1.wait();
	f2.wait();

	cout << "Now safe to exit" << endl;

	
	return EXIT_SUCCESS;
}