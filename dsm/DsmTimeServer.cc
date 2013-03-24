#include "TcpListener.h"
#include "Dsm.h"

#include <iostream>

extern "C" {
	#include <sys/time.h>
}

void usage() {
	cout << "Usage: DsmTimeclient <dns-server-ip> <dns-server-port> <dsm-server-name>" << endl;
	exit(1);
}

int main(int argc, char** argv) {

	if (argc != 4) {
		usage();
	}

	PracticaCaso::DsmDriver * driver = new PracticaCaso::DsmDriver(argv[1], atoi(argv[2]), argv[3]);
	PracticaCaso::DsmData data;

	struct timeval timestamp;
	struct timezone tzp;

	try {
		driver->dsm_malloc("GLOBAL_TIMESTAMP", sizeof(timestamp));
		while(1)
		{
			try {
				gettimeofday(&timestamp, &tzp);
				// How to print out the current time in console				
				char buffer[100];
				struct timeval tv;
				time_t curtime;

				gettimeofday(&tv, NULL); 
				curtime=tv.tv_sec;
			    strftime(buffer,100,"%d-%m-%Y, %H:%M:%S",localtime(&curtime));
				cout << "new system time set " << buffer << endl;
				driver->dsm_put("GLOBAL_TIMESTAMP", &timestamp, sizeof(timestamp)); 
			} catch (DsmException dsme) {
				cerr << "ERROR: dsm_put(\"GLOBAL_TIMESTAMP\", a, " << sizeof(timestamp) << ")): " << dsme << endl;
				driver->dsm_free("GLOBAL_TIMESTAMP");
				exit(1);
			}

			sleep(1);
		}
	} catch (DsmException dsme) {
		// There may be several processes doing a dsm_malloc, only the first one will succeed 
		cerr << "ERROR in dsm_malloc(\"GLOBAL_TIMESTAMP\", sizeof(" << sizeof(timestamp) << ")): " << dsme << endl;
		exit(1);
	}
	delete driver;
}
