CC = gcc
CFLAGS = -Wall -Wno-unused-result -g

COMMON_SRCS = std_data/binary_tree/tree/tree.c std_data/binary_tree/node/node.c std_data/binary_tree/key_val_pair/key_val_pair.c std_data/vector/vector.c utils/utils.c file_reading/dir_read.c
MAIN_SRCS = main.c $(COMMON_SRCS)
INDEX_SRCS = index.c $(COMMON_SRCS)

MAIN_OBJS = $(MAIN_SRCS:.c=.o)
INDEX_OBJS = $(INDEX_SRCS:.c=.o)

all: main index

main: $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(MAIN_OBJS)

index: $(INDEX_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(INDEX_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJS) $(INDEX_OBJS) main index *.out

run_main:
	./main

run_index:
	./index

val_main:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./main

val_index:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./index
