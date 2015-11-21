#include <thread>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;


typedef pair<string, string> config; //actorName scriptFileName
typedef set<config> configSet;
typedef map<string, configSet> whole;
typedef pair<int, string> line;
typedef vector<line> script;
typedef map<string, script> container;

//Enumeration for return type of main function
enum {
    SUCCESS = 0,
    FAIL_WRONG_ARGUMENTS,
    FAIL_FILE_OPEN_MAIN_SCRIPT,
    FAIL_FILE_OPEN_CONFIG,
    FAIL_FILE_OPEN_OUTPUT
};

void fetcher(ifstream& in, string& baseName, string& sceneName, whole& w, container& myContainer) {
    char partIndex = 'a';
    getline(in, sceneName);
    string currentLine;
    bool isLastLineEmpty = false;
    bool isLastLineEnterOrExit = false;
    
	// set of players on stage
    set<string> onStageActor;    
    
    string currentScriptFileName;
    int currentLineNumber = 1;
    
    while (getline(in, currentLine)) {
        if (currentLine.size() == 0) {            
            if(isLastLineEnterOrExit){
                // generate config file and script files
                currentLineNumber = 1;            
                
                configSet cs;
                for (string actorName : onStageActor){
                    string scriptFileName = actorName + "_" + baseName + partIndex;
                    cs.insert(config(actorName, scriptFileName));
                }

                string configFileName = baseName + partIndex + "_config";
                w[configFileName] = cs;
                partIndex++;
            }
            
            isLastLineEmpty = true;
            isLastLineEnterOrExit = false;
        }
        else {
            regex re1("^\\[(Enter|Exit) (\\S+)\\.\\]$");
            smatch sm;
            regex_match(currentLine, sm, re1);
            if (sm.size() > 0) {
                string status = sm[1];
                if (status.compare("Enter") == 0){
                    onStageActor.insert(sm[2]);
                }else{
                    onStageActor.erase(sm[2]);
                }
                isLastLineEnterOrExit = true;
                isLastLineEmpty = false;
                continue;
            }           
            
            if (isLastLineEmpty){
                regex re3("^(\\w+).*$");
                regex_match(currentLine, sm, re3);
                if (sm.size() > 0) {
                    string s = sm[1];
                    char ind = partIndex - 1;
                    currentScriptFileName =  s + "_" + baseName + ind;
                    isLastLineEnterOrExit = false;
                    isLastLineEmpty = false;
                    continue;
                }               
            }else{
                line l(currentLineNumber, currentLine);
                myContainer[currentScriptFileName].push_back(l);
                currentLineNumber ++;
                isLastLineEnterOrExit = false;
                isLastLineEmpty = false;
            }           
        }
    }   
}

// print part files
void print(script& s, ofstream& os) {
    for (auto j : s){
        os << j.first << " " << j.second << endl;
    }    
    os.close();
}

// print corresponding script files
void printWhole(const whole& w, const string& baseName, const string& sceneName, ofstream& os){
    os << "[scene] " << sceneName << endl;
    for (auto s : w){
        os << s.first << ".txt" << endl;
    }   
    os.close();
}

// print fragment configuration 
void printConf(const configSet& cs, ofstream& os){
    for (config conf : cs){
        os << conf.first << " " << conf.second << ".txt" << endl;
    }    
    os.close();
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
		cerr << "[ERROR]: missing arguments" << endl;
		return FAIL_WRONG_ARGUMENTS;
    }
    
    string infile(argv[1]);    
    ifstream in(infile);
    
    string baseName = infile.substr(0, infile.find_last_of("."));   
    
    whole w;
    container myContainer;
    string sceneName;
    
    if (in.is_open()) {
        fetcher(in, baseName, sceneName, w, myContainer);
    }
    else {
        cerr << "[ERROR]: can not open main script : " << infile << endl;
        return FAIL_FILE_OPEN_MAIN_SCRIPT;
    }
        
    for(auto f : myContainer){
        ofstream temp;
        string outputFile = f.first + ".txt";
        temp.open(outputFile);
        if (temp.is_open()) {
			print(f.second, temp);
        }
        else {
            cerr << "[ERROR]: can not open outputfile : " << outputFile << endl;
            return FAIL_FILE_OPEN_OUTPUT;
        }
    }    
    
    ofstream temp;
    string wholeFileName = "partial_"+ baseName + "_script.txt";
    temp.open(wholeFileName);
    if (temp.is_open()) {
        printWhole(w, baseName, sceneName, temp);
    }
    else {
        cerr << "[ERROR]: can not open outputfile : " << wholeFileName << endl;
        return FAIL_FILE_OPEN_OUTPUT;
    }
    
    
    for (auto f : w){
        ofstream confStream;
        string confOutputFile = f.first + ".txt";
        confStream.open(confOutputFile);
        if (confStream.is_open()) {
			printConf(f.second, confStream);
        }
        else {
            cerr << "[ERROR]: can not open outputfile : " << confOutputFile << endl;
            return FAIL_FILE_OPEN_OUTPUT;
        }
    }
        
    return SUCCESS;
}

