#ifndef __DSMBRAILLESERVER_H
#define __DSMBRAILLESERVER_H

#include "Thread.h"
#include "TcpListener.h"
#include "DsmServer.h"

namespace PracticaCaso
{
	class DsmBrailleServer: public Thread {
		private:
			void run();
	};
};
#endif
