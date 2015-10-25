#ifndef PLAYER_H
#define PLAYER_H

#include "Play.h"

class Player
{
public:
	//Player() : infile(ifstream()), play(Play()) {}
	Player(Play& p) :play(p) {}
	void read();
	void act();
	void enter();
	void exit();
private:
	Line lines;
	Play& play;
	thread t;
};

#endif

