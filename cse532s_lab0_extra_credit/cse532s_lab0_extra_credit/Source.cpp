#include <thread>
#include "play.h"
using namespace std;

typedef map<int, thread> threadDic;

int play::lineIndex = 0;

void fetcher(play& p, ifstream& in) {
	string currentName;
	getline(in, currentName);
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
		os << fileName << " " << fileName.append(".txt") << endl;
		cName.pop();
	}
}

void print(play& p, string& s, ofstream& os) {
	line::iterator it = p.getIterator(s);
	line::iterator itEnd = p.getEndIterator(s);
	while (it != itEnd) {
		os << it->first << " " << it->second << endl;
		it++;
	}
}

int main(int argc, char *argv[]) {
	string prefix = "play/";

	if (argc > 3) {
		string infile = argv[1];
		string configFile = argv[2];
		string playName = argv[3];
		for (int i = 4; i < argc; i++) {
			playName.append(" ");
			playName.append(argv[i]);
		}

		play show(playName);
		ifstream in;
		ofstream os;
		infile.insert(0, prefix);
		configFile.insert(0, prefix);
		in.open(infile);
		os.open(configFile);

		fetcher(show, in);
		config(show, os);

		//start to print
		threadDic td;
		character cName = show.getKey();
		for (int i = 0; i < show.getContextSize(); i++) {
			ofstream temp;
			string outputFile = "play/";
			outputFile.append(cName.front()).append(".txt");
			temp.open(outputFile);
			td[i] = thread(print, ref(show), ref(cName.front()), ref(temp));
			td[i].join();
			cName.pop();
		}
		
	}
	else {
		cout << "Please use correct command <filename> <configfile_name> <play_name>" << endl;
	}

	return 0;
}

