// BrailleTcpListener.cc
// author: dipina@eside.deusto.es

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

/*
void *thread_listener(void *arg) {
	PracticaCaso::TcpClient *c = (PracticaCaso::TcpClient *)sarg;
	string msg = c->receive();
	cout << "Message received: " << msg << endl;
	c->send(msg);
	cout << "Message envidado: " << msg << endl;
	c->close();
}*/



int main() {
	signal(SIGINT,ctrl_c);
	PracticaCaso::TcpListener listener(6767);
	listener_pointer = &listener;
	cout << "TcpListener created: " << listener << endl;
	listener.start();

	map<string, string> a;

	a.insert (a.begin(), pair<string, string>("A","1")); 
	a.insert (a.begin(), pair<string, string>("B","2"));
	a.insert (a.begin(), pair<string, string>("C","3"));
	a.insert (a.begin(), pair<string, string>("D","4"));
	a.insert (a.begin(), pair<string, string>("E","5"));
	a.insert (a.begin(), pair<string, string>("F","6"));
	a.insert (a.begin(), pair<string, string>("G","7"));
	a.insert (a.begin(), pair<string, string>("H","8"));
	a.insert (a.begin(), pair<string, string>("I","9"));
	a.insert (a.begin(), pair<string, string>("J","10"));
	a.insert (a.begin(), pair<string, string>("K","11"));
	a.insert (a.begin(), pair<string, string>("L","12"));
	a.insert (a.begin(), pair<string, string>("M","13"));
	a.insert (a.begin(), pair<string, string>("N","14"));
	a.insert (a.begin(), pair<string, string>("Ñ","15"));
	a.insert (a.begin(), pair<string, string>("O","16"));
	a.insert (a.begin(), pair<string, string>("P","17"));
	a.insert (a.begin(), pair<string, string>("Q","18"));
	a.insert (a.begin(), pair<string, string>("R","19"));
	a.insert (a.begin(), pair<string, string>("S","20"));
	a.insert (a.begin(), pair<string, string>("T","21"));
	a.insert (a.begin(), pair<string, string>("U","22"));
	a.insert (a.begin(), pair<string, string>("V","23"));
	a.insert (a.begin(), pair<string, string>("W","24"));
	a.insert (a.begin(), pair<string, string>("X","25"));
	a.insert (a.begin(), pair<string, string>("Y","26"));
	a.insert (a.begin(), pair<string, string>("Z","27"));
	a.insert (a.begin(), pair<string, string>(".","28"));
	a.insert (a.begin(), pair<string, string>(",","29"));
	a.insert (a.begin(), pair<string, string>("_","30"));
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
