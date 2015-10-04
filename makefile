
### DEFINITIONS

CC=gcc
CFLAGS=-std=c99 -Werror -Wextra -pedantic-errors -g -Wall

LIBS=

OBJ= \
	Bin/Connection.o \
	Bin/TCPConnection.o \
	Bin/main.o

EXECUTABLE=NetGen

### EXECUTABLE STATEMENTS 

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(LIBS)

## Connection/
Bin/Connection.o : Connection/Connection.c Connection/Connection.h 
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

Bin/TCPConnection.o : Connection/TCPConnection.c Connection/TCPConnection.h
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

Bin/main.o : main.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)


## Clean
clean:
	rm -f $(OBJ) $(EXECUTABLE)
