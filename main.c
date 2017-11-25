#include <stdio.h>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "utils.h"
#include "logger.h"

int main()
{
    open_log(LOG_FILE);

    signal(SIGPIPE, SIG_IGN);

    int serv_port = 5000;

    int listen_sock = create_listen_tcp_socket(serv_port);

    int epollfd = epoll_create(MAX_EVENTS);

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = listen_sock;   
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) < 0)
    {
        perror("Epoll fd add");
        exit(EXIT_FAILURE);
    }

    socklen_t addrlen;
    // Массив готовых дескрипторов
    struct epoll_event events[MAX_EVENTS];

    struct clients_array clients;
    clients.count = 0;

    for (;;)
    {
        int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == listen_sock)
            {
                struct sockaddr cliaddr;
                int conn_sock = accept(listen_sock, (struct sockaddr*) &cliaddr, &addrlen);
                if (conn_sock == -1)
                {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                setnonblocking(conn_sock, 1);
                setreuseaddr(conn_sock);

                if (clients.count < MAX_CLIENTS)
                {
                    ev.events = EPOLLIN | EPOLLRDHUP | EPOLLET;
                    ev.data.fd = conn_sock;
                    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1)
                    {
                        perror("epoll_ctl: conn_sock");
                        exit(EXIT_FAILURE);
                    }

                    add_client(&clients, conn_sock);
                }
                else
                {
                    send_msg_close(conn_sock, MSG_NO_PLACES);
                }
            }
            else
            {
                if (events[n].events & EPOLLHUP ||
                        events[n].events & EPOLLERR ||
                        events[n].events & EPOLLRDHUP)
                {
                    delete_client(&clients, events[n].data.fd);
                    close(events[n].data.fd, SHUT_RDWR);
                }
                else if (events[n].events & EPOLLIN)
                {
                    int event_socket = events[n].data.fd;
                    char received_msg[MAX_MSG_LEN];
                    int receivedbytes = 0;
                    while (receivedbytes <= 0)
                           receivedbytes = recv(event_socket, received_msg, MAX_MSG_LEN, 0);

                    write_log(received_msg);

                    send_to_clients(&clients, received_msg, receivedbytes, event_socket);
                }

            }
        }
    }

    return 0;
}
