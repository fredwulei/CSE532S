//
//  main.cpp
//  studio2
//
//  Lei, Ren, Yiheng
//

#include <iostream>
#include <vector>
#include <numeric>
#include <thread>
#include <mutex>
#include <future>


using namespace std;




/*******************
* Exercise 2 - Class
*******************/



template <class T> 
class SalesItems2 {
private:
	vector<int> items;
	T myMutex;
public:

	SalesItems2(T);

	friend SalesItems2& operator<<(SalesItems2& rh, const int& i);
	void factorial_of_sum(promise<long> && p);
	//void factorial_of_sum(long long& result);
	void printAll();
	int operator()();
};


template <class T>
SalesItems2<T>::SalesItems2<T>(T &m) {
	//myMutex = 
	items = vector<int>();
}

template <class T>
SalesItems2<T>& operator<<(SalesItems2<T>& rh, const int& i) {
	lock_guard<T> guard(rh.myMutex);
	rh.items.push_back(i);
	return rh;
}

template <class T>
int SalesItems2<T>::operator()() {
	//lock_guard<mutex> guard(myMutex);
	return accumulate(items.begin(), items.end(), 0);
}




class SalesItems {
private:
	vector<int> items;
	mutex myMutex;
public:

	SalesItems();

	friend SalesItems& operator<<(SalesItems& rh, const int& i);
	void factorial_of_sum(promise<long> && p);
	//void factorial_of_sum(long long& result);
	void printAll();
	int operator()();
};



SalesItems::SalesItems() {
	items = vector<int>();
}


/***********************
* Exercise 2 - Operators
************************/
SalesItems& operator<<(SalesItems& rh, const int& i) {
	lock_guard<mutex> guard(rh.myMutex);
	rh.items.push_back(i);
	return rh;
}

int SalesItems::operator()() {
	//lock_guard<mutex> guard(myMutex);
	return accumulate(items.begin(), items.end(), 0);
}


void SalesItems::printAll() {
	/*
	lock_guard<mutex> guard(myMutex);
	printf("Count: %lu\n", items.size());
	for (unsigned i = 0; i<items.size(); ++i) {
	printf("%d: %d\n", i, items[i]);
	}
	*/
	printf("Finished.\n");
}


void SalesItems::factorial_of_sum(promise<long> && p) {
	lock_guard<mutex> guard(myMutex);
	int sum = (*this)();
	long result = 1;
	for (int i = 1; i <= sum; ++i) {
		result *= i;
	}
	p.set_value(result);
}



/*
void SalesItems::factorial_of_sum(long long& result) {
	lock_guard<mutex> guard(myMutex);
	
	int sum = (*this)();
	printf("sum: %d\n", sum);

	result = 1;
	for (int i = 1; i <= sum; ++i) {
		result *= i;
		printf("sum: %lld\n", result);
	}

	
}
*/

//
void insertItem(SalesItems& s, int i) {
	s << i;
}

void printSum(SalesItems& s) {
	printf("Sum: %d\n", s());
}


void insertItemsWithVector(SalesItems &s, vector<int> items) {
	for (int item : items) {
		s << item;
		printf("Inserted: %d\n", item);
		printSum(s);
	}
}




void insert10Items(SalesItems& s, int i) {

	for (int x = i; x < 10 + i; ++x) {
		s << x;

	}
}

void printAll(SalesItems &s) {
	s.printAll();
}

void getValue(promise<int> && p) {
	p.set_value(111);
}


//void func2() {
//	lock_guard<mutex> guard(testMutex);
//	printf("Func2");
//}
//
//void func1() {
//	printf("Before Func1 locked");
//	lock_guard<mutex> guard(testMutex);
//	printf("Func1");
//	func2();
//}



int main(int argc, const char * argv[]) {
	// insert code here...



	SalesItems s;



	/***********************
	* Exercise 3 - Operators
	************************/


	/*
	
	vector<int> t1Items{ 1, 1, 1, 1};
	vector<int> t2Items{ 2, 2, 2, 2};
	thread t1(insertItemsWithVector, ref(s), t1Items);
	thread t2(insertItemsWithVector, ref(s), t2Items);

	t1.join();
	t2.join();
	

	
	promise<long> p;
	auto f = p.get_future();
	thread t3(&SalesItems::factorial_of_sum, &s, move(p));
	//thread t3(&getValue, move(p));
	t3.join();
	long factorial = f.get();
	printf("Factorial is: %ld\n", factorial);
	
	*/


	mutex m;

	SalesItems2<mutex> s2(m);


	/*

	long long factorial;

	thread t3(&SalesItems::factorial_of_sum, &s, ref(factorial));
	//thread t3(&getValue, move(p));

	//thread t3(&SalesItems::printAll, &s);

	t3.join();
	printf("Factorial is: %lld\n", factorial);

	*/


	/***********************
	* Exercise 3 - Operators
	************************/


	//
	//thread t3(printSum, ref(s));

	/*thread t4(insert10Items, ref(s), 99);

	thread t5(printAll, ref(s));*/
	//t3.join();



	/*t4.join();
	t5.join();*/



	//func1();


	system("pause");
	return 0;
}
