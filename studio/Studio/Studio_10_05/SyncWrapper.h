#ifndef SYNCWRAPPER_H
#define SYNCWRAPPER_H

#include <iostream>
#include <mutex>
#include <string>

using namespace std;

class SyncWrapper
{
public:
	SyncWrapper(ostream& o) :ostr(o) {}
	~SyncWrapper();
private:
	ostream& ostr;
	mutex m;
	void print(const string&);
};


#endif
