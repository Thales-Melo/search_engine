CC = gcc
CFLAGS = -Wall -Wno-unused-result -g

SRCS = main.c std_data/hash/hash.c std_data/vector/vector.c utils/utils.c 
OBJS = $(SRCS:.c=.o)

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) main *.out

run:
	./main

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./main