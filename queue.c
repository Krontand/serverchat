#include "queue.h"

#include <stdlib.h>
#include <string.h>

#include "utils.h"

void push_queue(struct queue *buf, const char *data, int n)
{
    while (buf->count + n > buf->size)
        realloc_queue(&buf);

    if (buf->tail + n > buf->size)
        shift_queue(buf);
    memcpy(buf->data + buf->tail, data, n);
    buf->tail += n;
    buf->count += n;
}

int pop_queue(struct queue *buf, int n)
{
    if (buf->count < n)
        n = buf->count;
    buf->head += n;
    buf->count -= n;
    return n;
}

void init_queue(struct queue **buf, int size)
{
    *buf = malloc(sizeof(struct queue));
    (*buf)->data = malloc(sizeof(char) * size);
    (*buf)->head = 0;
    (*buf)->tail = 0;
    (*buf)->count = 0;
    (*buf)->size = size;
}

void free_queue(struct queue **buf)
{
    free((*buf)->data);
    free(*buf);
}

void realloc_queue(struct queue **buf)
{
    (*buf)->data = realloc((*buf)->data, (*buf)->size * REALLOC_COEF);
    if (!((*buf)->data))
        err_quit("realloc_queue");
    (*buf)->size = (*buf)->size * REALLOC_COEF;
}

void shift_queue(struct queue *buf)
{
    memmove(buf->data, buf->data + buf->head, buf->tail - buf->head);
    buf->tail = buf->tail - buf->head;
    buf->head = 0;
}

char* top(struct queue *buf)
{
    return buf->data + buf->head;
}
