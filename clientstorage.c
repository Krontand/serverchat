#include "clientstorage.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_client(struct client **client, int sockfd, struct sockaddr_in addr, char *nick)
{
    *client = malloc(sizeof(struct client));
    init_queue(&((*client)->buffer), DEFAULT_SIZE);
    (*client)->sockfd = sockfd;
    get_ip_port((*client)->addr, sizeof((*client)->addr), addr);
    memcpy((*client)->nick, nick, sizeof((*client)->nick));
    (*client)->writable = 0;
}

void free_client(struct client **client)
{
    free_queue(&((*client)->buffer));
    free(*client);
}

int delete_client(struct clients_array *clients, struct client *client)
{
    int i = 0;

    // Searching client in clients_array
    for (; i < clients->count && clients->client[i] != client; i++);
    // Not found
    if (i == clients->count)
        return -1;

    free_client(&(clients->client[i]));

    memmove(clients->client + i, clients->client + i + 1, sizeof(struct client*) * (clients->count - i - 1));
    clients->count--;

    return i;
}

struct client* add_client(struct clients_array *clients, int sockfd, struct sockaddr_in addr, char* nick)
{
    if (clients->count == MAX_CLIENTS)
        return NULL;

    struct client *newclient = NULL;
    init_client(&newclient, sockfd, addr, nick);

    clients->client[clients->count++] = newclient;
    return newclient;
}

