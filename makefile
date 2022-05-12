# 2022 Vincent Sivadon <vincent.sivadon@ens.uvsq.fr>

CC = gcc

TARGET  = lib/libTSP.so
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
INC_DIR = ./include/
CFLAGS  = -I$(INC_DIR) -ldl -lm -fPIC -Ofast

all: TSP

$(TARGET): $(OBJECTS)
	$(CC) -fPIC -g -o $(TARGET) $(OBJECTS) -shared

TSP: $(TARGET) TSP.c

clean:
	rm -f lib/*
	rm -f src/*.o
	rm -f TSP