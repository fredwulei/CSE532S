#ifndef PLAY_H
#define PLAY_H

#include <sstream>
#include <mutex>
#include <condition_variable>
#include <exception>
#include "Utility.h"


class Play
{
public:
	Play(sceneTitles& ref,endFuture&& fut) :sceneRef(ref), on_stage(0), waiting(0), line_counter(1), scene_fragment_counter(1), firstLine(true) {
		iter = sceneRef.begin();
		if (!ref.empty()) {
			cout << *iter << endl;
			iter++;
		}
		finishFlag = move(fut);
	}
	void recite(LineIter& iter, int sceneCount);
	void enter(int sceneCount);
	void exit();
	void checkAvailable(int max);
	bool checkPlayFinished();
private:
	int line_counter;
	int scene_fragment_counter;
	int on_stage;
	int waiting;
	//#######################################
	// should refresh as true after each fragment
	//The boolean value used to determine whether it's firstLine right now
	bool firstLine;

	endFuture finishFlag;

	mutex m;
	mutex m_enter;
	mutex m_check;
	condition_variable cv;
	condition_variable cv_enter;
	condition_variable cv_cue;
	// #######################################
	// should refresh as "" afer each single fragment
	string currentCharacter;
	sceneTitles& sceneRef;
	sceneCountIter iter;

	//reset current character and first line variables
	void resetCCandFL();
};

#endif PLAY_H

