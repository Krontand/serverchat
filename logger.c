#include "logger.h"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

static int logfile;

void open_log(const char* path)
{
    logfile = open(path, O_APPEND | O_WRONLY | O_CREAT, 0666);
}

void write_log(const char *message)
{
    write(logfile, message, strlen(message));
}

void close_log()
{
    close(logfile);
}
