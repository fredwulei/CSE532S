#include "Director.h"

Director::Director(string scriptName, unsigned int playerCount)
{
	maximum = 0;
	ifstream infile(scriptName);
	if (!infile.is_open()) {
		string error = "[ERROR]:  Open file fail: " + scriptName;
		throw exception(error.c_str());
	}
	string currentLine;
	bool followingPL;
	int scriptCounter = 1;
	while (getline(infile, currentLine)) {
		regex re("^\\[scene\\][\\s]([\\w\\s]*)$");
		smatch sm;
		if (regex_match(currentLine, sm, re)) {
			titles.push_back(sm[1]);
			followingPL = false;
		}
		else {
			regex re_config("^[\\s]*(.*.txt)[\\s]*$");
			smatch sm_config;
			if (regex_match(currentLine, sm_config, re_config)) {
				scripts[scriptCounter] = script();

				if (!followingPL) {
					followingPL = true;
				}
				else {
					titles.push_back(string());
				}
				ifstream configFile(sm_config[1]);
				int partDefinitionLineCount = 0;
				if (!configFile.is_open()) {
					string temp = sm_config[1];
					string error = "[ERROR]:  Open file fail: " + temp;
					throw exception(error.c_str());
				}
				string partDefinitionLine;
				regex re_part("^[\\s]*([\\w]+)[\\s]+(.*.txt)[\\s]*$");
				while (getline(configFile, partDefinitionLine)) {
					smatch sm_part;
					if (regex_match(partDefinitionLine, sm_part, re_part)) {
						partDefinitionLineCount++;
						scripts[scriptCounter][sm_part[1]] = sm_part[2];
					}
				}

				scriptCounter++;
				maximum = maximum > partDefinitionLineCount ? maximum : partDefinitionLineCount;
			}
		}
	}

	//finish reading script
	//#############remeber check whether null or not
	play = playPtr(new(nothrow) Play(titles, finished.get_future()));
	maximum = maximum > (int)playerCount ? maximum : (int)playerCount;
	for (int i = 0; i < maximum; i++) {
		players.push_back(playerPtr(new(nothrow) Player(*play)));
		players[i]->activate();
	}
}

void Director::cue()
{
	thread temp = thread([&] {
		scriptsIter iter = scripts.begin();
		while (iter != scripts.end()) {
			sIter sIt = iter->second.begin();
			while (sIt != iter->second.end()) {
				play->checkAvailable(maximum);
				for (int i = 0; i < maximum; i++) {
					if (!players[i]->isbusy()) {
						players[i]->enter(iter->first,sIt->first,sIt->second);
						break;
					} 
				}
				sIt++;
			}
			iter++;
		}
		
		finished.set_value(true);
		for (int i = 0; i < maximum; i++) {
			players[i]->join();
		}
		
	});

	temp.join();
}
