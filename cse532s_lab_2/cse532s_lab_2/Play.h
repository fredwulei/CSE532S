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
	//Play() : on_stage(0), line_counter(1), scene_fragment_counter(0), firstLine(true) {}
	Play(sceneTitles& ref) :sceneRef(ref), on_stage(0), line_counter(1), scene_fragment_counter(0), firstLine(true) {
		iter = sceneRef.begin();
		if (!ref.empty()) {
			cout << *iter << endl;
			iter++;
		}
	}
	void recite(LineIter& iter, int sceneCount);
	void enter(int sceneCount);
	void exit();
private:
	int line_counter;
	int scene_fragment_counter;
	int on_stage;
	//#######################################
	// should refresh as true after each fragment
	//The boolean value used to determine whether it's firstLine right now
	bool firstLine;

	mutex m;
	condition_variable cv;
	condition_variable cv_enter;
	// #######################################
	// should refresh as "" afer each single fragment
	string currentCharacter;
	sceneTitles& sceneRef;
	sceneCountIter iter;
};

#endif PLAY_H

