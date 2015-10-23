#include <iostream>
#include <queue>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>

using namespace std;

int main(int argc, char* argv[]){
	if (argc < 2)
		return 1;

	ACE_INET_Addr addr(1234, ACE_LOCALHOST);
	ACE_SOCK_Stream stream;
	ACE_SOCK_Connector connector;

	int success = connector.connect(stream, addr);

	if (success < 0) {
		cout << "Cannot connect" << endl;
		return 1;
	}

	ACE_TCHAR addrStr[20];
	addr.addr_to_string(addrStr, 20);

	/*
	for (int i = 1; i < argc; i++) {
		string str(argv[i]);
		stream.send_n(&str, sizeof(str));
		stream.send_n(&string(" "), sizeof(string(" ")));
	}
	//*/

	//*
	for (int i = 1; i < argc; i++) {
		stream.send_n((argv[i]), strlen(argv[i]));
		stream.send_n(" ", 1);
	}
	//*/

	stream.close();

	cout << endl << "Done" << endl;



	return 0;
}