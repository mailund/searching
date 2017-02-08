
all: search

search: search.c
	cc -coverage search.c -o search

test: search test.sh
	./test.sh