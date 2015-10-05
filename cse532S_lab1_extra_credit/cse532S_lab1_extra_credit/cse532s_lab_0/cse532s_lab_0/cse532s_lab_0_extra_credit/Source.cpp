#include <thread>
#include "play.h"
#include "SafeThread.h"

using namespace std;

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

void print(play& p, string& s, ofstream& os) {
	line::iterator it = p.getIterator(s);
	line::iterator itEnd = p.getEndIterator(s);
	while (it != itEnd) {
		os << it->first << " " << it->second << endl;
		it++;
	}
}

int main(int argc, char *argv[]) {
	//string prefix = "play/";

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
		//infile.insert(0, prefix);
		//configFile.insert(0, prefix);
		in.open(infile);
		os.open(configFile);
		
		if (in.is_open()){
			fetcher(show, in);
		}
		else{
			cout << "can not open main script : " << infile << endl;
			system("pause");
			return -1;
		}
		
		if (os.is_open()){
			config(show, os);
		}
		else{
			cout << "can not open output script : " << configFile << endl;
			system("pause");
			return -2;
		}
		

		//start to print
		character cName = show.getKey();
		for (int i = 0; i < show.getContextSize(); i++) {
			ofstream temp;
			string outputFile = cName.front();
			outputFile.append(".txt");
			temp.open(outputFile);
			if (temp.is_open()){
				SafeThread(thread(print, ref(show), ref(cName.front()), ref(temp)));
				cName.pop();
			}
			else{
				cout << "can not open outputfile : " << outputFile << endl;
				system("pause");
				return -3;
			}
			
		}
		
	}
	else {
		cout << "Please use correct command <filename> <configfile_name> <play_name>" << endl;
	}

	system("pause");

	return 0;
}

