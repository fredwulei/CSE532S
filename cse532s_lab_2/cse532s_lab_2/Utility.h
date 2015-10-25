#ifndef H_UTILITY
#define H_UTILITY

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <regex>
#include <memory>
#include "SafeThread.h"

using namespace std;

//######################################
//put these where they belong
typedef vector<string> sceneTitles;
typedef sceneTitles::iterator sceneCountIter;
typedef pair<string, string> SingleLine;
typedef map<int, pair<string, string>> Line;
typedef Line::iterator LineIter; 

//Enumeration for return type of main function
enum {
	SUCCESS = 0,
	FAIL_WRONG_ARGUMENTS = 1,
	FAIL_FILE_OPEN = 2
};

#endif