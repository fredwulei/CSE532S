#include <iostream>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Event_Handler.h>
#include <ace/Reactor.h>
#include <ace/Signal.h>
#include "Packet.h"

using namespace std;

class Server :public ACE_Event_Handler{
public:
	virtual ~Server(){ this->handle_close(ACE_INVALID_HANDLE, 0); }

	Server(int argc_, char** argv_) :argc(argc_), argv(argv_){
		ACE_INET_Addr addr(1234, ACE_LOCALHOST);
		acceptor.open(addr, 1);
		counter = 0;
	}


	virtual int handle_signal(int signum, siginfo_t * /* = 0 */, ucontext_t * /*= 0 */ ){

		cout << "In Handle_Signal" << endl;

		if (signum == SIGINT){
			cout << "SIGINT" << endl;
		}
		else if (signum == SIGQUIT){
			cout << "End Event Loop" << endl;
			ACE_Reactor::end_event_loop();
		}
		else {
			cout << "Unknown SIG" << endl;
		}
		return 0;
	}

	virtual int handle_input(ACE_HANDLE h = ACE_INVALID_HANDLE){
		int success = acceptor.accept(stream);
		counter++;

		if (success < 0) {
			cout << "Cannot accept" << endl;
		}
		else{
			// char buf[BUFSIZ];
			int n;
			Packet packet;

			stream.recv_n(&packet, sizeof(Packet));

			cout << packet.id << endl;
			cout << packet.msg << endl;


			packet.id = counter;
			strcpy_s(packet.msg, "see next");

			stream.send_n(&packet, sizeof(Packet));
		}

		return 0;
	}
	
	virtual int handle_output(ACE_HANDLE h = ACE_INVALID_HANDLE){
		return 0;
	}	

	ACE_HANDLE get_handle(void) const {
		return acceptor.get_handle();
	}

	virtual int handle_close(ACE_HANDLE handle,
		ACE_Reactor_Mask close_mask)
	{
		/*cout << endl << "connecetd closed";
		return ACE_Event_Handler::handle_close(handle, close_mask);*/


		if (this->acceptor.get_handle() != ACE_INVALID_HANDLE)
		{
			ACE_Reactor_Mask m = ACE_Event_Handler::ACCEPT_MASK |
				ACE_Event_Handler::DONT_CALL;
			this->reactor()->remove_handler(this, m);
			this->acceptor.close();
		}
		return 0;
	}

private:
	int counter;
	int argc;
	char** argv;
	ACE_SOCK_Stream stream;
	ACE_SOCK_Acceptor acceptor;

};


int main(int argc, char* argv[]){
	if (argc > 1){
		return 1;
	}

	Server server(argc, argv);
	ACE_Reactor::instance()->register_handler(&server, ACE_Event_Handler::ALL_EVENTS_MASK);
	ACE_Sig_Set sigSet;
	//sigSet.sig_add(SIGINT);
	sigSet.sig_add(SIGQUIT);
	//sigSet.fill_set();


	//ACE_Reactor::instance()->register_handler(SIGINT, &server);
	ACE_Reactor::instance()->register_handler(sigSet, &server);
	
	ACE_Reactor::instance()->run_reactor_event_loop();

	return 0;
}
