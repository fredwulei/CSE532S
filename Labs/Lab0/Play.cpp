#include "Play.h"

Play::Play(string s):_name(s=string()), _line(pline()) {}

string Play::getName() {
	return _name;
}

void Play::print(ostream& os) {
	for (auto const &line : _line) {
		os << line.second[1] << endl;
	}
}

Play& Play::operator<<(const pline& pl) {
	lock_guard<mutex> guard(_m);
	_line.insert(pl.begin(), pl.end());
	return *this;
}

