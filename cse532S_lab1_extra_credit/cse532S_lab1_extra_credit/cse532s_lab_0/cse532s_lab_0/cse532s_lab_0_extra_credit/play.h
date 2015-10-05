#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <queue>
#include <iterator>

using namespace std;

typedef pair<int, string> part;
typedef map<int, string> line;
typedef map<string, line> script;
typedef pair<string, part> singleLine;
typedef queue<string> character;

class play {
private:
	string playName;
	script context;
	static int lineIndex;
public:
	static int getIndex();
	play(string s);
	play& operator << (singleLine& s);
	const string& getName();
	const character getKey();
	const int getContextSize();
	line::iterator getIterator(string& s);
	line::iterator getEndIterator(string& s);
};


#endif
