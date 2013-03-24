// Dsm.h
// author: dipina@eside.deusto.es
#ifndef __DSM_H
#define __DSM_H

#define MSGBUFSIZE 256

extern "C" {
	#include <pthread.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <time.h>
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
}

#include <sstream>

#include "Thread.h"
#include "TcpListener.h"
#include "DsmTypes.h"

namespace PracticaCaso
{
	class DsmDriver;
	class DsmObserver: public Thread { //va a estar escuchando los mensajes que lleguen 
		private:
			int fd;
			bool keepRunning;
			struct sockaddr_in addr;
			void run();

			DsmDriver* client;
		public:
			DsmObserver(DsmDriver* client);
			~DsmObserver() {}
			void stop();
	};

	// In order to act as a DSM client you need to instantiate a DsmDriver
	class DsmDriver: public TcpClient { 
		private:
			DsmNodeId nid;
			DsmObserver *observer;

			pthread_cond_t cond_t;
			pthread_mutex_t mutex_t;

			// Caches the DSM events multicasted by the DSM server everytime a new block is put or freed
			vector<DsmEvent> putEvents;
			// TODO: Declare here conditional variable  sync_cond thatcontrols the synchronisation between the Observer and the DsmDriver threads
		public:
			DsmDriver( string ipAddressNameServer, int portNameServer, string dmsServerName2Lookup );
			~DsmDriver();

			// Allows a DSM node to retrieve its ID
			DsmNodeId get_nid();
			// Issues a DSM command to the DSM server: malloc, put, get, free
			void dsm_malloc(string blockId, int size) throw (DsmException);
			void dsm_put(string blockId, void *content, int size) throw (DsmException);
			DsmData dsm_get(string blockId) throw (DsmException); 
			void dsm_free(string blockId) throw (DsmException);

			// dsm_notify is invoked by a DsmObserver to notify when a node undertakes a dsm_put command
			void dsm_notify(string cmd, string blockId); //se gestionan los mensajes que se envien desde el servidor
			// block the calling process until a dsm_put for blockId is received
			void dsm_wait(string blockId); //cuando haga un get de una variable que todavia no esta en el servido se llama a dsm_wait. hace una espera actica hasta que llegue el blockid

			friend ostream & operator << (ostream &os, DsmDriver &n);
	};
};
#endif
