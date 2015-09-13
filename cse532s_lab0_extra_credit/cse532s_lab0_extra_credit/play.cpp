#include "play.h"

int play::getIndex()
{
	lineIndex++;
	return play::lineIndex;
}

play::play(string s)
{
	playName = s;
}

play & play::operator<<(singleLine & s)
{
	if (context.count(s.first) > 0) {
		context[s.first].insert(s.second);
	}
	else {
		line temp;
		temp.insert(s.second);
		context[s.first] = temp;
	}

	return *this;
}

const string & play::getName()
{
	return playName;
}

const character play::getKey()
{
	character temp;
	script::iterator it = context.begin();
	while (it != context.end()) {
		temp.push(it->first);
		it++;
	}
	return temp;
}

const int play::getContextSize()
{
	return context.size();
}

line::iterator play::getIterator(string & s)
{
	return context[s].begin();
}

line::iterator play::getEndIterator(string & s)
{
	return context[s].end();
}
