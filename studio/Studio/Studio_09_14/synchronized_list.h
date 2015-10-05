#ifndef SYNCHRONIZED_LIST_H
#define SYNCHRONIZED_LIST_H

#include <iostream> 
#include <vector>
#include <mutex>


using namespace std;

template <class T>
class SyncList {
public:
	SyncList() :low_mark(0), high_mark(1), hasShutDown(false) {};
	SyncList(size_t l, size_t h) :
		low_mark(l), high_mark(h), hasShutDown(false) {
		if (low_mark < 0)   low_mark = 0;
		if (high_mark <= 0) high_mark = 1;
	};
	SyncList(const SyncList&);
	void push_back(const T&);
	void pop_back(T&);
	void push_front(const T&);
	void pop_front(T&);
	bool empty() const;
	void shut_down();
	void reset();
private:
	bool hasShutDown;
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

	cond.wait(lck, [this] {
		return vec.size() <= high_mark;
	});
	cout << "Push back " << value << endl;
	vec.push_back(value);
	cond.notify_one();
}

template <class T>
void SyncList<T>::pop_back(T& value)
{
	if (!hasShutDown) {
		unique_lock<mutex> lck(mtx);
		cond.wait(lck, [this] {
			return vec.size() >= low_mark;
		});
		// lck.unlock();
		value = vec.back();
		vec.pop_back();
		cout << "Pop back " << value << " from " << this << endl;
		//" Size of list is: " << vec.size() << endl; // " is shut_down: " << (hasShutDown ? "Yes" : "No") << endl;
		cond.notify_one();
	}
}

template <class T>
void SyncList<T>::push_front(const T& value)
{
	unique_lock<mutex> lck(mtx);
	cond.wait(lck, [this] {
		return vec.size() <= high_mark;
	});
	cout << "Push front " << value << " in " << this << endl;
	vec.insert(vec.begin(), value);
	cond.notify_one();
}

template <class T>
void SyncList<T>::pop_front(T& value)
{
	unique_lock<mutex> lck(mtx);
	cond.wait(lck, [this] {
		return vec.size() >= low_mark;
	});
	// lck.unlock();
	value = vec.front();
	cout << "Pop front " << value << endl;
	vec.erase(vec.begin());
	cond.notify_one();
}

template <class T>
bool SyncList<T>::empty() const {
	lock_guard<mutex> lck(mtx);
	return vec.empty();
}

template <class T>
void SyncList<T>::shut_down() {
	{
		lock_guard<mutex> lck(mtx);
		hasShutDown = true;
		cond.notify_all();
	}
	// hasShutDown = false;
}

template <class T>
void SyncList<T>::reset() {
	lock_guard<mutex> lck(mtx);
	hasShutDown = false;
}

#endif