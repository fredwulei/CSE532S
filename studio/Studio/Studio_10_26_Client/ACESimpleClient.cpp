#include <iostream>
#include <queue>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>
#include <ace/Event_Handler.h>
#include <ace/Timer_Queue_Adapters.h>
#include <ace/Timer_Heap.h>
// #include <ace/Timer_Heap_T.h>
#include <ace/Event_Handler_Handle_Timeout_Upcall.h>
#include <ace/Reactor.h>
#include <ace/Get_Opt.h>
#include <thread>
#include <chrono>

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
		
		for (int i = 1; i < argc; i++) {
			stream.send_n((argv[i]), strlen(argv[i]));
			stream.send_n(" ", 1);
		}
		return 0;
	}

	virtual int handle_input(ACE_HANDLE h = ACE_INVALID_HANDLE){


		return 0;
	}


	virtual int handle_output(ACE_HANDLE h = ACE_INVALID_HANDLE){

		for (int i = 1; i < argc; i++) { 
			stream.send_n((argv[i]), strlen(argv[i]));
			stream.send_n(" ", 1);
		}
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

	//static const ACE_TCHAR options[] = ACE_TEXT(": f:");
	//ACE_Get_Opt cmd_opts
	//	(argc, argv, options, 1, 0, ACE_Get_Opt::PERMUTE_ARGS, 1);
	//// Specify the short switch corresponding long option switch
	//if (cmd_opts.long_option(ACE_TEXT("config"), 'f', ACE_Get_Opt::ARG_REQUIRED) == -1)
	//	return 1;


	Client client(argc, argv);

	ACE_Time_Value interval(3, 0);
	ACE_Time_Value delay(0, 0);
	ACE_Time_Value currTime = ACE_OS::gettimeofday();
	
	/*
	ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> timer;
	timer.activate();
	timer.schedule(&client, 0, currTime+interval, interval);
	ACE_Thread_Manager::instance()->wait();
	//*/

	ACE_Reactor::instance()->schedule_timer(&client, 0, delay, interval);
	ACE_Reactor::instance()->run_event_loop();
	// ACE_Reactor::instance()->run_reactor_event_loop();


	return 0;
}