#include "clients.h"
#include "rbt.h"

struct clients {
    Node* idsByFirstLetter;
    int num_values;
};



Clients initClients() {
    Clients clients = (Clients) malloc(sizeof(struct clients));
    clients->idsByFirstLetter = (Node*) malloc(TAM * sizeof(Node));
    clients->num_values = 0;

    for(int i = 0; i < TAM; i++)
        (clients->idsByFirstLetter)[i] = NULL;

    return clients;
}


void addClient(Clients clients, char* id) {
    int index = (int) id[0] - ASCII;

    insertion(&(clients->idsByFirstLetter[index]), id);
    clients->num_values++;
}


int searchClient(Clients clients, char* id) {
    int index = (int) id[0] - ASCII;

    return lookup(clients->idsByFirstLetter[index], id);
}


int getNumClients(Clients clients) {
    return clients->num_values;    
}