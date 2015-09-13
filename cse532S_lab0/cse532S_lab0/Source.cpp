#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <thread>
#include "play.h"

using namespace std;

mutex play::lock;

void fetcher(play& p, const string& character, ifstream& in) {
	string currentLine;
	while (getline(in, currentLine)) {
		if (currentLine.size() >= 3) {
			istringstream iss(currentLine);
			int index = 0;
			iss >> index;
			string whiteSpace;
			do {
				whiteSpace = iss.get();
			} while (whiteSpace == " ");
			string rest;
			getline(iss, rest);
			string restLine = whiteSpace.append(rest);

			//now we have got index, character's name and line
			line current(index, part(character, restLine));
			p << current;
		}
	}
}

int main(int argc, char* argv[]) {
	string playName;
	queue<part> information;
	int characterCount = 0;

	if (argc > 1) {
		string configPath = argv[1];
		ifstream config(configPath);
		string currentLine;
		bool findingName = true;
		while (getline(config, currentLine)) {
			if (currentLine.size() > 0) {
				if(findingName){
					playName = currentLine;
					findingName = false;
				}
				else {
					istringstream iss(currentLine);
					string character, path;
					iss >> character >> path;
					part temp(character, path);
					information.push(temp);
					characterCount++;
				}
			}
		}

		play show(playName);

		map<int,thread> threadDic;
		for (int i = 1; i <= characterCount; i++) {
			ifstream tempIn;
			string prefix = "play/";
			tempIn.open(prefix.append(information.front().second));
			string characterName = information.front().first;
			threadDic[i] = thread(fetcher, ref(show), ref(information.front().first), ref(tempIn));
			threadDic[i].join();
			information.pop();
		}



		show.print(cout);
	}
	else {
		cout << "usage: " << argv[0] << "<configuration_file_name>" << endl;
	}

	return 0;
}

