// BrailleServerThread.cc
// author: dipina@eside.deusto.es

#include "BrailleServerThread.h"

#include <sstream>
#include <string>

namespace PracticaCaso
{
	BrailleServerThread::~BrailleServerThread() {
		delete this->client;
	}

	void BrailleServerThread::run() {
		// make the type casting and recuperate the parameters using "arg"

		cout << "AHORA LO IMPORTANTE";
		//RECIBE EL MENSAJE EN CLARO
		string msg = (this->client)->receive();

		cout << "Message received: " << msg << endl;

		//AQUI VENDRIA LA GESTION DEL MENSAJE
		int i;
		string response = "";
		string response2 = "";

		for(i = 0;i < msg.size();i=i+1){
			char space = msg[i];

			if (isspace(space)){
				response = 	response + "      ";
			}else{
				stringstream ss;
				string s;
				char c = toupper(msg[i]);
				ss << c;
				ss >> s;
				
				if (alfabeto.find(s) != alfabeto.end())
				{
					response = 	response + alfabeto.find(s)->second;
				}
				else
				{
					response = 	response + "//////";
				}	
			}		
		};

		for (i = 0; i < 3; i = i+1){
			for (int j = 0; j < msg.size(); i = i+1){
				response2 = response2 + response.substr ((i * 2) + (j*6),2);
			};

			response2 = response2 + "\n";
		};



		




		//AQUI SE DEVOLVERIA EL MENSAJE BRAILLEADO
		(this->client)->send(response2);
		cout << "Message sent: " << response2 << endl;
		(this->client)->close();
	}
}
