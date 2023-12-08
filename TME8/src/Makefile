CC=g++
FLAGS=-Wall -std=c++1y -g3 -O0

all : mainClient mainServeur

mainClient : Socket.o mainClient.cpp
	$(CC) $(FLAGS) -o mainClient Socket.o mainClient.cpp

mainServeur : ServerSocket.o mainServeur.cpp
	$(CC) $(FLAGS) -o mainServeur ServerSocket.o Socket.o mainServeur.cpp

Socket.o : Socket.h Socket.cpp
	$(CC) $(FLAGS) -c Socket.o Socket.cpp

ServerSocket.o : ServerSocket.h ServerSocket.cpp
	$(CC) $(FLAGS) -c ServerSocket.o ServerSocket.h ServerSocket.cpp


