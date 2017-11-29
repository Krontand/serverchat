#ifndef CLIENTSTORAGE_H
#define CLIENTSTORAGE_H

#include "ringbuffer.h"
#include "net_utils.h"

struct clients_array
{
    struct client *client[MAX_CLIENTS];
    int count;
};

struct client
{
    int sockfd;
    int writable;
    char addr[22];
    struct ringbuffer *buffer;
};

// Functions to work with struct clients_array
int delete_client(struct clients_array *clients, struct client *client);

struct client *add_client(struct clients_array *clients, int sockfd, sockaddr_in addr);

void init_client(struct client *client, int sockfd, sockaddr_in addr);
void free_client(struct client *client);

#endif // CLIENTSTORAGE_H
