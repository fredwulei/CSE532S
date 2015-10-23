#include <iostream>
#include <stdio.h>
#include <string>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Acceptor.h>

using namespace std;


int main(int argc, char* argv[]){
	if (argc > 1){
		return 1;
	}
	
	cout << argv[0] << endl;


	ACE_INET_Addr addr(1234, ACE_LOCALHOST);
	ACE_SOCK_Stream stream;
	ACE_SOCK_Acceptor acceptor;

	int success = acceptor.open(addr, 1);
	
	ACE_TCHAR addrStr[20];

	if (success > 0) {
		addr.addr_to_string(addrStr, 20);
	}

	success = acceptor.accept(stream);

	if (success < 0) {
		cout << "Cannot accept" << endl;
		return 1;
	}



	char buf[BUFSIZ];
	int n;


	/*
	string str;

	while (n = stream.recv(&str, 1000)) {
		cout << str << " ";
	}

	//*/

	
	//*
	while (n = stream.recv(buf, BUFSIZ)) {
		_write(1, buf, n);
	}	
	//*/


	cout << endl << "Done" << endl;

	return 0;
}
