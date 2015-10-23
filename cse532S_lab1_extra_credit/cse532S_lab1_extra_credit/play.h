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
//major container to store the lines
typedef pair<string, part> singleLine;
//container to store the information of characters
typedef queue<string> character;

class play {
private:
	string playName;
	script context;
	static int lineIndex;
public:
	static int getIndex();
	play(string s);
	//insertion overload
	play& operator << (singleLine& s);
	const string& getName();
	const character getKey();
	const int getContextSize();
	line::iterator getIterator(string& s);
	line::iterator getEndIterator(string& s);
};


#endif
