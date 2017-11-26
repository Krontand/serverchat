CC=gcc

CFLAGS = -Wall

TARGET = chatserver

PREFIX = /usr/local/bin

SRCS = main.c net_utils.c utils.c logger.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
 
.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
