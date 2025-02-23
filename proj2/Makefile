CC = gcc
CFLAGS = -std=c99 -Wall -Werror -g

SOURCES = Tree.c main.c RDP.c TDP.c Stack.c 
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = proj2

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean