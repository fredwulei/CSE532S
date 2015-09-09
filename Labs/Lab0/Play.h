#ifndef PLAY_H
#define PLAY_H

#include <ostream>
#include <mutex>
#include "pline.h"

using namespace std;

class Play {

public:
	Play(string s);
	void print(ostream& os);
	Play& operator<<(const pline& p);

	string getName();
private:
	mutex _m;
	string _name;
	pline _line;
};


#endif