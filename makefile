CC=gcc

SRC_FILES=./src/*
HDR_FILES=./include/*

SRC_DIR=./src/
HDR_DIR=./include/
LIB_DIR=./lib/
BIN_DIR=./bin/

TSP: main.c $(SRC_FILES) $(HDR_FILES)
	$(CC) -g -I$(HDR_DIR) $< $(SRC_FILES) -o $@	

# ====================== #

clean:
	rm -rf TSP

.PHONY:
	clean