#ifndef SYNCHRONIZED_LIST_H
#define SYNCHRONIZED_LIST_H

#include <iostream> 
#include <vector>

using namespace std;

template <class T>
class SyncList {
public:
	SyncList() {};
	void push_back(const T&);
	T pop_back();
	void push_front(const T&);
	T pop_front();
private:
	vector<T> vec;
};

template <class T>
void SyncList<T>::push_back(const T& value)
{
	cout << "Push back " << value << endl;
	vec.push_back(value);
}

template <class T>
T SyncList<T>::pop_back()
{
	T value = vec.back();
	cout << "Pop back " << value << endl;
	vec.pop_back();
	return value;
}

template <class T>
void SyncList<T>::push_front(const T& value)
{
	cout << "Push front " << value << endl;
	vec.insert(vec.begin(), value);
}

template <class T>
T SyncList<T>::pop_front()
{
	T value = vec.front();
	cout << "Pop front " << value << endl;
	vec.erase(vec.begin());
	return value;
}

#endif