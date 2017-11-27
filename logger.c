#include "logger.h"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "net_utils.h"
#include "utils.h"

static int logfile;

void open_log(const char *path)
{
    logfile = open(path, O_APPEND | O_WRONLY | O_CREAT, 0666);
}

void write_log(const char *addr, const char *message)
{
    const int buf_size = MAX_MSG_LEN + 50;
    char buf[buf_size];

    char timebuf[30];
    get_time(timebuf, 30);

    int len = snprintf(buf, buf_size, "[%s] [%s] %s", timebuf, addr, message);
    if (len > buf_size)
        len = buf_size;

    write(logfile, buf, len);
}

void close_log()
{
    close(logfile);
}
