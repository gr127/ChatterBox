all: client_module.o client.o 
	gcc client_module.o client.o -o hat -lpthread
client_module.o: client_module.c client_module.h
	gcc -c client_module.c
client.o: client.c client_module.h
	gcc -c client.c
