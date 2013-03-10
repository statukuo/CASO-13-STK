// EchoTcpClient.cc
// author: dipina@eside.deusto.es

#include "TcpListener.h"

void usage() {
	cout << "Usage: EchoTcpClient <server-port> <domain-name-to-resolve>" << endl;
	exit(1);
}

int main(int argc, char** argv) {
/*
	// MODIFICATION 2.3.3
		PracticaCaso::TcpClient * client = new PracticaCaso::TcpClient();
		client->connect("127.0.0.1", 4321);
		string msg = "¡Hello CASO students!";
		client->send(msg);
		cout << "Message sent: " << msg << endl;
		msg = client->receive();
		cout << "Message received: " << msg << endl;
		client->close();	
		delete client;
*/
	// MODIFICATION 2.3.5
	if (argc != 3) {
		usage();
	}


	PracticaCaso::TcpClient * client = new PracticaCaso::TcpClient();
	client->connect("127.0.0.1", atoi(argv[1]));
	string dnsName = argv[2];
	client->send(dnsName);
	string ipAddressAndPort = client->receive();
	client->close();
	if (ipAddressAndPort.find("ERROR") == 0) {
		cout << "The DNS name " << dnsName << " could not be resolved." << endl;
	} else {
		cout << "The DNS name: " << dnsName << " corresponds to: " << ipAddressAndPort << endl;
		client->connect(ipAddressAndPort.substr(0, ipAddressAndPort.find(":")), atoi((ipAddressAndPort.substr(ipAddressAndPort.find(":")+1)).c_str()));
		string msg = "HOLA K ASE!";
		client->send(msg);
		cout << "Message sent: " << msg << endl;
		msg = client->receive();
		cout << "Message received: " << msg << endl;
		client->close();	
	}	
	delete client;

}

