#include <iostream>
#include <mutex>
#include <numeric>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <time.h>
#include <algorithm>


using namespace std;

template <class T>
class myVec
{
public:
	myVec<T>& operator<<(int&&);
	myVec<T>& operator<<(const int&);
	int operator()();
	void factorial_of_sum();
private:
	T mtx;
	int sum();
	vector<int> v;
};


template <class T>
myVec<T>& myVec<T>::operator<<(int&& n) {
	unique_lock<T> lck(mtx);
	v.emplace_back(n);
	return *this;
}

template <class T>
myVec<T>& myVec<T>::operator<<(const int& n) {
	unique_lock<T> lck(mtx);
	cout << "Inserting " << n << endl;
	v.emplace_back(n);
	return *this;
}

template <class T>
int myVec<T>::operator()() {
	unique_lock<T> lck(mtx);
	return sum();
}

template <class T>
int myVec<T>::sum() {
	unique_lock<T> lck(mtx);
	return accumulate(v.begin(), v.end(), 0);
}

template <class T>
void myVec<T>::factorial_of_sum() {
	lock_guard<T> lck(mtx);
	int s = sum();
	int fact = 1;
	for (int i = 2; i <= s; i++) {
		fact *= i;
	}

	cout << "\nFactorial of " << s << " is " << fact << endl;
}


int main (int argc, char* argv[])
{
	myVec<recursive_mutex> vec;
	// myVec<mutex> vec;
	srand(time(NULL));
	/*
	for (int i = 1; i < argc; i++) {
		vec << atoi(argv[i]);
	}
	//*/
	

	/*
	vector<thread> th;

	for (int i = 0; i < 10; i++) {
		int n = rand() % 10 + 1;
		cout << n << " ";
		// th.emplace_back(thread(static_cast<myVec& (myVec::*)(int&&)>(&myVec::operator<<), &vec, ref(n)));
		th.emplace_back(thread([&]() { vec<< n;}));
	}
	
	for_each(th.begin(), th.end(), mem_fn(&thread::join));

	cout << "\nSum is " << vec() << endl;
	//*/


	//*
	vector<thread> th;

	for (int i = 0; i < 5; i++) {
	int n = rand() % 5 + 1;
	// cout << n << " ";
	th.emplace_back(thread([&]() { vec<< n;}));
	vec.factorial_of_sum();
	}

	for_each(th.begin(), th.end(), mem_fn(&thread::join));	
	//*/
	
	return EXIT_SUCCESS;
}