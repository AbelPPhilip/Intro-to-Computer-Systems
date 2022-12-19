CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Werror -Wshadow -Wwrite-strings \
-pedantic-errors -fstack-protector-all
PROGS = d8sh
all: d8sh

clean:
	rm -f d8sh ./*~ ./*.o

d8sh: d8sh.o executor.o parser.tab.o lexer.o
	$(CC) -lreadline d8sh.o executor.o parser.tab.o lexer.o -o d8sh

d8sh.o: d8sh.c executor.h lexer.h
	$(CC) $(CFLAGS) -c d8sh.c

lexer.o: lexer.c
	$(CC) $(CFLAGS) -c lexer.c

executor.o: executor.c executor.h command.h
	$(CC) $(CFLAGS) -c executor.c

parser.tab.o: parser.tab.c command.h
	$(CC) $(CFLAGS) -c parser.tab.c







