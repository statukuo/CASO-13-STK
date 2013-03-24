// DsmTypes.h
// author: dipina@eside.deusto.es
#ifndef __DSMTYPES_H
#define __DSMTYPES_H

#define DSM_PORT 12345
#define DSM_GROUP "225.0.0.37"

#include "TcpListener.h"
#include <vector>

using namespace std;

typedef int DsmNodeId;
typedef string DsmException;

namespace PracticaCaso
{
	struct DsmEvent {
		string cmd;
		string blockId;
	};

	struct DsmData {
		void *addr;
		int size;
	};

	struct DsmBlock {
		string blockId;
		DsmNodeId creatorNode; //el nodo que ha creado el bloque de memoria
		DsmNodeId lastAccessNode; //el ultimo nodo que ha accedido al bloque de memoria. se guarda así porque solo el creador puede borrar el bloque, no puede hacerlo cualquiera
		int blockSize;
		void *addr;
		int size; //para comprobar que el size entra en el block size que hemos reservado
	};

	struct DsmNodeMetadata {
		DsmNodeId nid;
		TcpClient* client; //socket de conexión
		vector <DsmBlock> dsmBlocksRequested;//registrando los bloques que va usando. no sirve para nada mas.
	};
};

#endif
