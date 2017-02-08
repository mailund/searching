
all: search

search: search.c
	cc search.c -o search

test: search test.sh
	./test.sh