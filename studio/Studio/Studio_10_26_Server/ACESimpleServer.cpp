#include <iostream>
#include <stdio.h>
#include <string>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Event_Handler.h>
#include <ace/Reactor.h>

using namespace std;

class Server :public ACE_Event_Handler{
public:
	virtual ~Server(){ this->handle_close(ACE_INVALID_HANDLE, 0); }

	Server(int argc_, char** argv_) :argc(argc_), argv(argv_){
		ACE_INET_Addr addr(1234, ACE_LOCALHOST);
		acceptor.open(addr, 1);
		// int success = acceptor.accept(stream);
	}

	/*
	virtual int handle_timeout(const ACE_Time_Value & timeValue, const void* ptr = nullptr){
		cout << "Time out" << endl;
		return 0;
	}
	*/

	virtual int handle_input(ACE_HANDLE h/* = ACE_INVALID_HANDLE*/){
		cout << "Here" << endl;

		//int success = acceptor.accept(stream);

		//if (success < 0) {
		//	cout << "Cannot accept" << endl;
		//}
		//else{
		//	char buf[BUFSIZ];
		//	int n;

		//	while ((n = stream.recv(buf, BUFSIZ)) > 0) {
		//		_write(1, buf, n);
		//		//cout << buf << endl;
		//	}
		//}

		return 0;
	}


	/*
	virtual int handle_output(ACE_HANDLE h = ACE_INVALID_HANDLE){
		cout << "Output" << endl;
		return 0;
	}
	*/

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
	int argc;
	char** argv;
	ACE_SOCK_Stream stream;
	ACE_SOCK_Acceptor acceptor;

};





int main(int argc, char* argv[]){
	if (argc > 1){
		return 1;
	}
	

	/*
	char buf[BUFSIZ];
	int n;

	ACE_INET_Addr addr(1234, ACE_LOCALHOST);
	ACE_SOCK_Stream stream;
	ACE_SOCK_Acceptor acceptor;
	int success = acceptor.open(addr, 1);
	ACE_TCHAR addrStr[20];

	if (success > -1) {
		addr.addr_to_string(addrStr, 20);
		cout << "Address is " << addrStr << endl;
	}
	
	
	for (;;) {			
		success = acceptor.accept(stream);

		if (success < 0) {
			cout << "Cannot accept" << endl;
			return 1;
		}
					
		while ((n = stream.recv(buf, BUFSIZ)) > 0) {
			_write(1, buf, n);
			//cout << buf << endl;
		}

		if (n < 0) {
			cout << "Error" << endl;
			break;
		}
		else{
			cout << endl;
		}
	}

	cout << endl << "Done" << endl;
	stream.close();
	//*/

	cout << "28 new Server" << endl;

	Server server(argc, argv);
	//ACE_Reactor::instance()->register_handler(&server, ACE_Event_Handler::ALL_EVENTS_MASK);
	ACE_Reactor::instance()->register_handler(&server, ACE_Event_Handler::ACCEPT_MASK);
	//server.handle_input();

	//while (true)
	//{
	//	ACE_Reactor::instance()->handle_events();
	//}

	ACE_Reactor::instance()->run_reactor_event_loop();

	return 0;
}
