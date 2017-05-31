
all: search

search: main.c
	cc -coverage main.c -o search

test: search test.sh
	./test.sh