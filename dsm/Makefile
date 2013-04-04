# Makefile
# author: dipina@eside.deusto.es
CC=g++
LDFLAGS=-L../util -lm -lpthread -lesidesocket -lesidethread
INCLUDE=-I../util

main: libesidedsm.so DsmServer DsmTest MatrixEvenAdder MatrixOddAdder DsmTimeServer DsmTimeClient  DsmBrailleClient DsmBrailleTranslator 
#DsmBrailleServer

libesidedsm.so: Dsm.o
	$(CC) -shared $(LDFLAGS) Dsm.o -o libesidedsm.so
	cp libesidedsm.so libesidedsm.dll
	cp libesidedsm.* ../util/
		
Dsm.o: Dsm.cc Dsm.h DsmTypes.h
	$(CC) $(INCLUDE) -c Dsm.cc
	
DsmServer: DsmServer.o
	$(CC)  DsmServer.o $(LDFLAGS) -o DsmServer

DsmTest: DsmTest.o
	$(CC) DsmTest.o $(LDFLAGS) -L. -lesidedsm -o DsmTest

#Matrix example
	
MatrixEvenAdder: MatrixEvenAdder.o
	$(CC) MatrixEvenAdder.o $(LDFLAGS) -L. -lesidedsm -o MatrixEvenAdder
	
MatrixOddAdder: MatrixOddAdder.o
	$(CC) MatrixOddAdder.o $(LDFLAGS) -L. -lesidedsm -o MatrixOddAdder

#Proposal

#DsmBrailleServer: DsmBrailleServer.o
	#$(CC) DsmBrailleServer.o $(LDFLAGS) -L. -lesidedsm -o DsmBrailleServer

DsmBrailleClient: DsmBrailleClient.o
	$(CC) DsmBrailleClient.o $(LDFLAGS) -L. -lesidedsm -o DsmBrailleClient

DsmBrailleTranslator: DsmBrailleTranslator.o
	$(CC) DsmBrailleTranslator.o $(LDFLAGS) -L. -lesidedsm -o DsmBrailleTranslator

#Time modification

DsmTimeServer: DsmTimeServer.o
	$(CC) DsmTimeServer.o $(LDFLAGS) -L. -lesidedsm -o DsmTimeServer

DsmTimeClient: DsmTimeClient.o
	$(CC) DsmTimeClient.o $(LDFLAGS) -L. -lesidedsm -o DsmTimeClient

#

DsmServer.o: DsmServer.cc DsmServer.h DsmTypes.h
	$(CC) $(INCLUDE) -c DsmServer.cc

DsmTest.o: DsmTest.cc
	$(CC) $(INCLUDE) -c DsmTest.cc

#Matrix example

MatrixEvenAdder.o: MatrixEvenAdder.cc
	$(CC) $(INCLUDE) -c MatrixEvenAdder.cc
	
MatrixOddAdder.o: MatrixOddAdder.cc
	$(CC) $(INCLUDE) -c MatrixOddAdder.cc

#Time modification

DsmTimeServer.o: DsmTimeServer.cc
	$(CC) $(INCLUDE) -c DsmTimeServer.cc

DsmTimeClient.o: DsmTimeClient.cc
	$(CC) $(INCLUDE) -c DsmTimeClient.cc

#Proposal

#DsmBrailleServer.o: DsmBrailleServer.cc DsmBrailleServer.h
	#$(CC) $(INCLUDE) -c DsmBrailleServer.cc

DsmBrailleClient.o: DsmBrailleClient.cc
	$(CC) $(INCLUDE) -c DsmBrailleClient.cc

DsmBrailleTranslator.o: DsmBrailleTranslator.cc
	$(CC) $(INCLUDE) -c DsmBrailleTranslator.cc

clean:
	rm *.o
	rm *.so
	rm *.dll
	rm DsmServer DsmTest MatrixEvenAdder MatrixOddAdder DsmTimeServer DsmTimeClient  DsmBrailleClient DsmBrailleTranslator #DsmBrailleServer