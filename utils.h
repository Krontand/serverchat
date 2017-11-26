#ifndef UTILS_H
#define UTILS_H

void daemonize(const char *cmd);

int already_running(void);

int ignore_signal(int signal);

void err_quit(const char *msg);

#endif // UTILS_H
