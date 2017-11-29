#ifndef queue_H
#define queue_H

#define DEFAULT_SIZE 1000000
#define REALLOC_COEF 1.5

struct queue
{
    char *data;
    int head;
    int tail;
    int count;
    int size;
};


void init_queue(struct queue *buf, int size);
void free_queue(struct queue *buf);

int push_queue(struct queue *buf, const char *data, int n);

// Just shifting head, there is no real data copying
int pop_queue(struct queue *buf, int n);

void realloc_queue(struct queue *buf);

// Move queue to the beginning of buffer
void shift_queue(struct queue *buf);

#endif // queue_H
