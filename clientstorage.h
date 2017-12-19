#ifndef CLIENTSTORAGE_H
#define CLIENTSTORAGE_H

#include "queue.h"
#include "net_utils.h"
#include "local.h"

struct clients_array
{
    struct client *client[MAX_CLIENTS];
    int count;
};

struct client
{
    int sockfd;
    int writable;
    char nick[20];
    char addr[22];
    char id[40];
    struct queue *buffer;
};

// Functions to work with struct clients_array
int delete_client(struct clients_array *clients, struct client *client);
// Добаление нового клиента в массив клиентов (возвращает указатель на данные клиента для хранения в epoll)
struct client *add_client(struct clients_array *clients, int sockfd, struct sockaddr_in addr, char* nick);
// Инициализация структуры клиента
void init_client(struct client **client, int sockfd, struct sockaddr_in addr, char *nick);
// Освобождение структуры клиента
void free_client(struct client **client);

#endif // CLIENTSTORAGE_H
