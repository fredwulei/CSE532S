#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>
#include "Play.h"
#include "pline.h"

using namespace std;

void readPlay(Play& p, const string& name, ifstream& is) {
	/* For debugging
	cout << name << endl;
	cout << (is.is_open() ? "File opened" : "File not opened") << endl;
	//*/
	
	if (is.is_open()) {
		string line;	

		while (getline(is, line)) {
			string::size_type sz;

			int line_num = stoi(line, &sz);
			string s = line.substr(sz);
			printf("%d  %s\n", line_num, s.c_str());

			vector<string> svec;
			svec.push_back(name);
			svec.push_back(line.substr(sz));

			pline pl;
			pl[line_num] = svec;

			p << pl;			
		}

//	is.close();
	}
}

void test(int& i) {
	printf("%d\n", i);
}


int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "usage: " << argv[0] << " <configuration_file_name>" << endl;
		return 1;
	}

	unsigned int cores = thread::hardware_concurrency();
	cout << "Hardware concurrency: " << cores << endl;

	string config_file = string(argv[1]);
	size_t ind = config_file.find_last_of("/\\");
	string path = config_file.substr(0, ind+1);

	ifstream infile(argv[1]);
	
	int num_of_characters = 0;
	string play_name;
		
	vector<vector<string>> namelist;

	if (infile.is_open()) {		
		getline(infile, play_name);
		string line;
		while (getline(infile, line)) {
			++num_of_characters;
			stringstream ss(line);
			string token;
			char delim = ' ';
			vector<string> names;
			while (getline(ss, token, delim)) {
				names.push_back(token);
			}
			names[1] = path + names[1];
			namelist.push_back(names);
		}
		infile.close();
	}	
	
	Play p(play_name);

	// readPlay(p, namelist[0][0], ifstream(namelist[0][1]));

	vector<thread> threads;
	vector<ifstream> iss;

	/*
	int i = 3;
	ifstream file(namelist[i][1]);
	thread t(readPlay, ref(p), ref(namelist[i][0]), ref(file));

	t.join();

	p.print(cout);

	//*/


	//*
	for (int i = 0; i < num_of_characters; i++) {
		ifstream ifs(namelist[i][1]);
		string name = namelist[i][0];
		threads.push_back(thread(readPlay, ref(p), ref(name), ref(ifs)));
	}

	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

	
	//*/

	
	
	return 0;
}