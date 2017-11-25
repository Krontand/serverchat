#include "utils.h"

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/ip.h>

#include "local.h"

int setnonblocking(int desc, int value)
{
    int oldflags = fcntl(desc, F_GETFL, 0);

    if (oldflags == -1)
        return -1;

    if (value != 0)
        oldflags |= O_NONBLOCK;
    else
        oldflags &= ~O_NONBLOCK;

    return fcntl(desc, F_SETFL, oldflags);
}

int create_listen_tcp_socket(int port)
{
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0)
    {
        perror("Socket creation");
        exit(EXIT_FAILURE);
    }


    setnonblocking(listen_sock, 1);

    setreuseaddr(listen_sock);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(listen_sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Socket bind");
        exit(EXIT_FAILURE);
    }

    if (listen(listen_sock, BACK_LOG) < 0)
    {
        perror("Socket listen");
        exit(EXIT_FAILURE);
    }
    return listen_sock;
}

int send_msg_close(int sock, const char *msg)
{
    send(sock, msg, strlen(msg), 0);
    shutdown(sock, SHUT_WR);
    char buffer[4000];
    for (;;)
    {
        int res = read(sock, buffer, 4000);
        if(res < 0)
        {
            perror("reading before close");
            exit(1);
        }
        if(!res)
            break;
    }
    close(sock);
}

int delete_client(struct clients_array *clients, int sockfd)
{
    int i = 0;
    for (; i < clients->count && clients->fd[i] != sockfd; i++);

    if (i == clients->count)
        return -1;
    memmove(clients->fd + i, clients->fd + i + 1, clients->count - i - 1);
    clients->count--;
    return i;
}

int add_client(struct clients_array *clients, int sockfd)
{
    if (clients->count == MAX_CLIENTS)
        return -1;
    clients->fd[clients->count++] = sockfd;
    return 0;
}

int send_to_clients(const struct clients_array *clients, const char *message, int msg_len, int source_sock)
{
    for (int i = 0; i < clients->count; i++)
    {
        if (clients->fd[i] != source_sock)
        {
            int sentbytes = 0;
            while (sentbytes < msg_len)
                sentbytes = send(clients->fd[i], message + sentbytes, msg_len - sentbytes, 0);
        }
    }
    return 0;
}

int setreuseaddr(int sockfd)
{
    int enable = 1;
    return setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&enable, sizeof(enable));
}
