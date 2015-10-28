#include "Player.h"

mutex mmm;

void Player::read(string name, string script)
{
	ifstream infile(script);
	string currentLine;
	//Using regular expression to check the data for each line
	regex re("^\\s*(\\d+)\\s*([^\\d\\s].*?)\\s*$");
	while (getline(infile, currentLine)) {
		smatch sm;
		regex_match(currentLine, sm, re);
		if (sm.size() > 0) {
			//Once the line match the RE, come in this if condition and insert data
			lines[stoi(sm[1])] = SingleLine(name, sm[2]);
		}
	}
}

void Player::act()
{
	/*while (isActive) {
		if (!lines.empty() && retrieving == false) {
			if (iter != lines.end()) {
				play.recite(iter, sceneCount);
			}
			else {
				exit();
			}
		}
		else {
			cout << "sleep :  " << sceneCount << index << endl;
			this_thread::sleep_for(chrono::seconds(2));
		}
	}*/

	while (isActive) {
		if (!lines.empty() && retrieving == false) {
			if (iter != lines.end()) {
				play.recite(iter, sceneCount);
				iter++;
			}
			else {
				exit();
			}
			
		}
	}
}

void Player::enter(int sceneCounter, string name, string script)
{

	play.enter(sceneCounter);
	busy = true;
	retrieving = true;
	sceneCount = sceneCounter;
	read(name, script);
	iter = lines.begin();
	retrieving = false;
}

void Player::exit()
{
	auto temp = lines.begin()->second.first;
	lines.clear();
	busy = false;
	play.exit();

	if (play.checkPlayFinished()) {
		unique_lock<mutex> lock(mmm);
		lock.unlock();
		deactive();
	}
}

bool Player::isbusy()
{
	return busy;
}

void Player::activate()
{
	if (!isActive) {
		isActive = true;
		this->t = thread(&Player::act, this);
	}
}

void Player::deactive()
{
	if (isActive) {
		isActive = false;
	}
	//t.join();
}

void Player::join()
{
	if (t.joinable()) {
		t.join();
	}
}
