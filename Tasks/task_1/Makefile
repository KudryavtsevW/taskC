TARGET = exec
CC = gcc
CFLAGS = -c
LDFLAGS = 
LDLIBS = 
all: $(TARGET) clear

$(TARGET): *.o
	$(CC) $(LDFLAGS) *.o $(LDLIBS) -o $(TARGET)

*.c.o: 
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -rf *.o	