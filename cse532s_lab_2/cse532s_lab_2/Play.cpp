#include "Play.h"

void Play::recite(LineIter & iter, int sceneCount)
{
	unique_lock<mutex> lock(m);
	cv.wait(lock, [&] {
		if (sceneCount == scene_fragment_counter && iter->first == line_counter) {
			return true;
		}
		else if (scene_fragment_counter < sceneCount || (sceneCount == scene_fragment_counter && iter->first > line_counter)) {
			return false;
		}
		else {
			//to be finished
			cerr << "[ERROR]:  ##################################################" << endl;
			iter++;
			cv.notify_all();
			if (iter->first == line_counter){
				return true;
			}
			else{
				return false;
			}
		}
	});
	if (firstLine) {
		currentCharacter = iter->second.first;
		cout << iter->second.first << "." << endl;
		firstLine = false;
	}
	else {
		if (currentCharacter != iter->second.first) {
			cout << endl << iter->second.first << "." << endl;
			currentCharacter = iter->second.first;
		}
	}
	
	cout << iter->second.second << endl;
	
	line_counter++;
	//The notify_all can be done after unlock
	lock.unlock();
	cv.notify_all();
}

void Play::enter(int sceneCount)
{
	if (sceneCount < scene_fragment_counter) {
		throw exception("[ERROR]: scene counter less than current counter");
	}
	else if (sceneCount == scene_fragment_counter) {
		on_stage++;
	}
	else {
		// the same lock??????????????????????????????????
		// a new condition variable???????????????????????
		// for high concurrency. 
		unique_lock<mutex> lock(m_enter);
		waiting++;
		cv_enter.wait(lock, [&] {
			return (sceneCount == scene_fragment_counter);
		});
		waiting--;
		on_stage++;
	}
}

void Play::exit()
{
	if (on_stage > 1) {
		on_stage--;
		cv_cue.notify_all();
	}
	else if (on_stage < 1) {
		throw exception("[ERROR]: lower bound of on stage exceed");
	}
	else {
		on_stage--;
		cv_cue.notify_all();
		resetCCandFL();
		scene_fragment_counter++;
		line_counter = 1;
		if (iter != sceneRef.end()) {
			if (!iter->empty()) {
				cout << *iter << endl;
			}
			iter++;
		}
		cv_enter.notify_all();
	}
}

void Play::checkAvailable(int max)
{
	unique_lock<mutex> lock(m_check);
	cv_cue.wait(lock, [&] {
		return (on_stage + waiting) < max;
	});
}

bool Play::checkPlayFinished()
{
	return finishFlag._Is_ready();
}

void Play::resetCCandFL()
{
	firstLine = true;
	currentCharacter = string();
}


