// BrailleTcpClient.cc
// author: dipina@eside.deusto.es

#include "TcpListener.h"

void usage() {
	cout << "Usage: BrailleTcpClient <server-port> <domain-name-to-resolve>" << endl;
	exit(1);
}

int main(int argc, char** argv) {
	

	

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
		//SEGUNDA CONEXION PARA YA REALIZAR LA LOGICA
		client->connect(ipAddressAndPort.substr(0, ipAddressAndPort.find(":")), atoi((ipAddressAndPort.substr(ipAddressAndPort.find(":")+1)).c_str()));

		string input = "";
		//PREGUNTAMOS PARA VER QUE QUIERE (OLA K ASE, OLA K KIERE TRADUCI)
		cout << "Please enter a valid sentence (with spaces):\n>";
		getline(cin, input);

		client->send(input);
		cout << "Message sent for translate: " << input << endl;

		input = client->receive();

		//HAY QUE PROCESARLO :D
		cout << "Message received already translated: \n" << input << endl;

		client->close();	
	}	
	delete client;

}

