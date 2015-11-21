#include "SyncWrapper.h"



SyncWrapper::SyncWrapper()
{
}


SyncWrapper::~SyncWrapper()
{
}

void SyncWrapper::print(const string & str)
{
	lock_guard<mutex> lock(m);
	ostr << str;
}
