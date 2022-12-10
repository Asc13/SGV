#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef Clients_H
#define Clients_H

typedef struct clients* Clients;

#define ASCII 65
#define TAM 26


Clients initClients();

void addClient(Clients clients, char* id);

int searchClient(Clients clients, char* id);

int getNumClients(Clients clients);

#endif