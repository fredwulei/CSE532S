#include <sstream>
#include "Director.h"

int main(int argc, char* argv[]) {

	if (argc < 2 || argc > 4) {
		//Check for the command line usage
		cerr << "[ERROR]:  usage: " << argv[0] << "<script_file_name> <optional: minimum_player>" << endl;
		return FAIL_WRONG_ARGUMENTS;
	}

	try {
		if (argc == 2) {
			Director dic(argv[1]);
			dic.cue();
			auto fut = dic.getResult();
			try {
				fut.get();
			}
			catch (CodeException& e) {
				cerr << e.what() << endl;
				return e.errCode();
			}
		}
		else if (argc == 3) {
			istringstream iss(argv[2]);
			unsigned int minimum;
			iss >> minimum;
			Director dic(argv[1],minimum);
			dic.cue();
			auto fut = dic.getResult();
			try {
				fut.get();
			}
			catch (CodeException& e) {
				cerr << e.what() << endl;
				return e.errCode();
			}
		}
	}
	catch (CodeException& error) {
		cerr << error.what() << endl;
		return error.errCode();
	}
	
	return SUCCESS;
}