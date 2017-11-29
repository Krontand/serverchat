#include <queue.h>

int push_queue(struct queue *buf, const char *data, int n)
{
    while (buf->count + n > buf->size)
        realloc_queue(buf);

    if (buf->tail + n > buf->size)
        shiftqueue(buf);
    memcpy(buf->data[buf->tail], data, n);
    buf->count += n;
    return n;
}

int pop_queue(queue *buf, int n)
{
    if (buf->count < n)
        n = buf->count;
    buf->head += n;
    buf->count -= n;
    return n;
}

void init_queue(struct queue *buf, int size)
{
    buf->data = malloc(sizeof(char) * size);
    buf->head = 0;
    buf->tail = 0;
    buf->count = 0;
    buf->size = size;
}

void free_queue(struct queue *buf)
{
    free(buf->data);
    free(buf);
}

void realloc_queue(struct queue *buf)
{
    realloc(buf->data, buf->size * REALLOC_COEF);
    if (!(buf->data))
        err_quit("realloc_queue");
}

void shift_queue(struct queue *buf)
{
    memmove(buf->data, buf->data + buf->head, buf->tail - buf->head);
}
