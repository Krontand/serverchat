#ifndef UTILS_H
#define UTILS_H

#include <arpa/inet.h>

#include "local.h"



// Set SO_REUSEADDR option
int setreuseaddr(int sockfd);

int setnonblocking(int desc, int value);

// Functions to work with struct clients_array
int delete_client(struct clients_array *clients, int sockfd);
int add_client(struct clients_array *clients, int sockfd);

int create_listen_tcp_socket(int port);

// Send message to socket and close connection correctly
int send_msg_close(int sock, const char *msg);

// Send message to all clients except source_sock
int send_to_clients(const struct clients_array *clients, const char *message, int msg_len, int source_sock);

// Write socket ip and port to string
int get_ip_port(char *buf, int buf_size, struct sockaddr_in addr);


#endif // UTILS_H
