#include <iostream>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>
#include <ace/Event_Handler.h>
#include <ace/Reactor.h>
#include "Packet.h"

using namespace std;

class Client :public ACE_Event_Handler{
public:
	Client(int argc_, char** argv_) :argc(argc_), argv(argv_){
		ACE_INET_Addr addr(1234, ACE_LOCALHOST);
		ACE_SOCK_Connector connector;
		int success = connector.connect(stream, addr);
		if (success < 0) {
			cout << "Cannot connect" << endl;
			// return 1;
		}

		ACE_TCHAR addrStr[20];
		addr.addr_to_string(addrStr, 20);

	}
	virtual int handle_timeout(const ACE_Time_Value & timeValue, const void* ptr = nullptr){

		/*for (int i = 1; i < argc; i++) {
			stream.send_n((argv[i]), strlen(argv[i]));
			stream.send_n(" ", 1);
		}*/
		return 0;
	}

	virtual int handle_input(ACE_HANDLE h = ACE_INVALID_HANDLE){
		Packet packet;

		stream.recv_n(&packet, sizeof(Packet));

		cout << packet.id << endl;
		cout << packet.msg << endl;

		return 0;
	}


	virtual int handle_output(ACE_HANDLE h = ACE_INVALID_HANDLE){
		string str;

		for (int i = 1; i < argc; i++) {
			str += string(argv[i]);
			str += string(" ");
		}

		Packet packet;

		packet.id = 0;
		strcpy_s(packet.msg, str.c_str());
		stream.send_n(&packet, sizeof(Packet));
		return 0;
	}

	ACE_HANDLE get_handle(void) const
	{
		return stream.get_handle();
	}

private:
	int argc;
	char** argv;
	ACE_SOCK_Stream stream;

};


int main(int argc, char** argv){
	if (argc < 2)
		return 1;

	Client client(argc, argv);

	ACE_Time_Value interval(3, 0);
	ACE_Time_Value delay(0, 0);


	//ACE_Reactor::instance()->schedule_timer(&client, 0, delay, interval);
	ACE_Reactor::instance()->register_handler(&client, ACE_Event_Handler::ALL_EVENTS_MASK);
	ACE_Reactor::instance()->run_reactor_event_loop();


	return 0;
}