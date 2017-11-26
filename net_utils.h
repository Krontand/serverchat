#ifndef UTILS_H
#define UTILS_H

#include "local.h"

struct clients_array
{
    int fd[MAX_CLIENTS];
    int count;
};

int setreuseaddr(int sockfd);

int delete_client(struct clients_array *clients, int sockfd);
int add_client(struct clients_array *clients, int sockfd);

int setnonblocking(int desc, int value);

int create_listen_tcp_socket(int port);

int send_msg_close(int sock, const char *msg);

int send_to_clients(const struct clients_array *clients, const char *message, int msg_len, int source_sock);

#endif // UTILS_H
