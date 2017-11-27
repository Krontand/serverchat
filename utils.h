#ifndef UTILS_H
#define UTILS_H

void daemonize(const char *cmd);

int already_running(void);

int ignore_signal(int signal);

void err_quit(const char *msg);

// Write current time to string (HH:MM:SS)
int get_time(char *timebuf, int size);

#endif // UTILS_H
