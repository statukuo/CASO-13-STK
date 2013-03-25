# Makefile
# author: dipina@eside.deusto.es
CC=g++
LDFLAGS=-L../util -lm -lpthread -lesidesocket -lesidethread 
INCLUDE=-I../util

main: EchoTcpListener EchoTcpClient NameServer NameClient BrailleTcpListener BrailleTcpClient

EchoTcpListener: EchoServerThread.o EchoTcpListener.o
	$(CC) EchoServerThread.o EchoTcpListener.o $(LDFLAGS) -o EchoTcpListener

EchoTcpClient: EchoTcpClient.o
	$(CC) EchoTcpClient.o $(LDFLAGS) -o EchoTcpClient

BrailleTcpListener: BrailleServerThread.o BrailleTcpListener.o
	$(CC) BrailleServerThread.o BrailleTcpListener.o $(LDFLAGS) -o BrailleTcpListener

BrailleTcpClient: BrailleTcpClient.o
	$(CC) BrailleTcpClient.o $(LDFLAGS) -o BrailleTcpClient

NameServer: NameServer.o
	$(CC) NameServer.o $(LDFLAGS) -lesidesqlite -o NameServer

NameClient: NameClient.o
	$(CC) NameClient.o $(LDFLAGS) -o NameClient

EchoServerThread.o: EchoServerThread.cc EchoServerThread.h
	$(CC) $(INCLUDE) -c EchoServerThread.cc

EchoTcpListener.o: EchoTcpListener.cc
	$(CC) $(INCLUDE) -c EchoTcpListener.cc

EchoTcpClient.o: EchoTcpClient.cc
	$(CC) $(INCLUDE) -c EchoTcpClient.cc

BrailleServerThread.o: BrailleServerThread.cc BrailleServerThread.h
	$(CC) $(INCLUDE) -c BrailleServerThread.cc

BrailleTcpListener.o: BrailleTcpListener.cc
	$(CC) $(INCLUDE) -c BrailleTcpListener.cc

BrailleTcpClient.o: BrailleTcpClient.cc
	$(CC) $(INCLUDE) -c BrailleTcpClient.cc

NameServer.o: NameServer.cc NameServer.h
	$(CC) $(INCLUDE) -c NameServer.cc

NameClient.o: NameClient.cc 
	$(CC) $(INCLUDE) -c NameClient.cc

clean:
	rm *.o
	rm EchoTcpListener EchoTcpClient NameServer NameClient BrailleTcpListener BrailleTcpClient
	rm *.exe
