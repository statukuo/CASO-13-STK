#include "TcpListener.h"
#include "Dsm.h"
#include <iostream>
#include <map>

extern "C" {
	#include <sys/time.h>
}

void usage() {
	cout << "Usage: DsmBrailleClient <dns-server-ip> <dns-server-port> <dsm-server-name>" << endl;
	exit(1);
}

int main(int argc, char** argv) {

	if (argc != 4) {
		usage();
	}

	PracticaCaso::DsmDriver * driver = new PracticaCaso::DsmDriver(argv[1], atoi(argv[2]), argv[3]);
	PracticaCaso::DsmData sentence;
	PracticaCaso::DsmData alphabet;
	string result = "";
	bool braille_trans = false;

	//se coge de memoria la frase para traducir
	while (!braille_trans) {
		try {
			sentence = driver->dsm_get("PLAIN_SENTENCE");
			braille_trans = true;
			cout << "Se ha obtenido la frase correctamente: " << endl;
		} catch (DsmException dsme) {
			cerr << "ERROR in dsm_get(\"PLAIN_SENTENCE\") - waiting for other process to initialize it: " << dsme << endl;
			driver->dsm_wait("PLAIN_SENTENCE");
		}
	}

	//se coge el alfabeto braile de memoria
	/*while (!braille_trans) {
		try {
			alphabet = driver->dsm_get("BRAILLE_ALPHABET");
			braille_trans = true;
			cout << "Se ha obtenido la frase correctamente" << endl;
		} catch (DsmException dsme) {
			cerr << "ERROR in dsm_get(\"BRAILLE_ALPHABET\") - waiting for other process to initialize it: " << dsme << endl;
			driver->dsm_wait("BRAILLE_ALPHABET");
		}
	}*/

	//se traduce el mensaje
	int i;
	string msg = (char *)sentence.addr;
	//map<string, string> &alfabeto = *(std::map<string, string> *)alphabet.addr;
	cout << msg << endl;
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
	string response = "";
	string response2 = "";

	cout << "msg size: " << sentence.addr << endl;

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
			
			if (a.find(s) != a.end())
			{
				response = 	response + a.find(s)->second;
			}
			else
			{
				response = 	response + "//////";
			}	
		}		
	};

	for (i = 0; i < 3; i = i+1){
		for (int j = 0; j < msg.size(); j = j+1){
			response2 = response2 + response.substr ((i * 2) + (j*6),2);
		};

		response2 = response2 + "\n";
	};

	//se mete en memoria la frase traducida
	try
    {
        driver->dsm_malloc("BRAILLE_TRANSLATION", sizeof(response2));
        cout << "Adding the BRAILLE_TRANSLATION: " << driver->get_nid() << endl;
        try
        {
            driver->dsm_put("BRAILLE_TRANSLATION", &response2, sizeof(response2)); 
        }
        catch (DsmException dsme) 
        {
            cerr << "ERROR: dsm_put(\"BRAILLE_TRANSLATION\", response2, " << sizeof(response2) << ")): " << dsme << endl;
			driver->dsm_free("BRAILLE_TRANSLATION");
            exit(1);
        }
    }
    catch (DsmException dsme) 
    {
        cerr << "ERROR in dsm_malloc(\"BRAILLE_TRANSLATION\", response2, " << sizeof(response2) << ")): " << dsme << endl;
        exit(1);
    }
    sleep(1);
    driver->dsm_free("BRAILLE_TRANSLATION");
	delete driver;
}
