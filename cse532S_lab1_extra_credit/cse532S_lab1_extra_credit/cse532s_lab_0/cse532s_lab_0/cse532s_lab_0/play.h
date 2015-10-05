#ifndef FILE_H
#define FILE_H

#include <map>
#include <string>
#include <mutex>

using namespace std;

// some predefined data type
// ( index, (character name, line) )
typedef pair<string, string> part;
typedef pair<int,part> line;
typedef map<int, part> context;

class play {
private:
	string playName;
	context content;
	// static lock!!!
	static mutex lock;
	// using the Thread safe interface pattern
	void inner_print(ostream& os);
public:
	play(string s);
	context& operator << (const pair<int, part>& l);
	void print(ostream& os);
};


#endif
