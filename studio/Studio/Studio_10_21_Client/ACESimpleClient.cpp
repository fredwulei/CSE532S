#include <iostream>
#include <queue>
#include <ace/INET_Addr.h>
#include <ace/Log_Msg.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>

using namespace std;

struct Packet
{
	int id;
	char msg[BUFSIZ];
};



int main(int argc, char* argv[]){
	//if (argc < 2)
	//	return 1;

	ACE_INET_Addr addr(1234, ACE_LOCALHOST);
	ACE_SOCK_Stream stream;
	ACE_SOCK_Connector connector;

	int success = connector.connect(stream, addr);

	if (success < 0) {
		ACE_ERROR_RETURN((LM_ERROR,	"%p\n", "acceptor.open"), 100);
	}

	ACE_TCHAR addrStr[20];
	addr.addr_to_string(addrStr, 20);

	ssize_t sent = 0;


	char str[BUFSIZ];
	string sstr;

	/*
	for (int i = 1; i < argc; i++) {
		sent += stream.send_n(argv[i], strlen(argv[i]));
		sstr += stream.send_n(" ", 1);
	}	
	//*/



	//*
	for (int i = 1; i < argc; i++) {
		sstr += string(argv[i]);
		sstr += string(" ");
	}

	Packet packet;

	packet.id = 0;
	strcpy_s(packet.msg, sstr.c_str());
	sent = stream.send_n(&packet, sizeof(Packet));
	//*/

	// cout << "Sent " << sent << endl;

	int n;

	stream.recv(&packet, sizeof(Packet));
	cout << packet.id << endl;
	cout << packet.msg << endl;

	/*
	int n;
	char buf[BUFSIZ];

	while ((n = stream.recv(buf, BUFSIZ)) > 0) {
		_write(1, buf, n);
	}
	//*/

	stream.close();

	cout << endl << "Done" << endl;



	return 0;
}