
CC = gcc
CFLAGS = -fPIC -Wall
LDFLAGS = -shared -ldl


TARGET = libmy_readdir.so


SRC = myreadlib.c


all: $(TARGET)


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)


clean:
	rm -f $(TARGET)

.PHONY: all clean
