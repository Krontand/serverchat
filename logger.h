#ifndef LOGGER_H
#define LOGGER_H

void open_log(const char *path);

void write_log(const char *addr, const char *message);

void close_log();

#endif // LOGGER_H
