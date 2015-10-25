#ifndef H_DIRECTOR
#define H_DIRECTOR

#include "Utility.h"
#include "Play.h"
#include "Player.h"

typedef shared_ptr<Play> playPtr;
typedef shared_ptr<Player> playerPtr;
typedef vector<shared_ptr<Player>> playerContainer;

//data structure to store the script information
typedef map<string, string> script;
typedef map<int, script> scriptsContainer;
typedef scriptsContainer::iterator scriptsIter;


class Director
{
public:
	Director(string scriptName, unsigned int playerCount = 0) :maximum(0) {}
	void cue();
private:
	int maximum;

	sceneTitles titles;
	scriptsContainer scripts;
	playPtr play;
	playerContainer players;
};

#endif