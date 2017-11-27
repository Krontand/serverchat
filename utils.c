#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <errno.h>
#include <time.h>

#define LOCKFILE "/var/run/chatserver.pid"

int ignore_signal(int signal)
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    return sigaction(signal, &sa, NULL);
}

void daemonize(const char *cmd)
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;

    umask(0);

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_quit("getrlimit (daemonize)");

    if ((pid = fork()) < 0)
        err_quit("fork (daemonize)");

    else if (pid != 0)
        exit(0);

    setsid();

    if (ignore_signal(SIGHUP) < 0)
        err_quit("sighup ignore (daemonize)");

    if (chdir("/") < 0)
        err_quit("chdir (daemonize)");

    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++)
        close(i);

    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

}

int already_running(void)
{
    int fd;
    char buf[16];
    fd = open(LOCKFILE, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd < 0)
    {
        printf("Невозможно открыть %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    if (fcntl(fd, F_SETLKW, &lock) < 0)
    {
        if (errno == EACCES || errno == EAGAIN)
        {
            close(fd);
            return(1);
        }
        printf("Невозможно установить блокировку на %s: %s",
        LOCKFILE, strerror(errno));
        exit(1);
    }
    ftruncate(fd, 0);
    snprintf(buf, 16, "%ld", (long)getpid());
    write(fd, buf, strlen(buf)+1);
    return(0);
}


void err_quit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}


int get_time(char *timebuf, int size)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return snprintf(timebuf, size, "%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);
}
