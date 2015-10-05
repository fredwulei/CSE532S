#ifndef SAFESTHREAD_H
#define SAFESTHREAD_H

#include <thread>
#include <iostream>

class SafeThread {
	// std::thread& _t;
	std::thread _t;

public:
	/*
	SafeThread();
	SafeThread(std::thread& t) :_t(t) {}
//  explicit SafeThread(std::thread& t) :_t(t) {}

	~SafeThread()
	{
		if (_t.joinable()){
			_t.join();
		}
	}


	SafeThread& operator= (SafeThread &&rhs)
	{
		if (this != &rhs) {
			_t = move(rhs._t);
		}
		return *this;
	}

	// SafeThread(SafeThread const&) = delete;
	// SafeThread& operator= (SafeThread&) = delete;
	*/

	SafeThread();
	SafeThread(std::thread t) :_t(move(t)) {
		if (!_t.joinable()) {
			std::cout << "Error" << std::endl;
		}
	}
	//  explicit SafeThread(std::thread& t) :_t(t) {}

	~SafeThread()
	{
		std::cout << "Here" << std::endl;
		_t.join();
	}


	SafeThread& operator= (SafeThread &&rhs)
	{
		if (this != &rhs) {
			_t = move(rhs._t);
		}
		return *this;
	}
};

#endif