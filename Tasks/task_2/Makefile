TARGET = exec
CC = gcc
CFLAGS = -c -Wall
LDFLAGS = 
LDLIBS = -lncurses
all: $(TARGET) clear

$(TARGET): *.o
	$(CC) $(LDFLAGS) *.o $(LDLIBS) -o $(TARGET)

*.c.o: 
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -rf *.o	