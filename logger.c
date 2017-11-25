#include "logger.h"

#include <stdio.h>

static int logfile;

void open_log(const char* path)
{
    logfile = fopen(path, "a");
}


void write_log(const char *message)
{
    fprintf(logfile, "%s", message);
    fflush(logfile);
}

void close_log()
{
    fclose(logfile);
}
