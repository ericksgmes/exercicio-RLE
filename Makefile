CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCS = main.c RLE.c
HEADERS = RLE.h
OBJS = $(SRCS:.c=.o)
TARGET = main
all: $(TARGET)
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)
