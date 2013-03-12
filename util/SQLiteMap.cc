// SQLiteMap.cc
// author: dipina@eside.deusto.es
// compile: g++ SQLiteMap.cc -lsqlite3 -o SQLiteMap
#include "SQLiteMap.h"

namespace PracticaCaso {
	SQLiteMap::SQLiteMap(string fn): fileName(fn), dbh(0) {
		// Process the contents of the mapping file
		this->loadMappings(fn);
	}

	SQLiteMap::SQLiteMap(const SQLiteMap& rhs) {
		fileName = rhs.fileName;
		dbh = rhs.dbh;
		this->loadMappings(fileName);
	}

	SQLiteMap::~SQLiteMap() {
		cout << "SQLiteMap: destructor called " << endl;
		this->close();
	}

	void SQLiteMap::loadMappings(string mappingsDBFileName) {
		// Loads the mappings stored at SQLite DB into the map loadMappings

		char *toEncodePoint=new char[mappingsDBFileName.size()+1];
		toEncodePoint[mappingsDBFileName.size()]=0;
		memcpy(toEncodePoint,mappingsDBFileName.c_str(),mappingsDBFileName.size());

		cout << "Abriendo la base de datos ..." << endl;
		if (sqlite3_open(toEncodePoint, &dbh) != SQLITE_OK) {
			cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(dbh) << endl;
			sqlite3_close(dbh);
			exit(1);
		}

		// In the case that the DB does not exist, create it, its structure is given by file KeyValueDB.sql

		char **result;
     	int nrow;
      	int ncol;
       	char *errorMsg;
	    cout << "Checkeando si existe KeyValueDB.sql ..." << endl;
	    if (sqlite3_get_table(dbh, "select * from KeyValuePair", &result, &nrow, &ncol, &errorMsg) != SQLITE_OK) 
		{
			// If a select * from KeyValuePair executed through a sqlite3_get_table does not return SQLITE_OK, it means that the table does not exist, and needs being created
			cerr << errorMsg << endl;
			sqlite3_free(errorMsg);
			if (sqlite3_get_table(dbh, "create table KeyValuePair ( key_element      BLOB NOT NULL PRIMARY KEY, value_element    BLOB );", &result, &nrow, &ncol, &errorMsg) != SQLITE_OK) 
			{
				cerr << errorMsg << endl;
				sqlite3_close(dbh);
				exit(1);
			}
			else 
			{
				cout << "Creada la tabla KeyValuePair.sql" << endl;
				sqlite3_free_table(result);
			}
        }
		else
		{
			cout << "Contenido de dns2IpPortMap..." << endl;
			if (sqlite3_get_table(dbh, "select * from KeyValuePair", &result, &nrow, &ncol, &errorMsg) != SQLITE_OK) 
			{
				cerr << errorMsg << endl;
				sqlite3_free(errorMsg);
			} 
			else 
			{
			   for (int i=1; i<=nrow; i++) 
			   {
			   		//Como en el ejemplo de sqlite3
					map<string, string>::iterator ite;
					ite= dns2IpPortMap.begin();
					dns2IpPortMap.insert (ite, pair<string, string>(string(result[i*ncol]),string(result[i*ncol+1])));  
			   		cout << string(result[i*ncol]) + " / " + string(result[i*ncol+1]) << endl;
			   }
			sqlite3_free_table(result);
			}
		}
		
		// If there are unexpected error exit the program with exit(1)
	}

	
	map<string, string> SQLiteMap::getMap() {
		// To do
		//devuelve el objeto del .h
		return dns2IpPortMap;
	}


	string SQLiteMap::get(string key) {
		// To do
		// lo mismo que arriba, pero buscando dentro de el
		return dns2IpPortMap.find(key)->second;
	}

	void SQLiteMap::set(string mapKey, string mapValue) {
		// Undertake the update of the STL map and the database. Bear in mind that it there is not an entry with a passed key an INSERT will have to be executed, if there was already such an entry an UPDATE will take place
		
		//Meto el valor del map
		this->dns2IpPortMap[mapKey] = mapValue;

		char **result;
		int nrow;
		int ncol;
		char *errorMsg;

		string q;

		q = "select * from KeyValuePair where key_element='"+mapKey+"'";

		//Miro a ver si esta dentro de la BD

		if (sqlite3_get_table(dbh, q.c_str(), &result, &nrow, &ncol, &errorMsg) != SQLITE_OK) 
		{
			//Error al seleccionar
			cerr << errorMsg << endl;
			sqlite3_free(errorMsg);
			sqlite3_close(dbh);
			exit(1);
		}


		if (nrow == 0) //Si no hay resultado es que no esta en la BD, asi que lo meto
		{
			q = "insert into KeyValuePair values('" + mapKey + "', '" + mapValue + "')";
			if (sqlite3_get_table(dbh, q.c_str(), &result, &nrow, &ncol, &errorMsg) != SQLITE_OK)
			{
				//Error al insertar
				cerr << errorMsg << endl;
				sqlite3_free(errorMsg);
				sqlite3_close(dbh);
				exit(1);
			} 

			map<string, string>::iterator i;
			i= dns2IpPortMap.begin();
			dns2IpPortMap.insert (i, pair<string, string>(mapKey,mapValue));  
			cout << "Entrada creada: " << nrow << endl;
		}
		else //Si hay mas de 0 filas, es que si que hay algo, asi que lo actualizo 
		{	
			q= "update KeyValuePair set value_element = '" + mapKey + "' where key_element = '" + mapValue + "'";
			if (sqlite3_get_table(dbh, q.c_str(), &result, &nrow, &ncol, &errorMsg) != SQLITE_OK)
			{
				cerr << errorMsg << endl;
				sqlite3_free(errorMsg);
				sqlite3_close(dbh);
				exit(1);
			}
			this->dns2IpPortMap[mapKey] = mapValue;
		}

		sqlite3_free_table(result);
	}


	void SQLiteMap::close() {
		// Close the database properly
		// Como en el ejemplo de SQLITE
		if (dbh) {
			sqlite3_close(dbh);
		}
			
	}

	ostream & operator << (ostream & os, SQLiteMap &t) {
		os << "DB file name: " << t.fileName << endl;
		os << "DNS mappings:" << endl;
		typedef map<string, string>::const_iterator CI;
		for (CI p = t.dns2IpPortMap.begin(); p != t.dns2IpPortMap.end(); ++p) {
			os <<  p->first << " : " << p->second << endl;
		}
		return os;
	}
}


/*
// global variable
PracticaCaso::SQLiteMap * SQLiteMap_pointer;

// function called when CTRL-C is pressed
void ctrl_c(int)
{
    printf("\nCTRL-C was pressed...\n");
	delete SQLiteMap_pointer;
}


void usage() {
	cout << "Usage: SQLiteMap <name-mappings-db-file>" << endl;
	exit(1);
}

int main(int argc, char** argv) {
	signal(SIGINT,ctrl_c);

	if (argc != 2) {
		usage();
	}

	PracticaCaso::SQLiteMap * SQLiteMap = new PracticaCaso::SQLiteMap((string)argv[1]);
	cout << "SQLiteMap instance: " << endl << SQLiteMap << endl;
	//SQLiteMap_pointer = &SQLiteMap;
	SQLiteMap_pointer = SQLiteMap;

	//SQLiteMap.set("saludo", "hola");
	//SQLiteMap.set("despedida", "adios");
	SQLiteMap->set("saludo", "hola");
	SQLiteMap->set("despedida", "adios");

	//cout << "SQLiteMap[\"saludo\"] = " << SQLiteMap.get("saludo") << endl;
	//cout << "SQLiteMap[\"despedida\"] = " << SQLiteMap.get("despedida") << endl;
	cout << "SQLiteMap[\"saludo\"] = " << SQLiteMap->get("saludo") << endl;
	cout << "SQLiteMap[\"despedida\"] = " << SQLiteMap->get("despedida") << endl;

	cout << "SQLiteMap instance after 2 sets: " << endl << *SQLiteMap << endl;

	//map<string, string> savedSQLiteMap = SQLiteMap.getMap();
	map<string, string> savedSQLiteMap = SQLiteMap->getMap();
	cout << "Recuperado el mapa" << endl;
	typedef map<string, string>::const_iterator CI;
	for (CI p = savedSQLiteMap.begin(); p != savedSQLiteMap.end(); ++p) {
		cout << "dns2IpPortMap[" << p->first << "] = " << p->second << endl;
	}
	
	delete SQLiteMap_pointer;
}
*/

