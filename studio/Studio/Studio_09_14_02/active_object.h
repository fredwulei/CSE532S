#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include <future>
#include "synchronized_list.h"

using namespace std;

template <class T>
class ActiveObj {
public:
	// ActiveObj() :list(SyncList<T>(1, 500)), isActive(false) {};
	ActiveObj(ActiveObj<T> *pointer = nullptr) :
		ptr(pointer), list(SyncList<T>(1, 500)), isActive(false) {};
	void enque(const T&);
	future<void> active();
	void deactive();
private:
	SyncList<T> list;
	ActiveObj<T> *ptr;
	void run_service();
	bool isActive;
};


template <class T>
void ActiveObj<T>::enque(const T& value) {
	list.push_front(value);
}

template <class T>
future<void> ActiveObj<T>::active() {	
	isActive = true;
	list.reset();
	return async(&ActiveObj<T>::run_service, this);
}

template <class T>
void ActiveObj<T>::deactive() {
	isActive = false;
	list.shut_down();
}

template <class T>
void ActiveObj<T>::run_service() {
	T value;
	int counter = 0;
	while (isActive) {
		if (list.empty()) {
			// cout << "I'm waiting " << endl;
			counter++;
			if (counter % 1000000 == 0) {
				isActive = false;
			}
			this_thread::yield();
		}
		else {
			// cout << "I'm running" << endl;
			list.pop_back(value);

			if (ptr) {
				ptr->enque(value);
			}
		}
	}
}

#endif