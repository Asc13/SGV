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
    insertion(&(clients->idsByFirstLetter[(int) id[0] - ASCII]), id, NULL);
    clients->num_values++;
}


int searchClient(Clients clients, char* id) {
    return lookup(clients->idsByFirstLetter[(int) id[0] - ASCII], id);
}


int getNumClients(Clients clients) {
    return clients->num_values;    
}


char** getAllClients(Clients clients) {
    char** c = (char**) malloc(clients->num_values * sizeof(char*));
    
    int counter = 0;

    for(int i = 0; i < TAM; i++)
        getAllSeparated(clients->idsByFirstLetter[i], c, &counter);

    return c;
}