// BrailleServerThread.h
// author: dipina@eside.deusto.es
#ifndef __ECHOSERVERTHREAD_H
#define __ECHOSERVERTHREAD_H

#include <map>


#include "Thread.h"
#include "TcpListener.h"


namespace PracticaCaso
{
	class BrailleServerThread: public Thread {
		private:
			TcpClient* client;
			map<string, string> alfabeto;

			void run();
		public:
			BrailleServerThread(TcpClient* c, map<string, string> a): client(c) {alfabeto = a;}
			~BrailleServerThread();
	};
};
#endif
