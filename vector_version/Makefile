CC = gcc
CFLAGS = -Wall -Wno-unused-result -g

COMMON_SRCS = std_data/vector/vector.c utils/utils.c index-program/domain/file_reading/dir_read.c collection/collection.c index-program/domain/build_index/build_index.c word/word.c document/document.c search_program/domain/engine/engine.c
SEARCH_SRCS = search.c $(COMMON_SRCS)
INDEX_SRCS = index.c $(COMMON_SRCS)

SEARCH_OBJS = $(SEARCH_SRCS:.c=.o)
INDEX_OBJS = $(INDEX_SRCS:.c=.o)

all: search index

search: $(SEARCH_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SEARCH_OBJS)

index: $(INDEX_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(INDEX_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SEARCH_OBJS) $(INDEX_OBJS) search index *.out

run_search:
	./search

run_index:
	./index

val_search:
	valgrind ./search

val_index:
	valgrind ./index
