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
	cout << "Getting GLOBAL_TIMESTAMP: " << driver->get_nid() << endl;

	bool global_tmp = false;
	
	while(!global_tmp){
		try {
			data = driver->dsm_get("GLOBAL_TIMESTAMP");
			global_tmp = true;
		} catch (DsmException dsme) {
			cerr << "ERROR: dsm_get(\"GLOBAL_TIMESTAMP\") - Waiting for other process to initialise it: " << dsme << endl;
			driver->dsm_wait("GLOBAL_TIMESTAMP");
		}
	}
	
	struct timeval *timestamp = (struct timeval*)data.addr;
	settimeofday(timestamp, NULL);

	char buffer[100];
	struct timeval tv;
	time_t curtime;

	gettimeofday(&tv, NULL); 
	curtime=tv.tv_sec;
    strftime(buffer,100,"%d-%m-%Y, %H:%M:%S",localtime(&curtime));
	cout << "new system time set " << buffer << endl;

	cout << "System time set shincronized to the server. " << endl;

	delete driver;
}
