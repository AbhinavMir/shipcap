CC = gcc
CFLAGS = -Wall -O2
TARGET = shipcap

all: $(TARGET)

$(TARGET): shipcap.c
	$(CC) $(CFLAGS) -o $(TARGET) shipcap.c

install: $(TARGET)
	cp $(TARGET) /usr/local/bin

uninstall:
	rm -f /usr/local/bin/$(TARGET)

clean:
	rm -f $(TARGET)
