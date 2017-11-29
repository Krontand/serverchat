#include "clientstorage.h"

void init_client(struct client *client, int sockfd, sockaddr_in addr)
{
    client = malloc(sizeof(struct client));
    initbuffer(client->buffer, DEFAULT_SIZE);
    client->sockfd = sockfd;
    get_ip_port(client->addr, sizeof(client->addr), addr);
    client->writable = 0;
}

int delete_client(struct clients_array *clients, struct client *client)
{
    int i = 0;

    // Searching client in clients_array
    for (; i < clients->count && clients->client[i] != client; i++);
    // Not found
    if (i == clients->count)
        return -1;

    free_client(clients->client[i]);

    memmove(clients->fd + i, clients->fd + i + 1, clients->count - i - 1);
    clients->count--;

    return i;
}

struct client* add_client(struct clients_array *clients, int sockfd, sockaddr_in addr)
{
    if (clients->count == MAX_CLIENTS)
        return -1;

    struct client *newclient = NULL;
    init_client(newclient, sockfd, addr);

    clients->fd[clients->count++] = newclient;
    return newclient;
}

void free_client(struct client *client)
{
    freebuffer(client->buffer);
    free(client);
}
