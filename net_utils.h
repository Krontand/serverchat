#ifndef UTILS_H
#define UTILS_H

#include <arpa/inet.h>

#include "clientstorage.h"
#include "local.h"

// Set SO_REUSEADDR option
int setreuseaddr(int sockfd);
// Установка сокета в неблокирующий режим
int setnonblocking(int desc, int value);
// Создание слушающего сокета
int create_listen_tcp_socket(int port);

// Send message to socket and close connection correctly
void send_msg_close(int sock, const char *msg);

// Buffering message to all clients except source_sock and trying to send it
int send_to_clients(struct clients_array *clients, const char *message, int msg_len, int source_sock);

// Write socket ip and port to string
int get_ip_port(char *buf, int buf_size, struct sockaddr_in addr);

// Отослать сообщения из очереди клиенту
void flush_queue(struct client *client);

#endif // UTILS_H
