#ifndef SAFESTHREAD_H
#define SAFESTHREAD_H

#include <thread>

class SafeThread {
	std::thread& _t;

public:
	explicit SafeThread(std::thread& t) :_t(t){}
	~SafeThread()
	{
		//RAII, deconstructor to join
		if (_t.joinable()){
			_t.join();
		}
	}

	SafeThread(SafeThread const&) = delete;
	SafeThread& operator= (SafeThread&) = delete;
};

#endif