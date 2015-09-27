
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <random>
#include <chrono>
#include "synchronized_list.h";


int numbers[200];

void pushFifty(SyncList<int>& list) {
	for (int i = 0; i < 50; i++) {
		if (i % 2 == 0)
			list.push_front(numbers[i]);
		else
			list.push_back(numbers[i]);
	}
}

void popFifty(SyncList<int>& list) {
	int ref_store;
	for (int i = 0; i < 50; i++) {
		if (i % 2 == 0)
			list.pop_back(ref_store);
		else
			list.pop_front(ref_store);
	}
}


int main(int argc, char* argv[])
{
	SyncList<int> marked_list(1, 5);
	srand(time(NULL));


	for (int i = 0; i < 200; i++) {
		numbers[i] = rand() % 100 + 1;
		cout << numbers[i] << " ";
	}

	cout << endl;
	
	cout << "List: " << endl;

	vector<thread> th;

	th.push_back(thread(pushFifty, ref(marked_list)));
	th.push_back(thread(popFifty, ref(marked_list)));


	for (auto& t : th) {
		t.join();
	}

	cout << endl;

	//*/






	return EXIT_SUCCESS;
}