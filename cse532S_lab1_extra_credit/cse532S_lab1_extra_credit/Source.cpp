#include <thread>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

#include "play.h"
#include "SafeThread.h"

using namespace std;

//Enumeration for return type of main function
enum {
	SUCCESS = 0,
	FAIL_WRONG_ARGUMENTS = 1,
	FAIL_FILE_OPEN_MAIN_SCRIPT = 2,
	FAIL_FILE_OPEN_CONFIG = 3,
	FAIL_FILE_OPEN_OUTPUT =4
};

int play::lineIndex = 0;

void fetcher(play& p, ifstream& in) {
	string currentName;
	getline(in, currentName);
	// because the script contains a . in the end of each character's name
	size_t found = currentName.find_last_of(".");
	currentName =  currentName.substr(0, found);
	string currentLine;
	while (getline(in, currentLine)) {
		if (currentLine.size() != 0) {
			singleLine s(currentName, part(play::getIndex(), currentLine));
			p << s;
		}
		else {
			getline(in, currentName);
			found = currentName.find_last_of(".");
			currentName = currentName.substr(0, found);
		}
	}

}

void config(play& p, ofstream& os) {
	os << p.getName() << endl;
	character cName = p.getKey();
	while (!cName.empty()) {
		string fileName = cName.front();
		os << fileName << " " << fileName << ".txt" << endl;
		cName.pop();
	}
}

void print(play& p, string& s, ofstream& os, bool random) {
	line::iterator it = p.getIterator(s);
	line::iterator itEnd = p.getEndIterator(s);

	if (random) {
		srand(unsigned(time(0)));
		vector<string> line;
		while (it != itEnd) {			
			string l = to_string(it->first) + " " + it->second + "\n";
			line.emplace_back(l);
			it++;
		}

		random_shuffle(line.begin(), line.end());

		for (auto l : line) {
			os << l;
		}
	}
	else {
		while (it != itEnd) {
			os << it->first << " " << it->second << endl;
			it++;
		}
	}	
}

int main(int argc, char *argv[]) {

	bool isScramble = false;
	char *scramble = "scramble";

	if (argc < 3) {
		cerr << "Please use correct command [scramble] <filename> <configfile_name> <play_name>" << endl;
		return FAIL_WRONG_ARGUMENTS;
	}

	string infile;
	string configFile;
	string playName;

	if (_stricmp(scramble, argv[1]) == 0) {
		isScramble = true;
		infile = argv[2];
		configFile = argv[3];
		playName = argv[4];
		for (int i = 5; i < argc; i++) {
			playName.append(" ");
			playName.append(argv[i]);
		}
	}
	else {
		infile = argv[1];
		configFile = argv[2];
		playName = argv[3];
		for (int i = 4; i < argc; i++) {
			playName.append(" ");
			playName.append(argv[i]);
		}
	}
	
	cout << infile << endl;


	play show(playName);
	ifstream in;
	ofstream os;
	in.open(infile);
	os.open(configFile);

	if (in.is_open()) {
		fetcher(show, in);
	}
	else {
		cerr << "can not open main script : " << infile << endl;
		return FAIL_FILE_OPEN_MAIN_SCRIPT;
	}

	if (os.is_open()) {
		config(show, os);
	}
	else {
		cerr << "can not open output script : " << configFile << endl;
		return FAIL_FILE_OPEN_CONFIG;
	}

	//start to print
	character cName = show.getKey();
	for (int i = 0; i < show.getContextSize(); i++) {
		ofstream temp;
		string outputFile = cName.front();
		outputFile.append(".txt");
		temp.open(outputFile);
		if (temp.is_open()) {
			SafeThread(thread(print, ref(show), ref(cName.front()), ref(temp), isScramble));
			cName.pop();
		}
		else {
			cerr << "can not open outputfile : " << outputFile << endl;
			return FAIL_FILE_OPEN_OUTPUT;
		}

	}

	return SUCCESS;
}

