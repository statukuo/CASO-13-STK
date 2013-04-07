// BrailleTcpListener.cc
// author: CASO-13

#include "TcpListener.h"
#include "BrailleServerThread.h"

extern "C" {
	#include </usr/include/signal.h>
}

// global variable
PracticaCaso::TcpListener * listener_pointer;

// function called when CTRL-C is pressed
void ctrl_c(int)
{
    cout << "CTRL-C was pressed..." << endl;
	listener_pointer->stop();
}

void usage() {
	cout << "Usage: BrailleTcpListener <server-port>" << endl;
	exit(1);
}




int main(int argc, char** argv) {
	if (argc != 2) {
		usage();
	}

	signal(SIGINT,ctrl_c);
	PracticaCaso::TcpListener listener(atoi(argv[1]));
	listener_pointer = &listener;
	cout << "TcpListener created: " << listener << endl;
	listener.start();

	map<string, string> a;

	a.insert (a.begin(), pair<string, string>("A","*     ")); 
	a.insert (a.begin(), pair<string, string>("B","* *   "));
	a.insert (a.begin(), pair<string, string>("C","**    "));
	a.insert (a.begin(), pair<string, string>("D","** *  "));
	a.insert (a.begin(), pair<string, string>("E","*  *  "));
	a.insert (a.begin(), pair<string, string>("F","***   "));
	a.insert (a.begin(), pair<string, string>("G","****  "));
	a.insert (a.begin(), pair<string, string>("H","* **  "));
	a.insert (a.begin(), pair<string, string>("I"," **   "));
	a.insert (a.begin(), pair<string, string>("J"," ***  "));
	a.insert (a.begin(), pair<string, string>("K","*   * "));
	a.insert (a.begin(), pair<string, string>("L","* * * "));
	a.insert (a.begin(), pair<string, string>("M","**  * "));
	a.insert (a.begin(), pair<string, string>("N","** ** "));
	a.insert (a.begin(), pair<string, string>("Ñ","15"));
	a.insert (a.begin(), pair<string, string>("O","*  ** "));
	a.insert (a.begin(), pair<string, string>("P","*** * "));
	a.insert (a.begin(), pair<string, string>("Q","***** "));
	a.insert (a.begin(), pair<string, string>("R","* *** "));
	a.insert (a.begin(), pair<string, string>("S"," ** * "));
	a.insert (a.begin(), pair<string, string>("T"," **** "));
	a.insert (a.begin(), pair<string, string>("U","*   **"));
	a.insert (a.begin(), pair<string, string>("V","* * **"));
	a.insert (a.begin(), pair<string, string>("W","**  **"));
	a.insert (a.begin(), pair<string, string>("X","** ***"));
	a.insert (a.begin(), pair<string, string>("Y","** ***"));
	a.insert (a.begin(), pair<string, string>("Z","*  ***"));
	a.insert (a.begin(), pair<string, string>(".","    * "));
	a.insert (a.begin(), pair<string, string>(",","  *   "));
	a.insert (a.begin(), pair<string, string>("_","    **"));	
	a.insert (a.begin(), pair<string, string>("!","  *** "));
	a.insert (a.begin(), pair<string, string>("?","  *  *"));	
	a.insert (a.begin(), pair<string, string>("¡","  *** "));
	a.insert (a.begin(), pair<string, string>("¿","  *  *"));
	a.insert (a.begin(), pair<string, string>(" "," "));

	while (true) {
		PracticaCaso::TcpClient* client = listener.acceptTcpClient();
		
		//string msg = client->receive();
		//client->send(msg);
		//client->close();
		
		// MODIFICATION 2.3.5

		PracticaCaso::BrailleServerThread* t = new PracticaCaso::BrailleServerThread(client, a);
		t->start();
		
		/*
		pthread_t thread_id;
		int status_listener = pthread_create(&thread_id, NULL, thread_listener, client);
		// check if the thread wass well created
		if(status_listener==0) {
			cout << "Thread was correctly initialized" << endl;
		} else {
			cout << "[aborted]\n" << "[error - initialising thread]" << endl;
			exit(1);
		}*/
	}
	cout << "Finishing server ..." << endl;
	listener.stop();
}
