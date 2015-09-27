#ifndef SYNCHRONIZED_LIST_H
#define SYNCHRONIZED_LIST_H

#include <iostream> 
#include <vector>
#include <mutex>


using namespace std;

template <class T>
class SyncList {
public:
	SyncList() :low_mark(0), high_mark(1) {};
	SyncList(size_t l, size_t h) :
		low_mark(l), high_mark(h) {
		if (low_mark < 0)   low_mark = 0;
		if (high_mark <= 0) high_mark = 1;
	};
	SyncList(const SyncList&);
	void push_back(const T&);
	void pop_back(T&);
	void push_front(const T&);
	void pop_front(T&);
private:
	size_t low_mark;
	size_t high_mark;
	mutable mutex mtx;
	condition_variable cond;
	vector<T> vec;
};

template <class T>
SyncList<T>::SyncList(const SyncList<T>& other) {
	lock(mtx, other.mtx);
	lock_guard<mutex> lck1(mtx, adopt_lock);
	lock_guard<mutex> lck2(other.mtx, adopt_lock);
	low_mark = other.low_mark;
	high_mark = other.high_mark;
	vec = other.vec;
}

template <class T>
void SyncList<T>::push_back(const T& value)
{
	unique_lock<mutex> lck(mtx);

	cond.wait_for(lck, std::chrono::milliseconds(100), [this] {
		return vec.size() <= high_mark;
	});

	/*
	cond.wait(lck, [this] {
		return vec.size() <= high_mark;
	});
	//*/
	cout << "Push back " << value << endl;
	vec.push_back(value);
	cond.notify_one();
}

template <class T>
void SyncList<T>::pop_back(T& value)
{
	unique_lock<mutex> lck(mtx);
	cond.wait_for(lck, std::chrono::milliseconds(100), [this] {
		return vec.size() >= low_mark;
	});
	// lck.unlock();
	value = vec.back();
	cout << "Pop back " << value << endl;
	vec.pop_back();
	cond.notify_one();
}

template <class T>
void SyncList<T>::push_front(const T& value)
{
	unique_lock<mutex> lck(mtx);
	cond.wait_for(lck, std::chrono::milliseconds(100), [this] {
		return vec.size() <= high_mark;
	});
	cout << "Push front " << value << endl;
	vec.insert(vec.begin(), value);
	cond.notify_one();
}

template <class T>
void SyncList<T>::pop_front(T& value)
{
	unique_lock<mutex> lck(mtx);
	cond.wait_for(lck, std::chrono::milliseconds(100), [this] {
		return vec.size() >= low_mark;
	});
	// lck.unlock();
	value = vec.front();
	cout << "Pop front " << value << endl;
	vec.erase(vec.begin());
	cond.notify_one();
}

#endif