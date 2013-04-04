#include "TcpListener.h"
#include "Dsm.h"
#include <iostream>

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
	PracticaCaso::DsmData data;
	string input = "";
	bool braille_trans = false;
	//El usuario mete una frase
	cout << "Please enter a valid sentence (with spaces):\n>";
	getline(cin, input);

	//se deja en memoria la frase para traducir
	try
    {
        driver->dsm_malloc("PLAIN_SENTENCE", sizeof(input));
        cout << "Adding the PLAIN_SENTENCE: " << driver->get_nid() << endl;
        try
        {
            driver->dsm_put("PLAIN_SENTENCE", &input, sizeof(input)); 
        }
        catch (DsmException dsme) 
        {
            cerr << "ERROR: dsm_put(\"PLAIN_SENTENCE\", input, " << sizeof(input) << ")): " << dsme << endl;
			driver->dsm_free("PLAIN_SENTENCE");
            exit(1);
        }
    }
    catch (DsmException dsme) 
    {
        cerr << "ERROR in dsm_malloc(\"PLAIN_SENTENCE\", input, " << sizeof(input) << ")): " << dsme << endl;
        //exit(1);
    }

	//se coge de memoria la frase traducida
	while (!braille_trans) {
		try {
			data = driver->dsm_get("BRAILLE_TRANSLATION");
			braille_trans = true;
		} catch (DsmException dsme) {
			cerr << "ERROR in dsm_get(\"BRAILLE_TRANSLATION\") - waiting for other process to initialize it: " << dsme << endl;
			driver->dsm_wait("BRAILLE_TRANSLATION");
		}
	}
	cout << "Your message's translation: " << (char *)data.addr << endl;
	driver->dsm_free("PLAIN_SENTENCE");
	delete driver;
}
