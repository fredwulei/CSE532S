#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <thread>
#include "play.h"
#include "SafeThread.h"

using namespace std;

mutex play::lock;

// function called by threads to read in each character's lines
void fetcher(play& p, const string& character, ifstream& in) {
	string currentLine;
	while (getline(in, currentLine)) {
		// determien whether we should escape this line
		if (currentLine.size() >= 3) {
			istringstream iss(currentLine);
			int index = 0;
			iss >> index;
			string whiteSpace;
			// dealing with multiple whitespaces
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

	// make sure the input command is correct
	if (argc > 1) {
		string configPath = argv[1];
		ifstream config(configPath);
		string currentLine;
		bool findingName = true;
		// while loop to store the important information
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

		// initial the whole play using name
		play show(playName);

		for (int i = 1; i <= characterCount; i++) {
			ifstream tempIn;
			tempIn.open(information.front().second);
			if (tempIn.is_open()){
				string characterName = information.front().first;
				SafeThread(thread(fetcher, ref(show), ref(information.front().first), ref(tempIn)));
				information.pop();
			}
			else{
				cout << "please check the config file, can not open " << information.front().second << endl;
				system("pause");
				return -1;
			}
		}

		// print out all the lines
		show.print(cout);
		
	}
	else {
		cout << "usage: " << argv[0] << "<configuration_file_name>" << endl;
	}

	system("pause");

	return 0;
}

