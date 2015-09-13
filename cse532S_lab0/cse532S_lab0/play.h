#ifndef FILE_H
#define FILE_H

#include <map>
#include <string>
#include <mutex>

using namespace std;

// some predefined data type
// ( index, (character name, line) )
typedef map<int, pair<string, string>> context;;
typedef pair<int, pair<string, string>> line;
typedef pair<string, string> part;

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
	context& operator << (const pair<int, pair<string, string>>& l);
	void print(ostream& os);
};


#endif
