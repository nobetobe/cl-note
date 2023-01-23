
all: note

note: main.c utils.o command_parser.o
	$(cc) -o ../note main.c utils.o command_parser.o

utils.o: utils.c utils.h
	$(cc) -c -o utils.o utils.c

command_parser.o: command_parser.c command_parser.h utils.h
	$(cc) -c -o command_parser.o command_parser.c
