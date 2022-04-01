CC=gcc

SRC_FILES=./src/*
HDR_FILES=./include/*

SRC_DIR=./src/
HDR_DIR=./include/
LIB_DIR=./lib/
BIN_DIR=./bin/

TSP: $(SRC_FILES) $(HDR_FILES)
	$(CC) -I$(HDR_DIR) -fPIC -shared $(SRC_FILES) -o $(LIB_DIR)libTSP.so -ldl

Initialization: tests/Initialization.c
	$(CC) -I$(HDR_DIR) -L$(LIB_DIR) -Wl,-rpath=$(LIB_DIR) $< -o $(BIN_DIR)$@ -lTSP

runTests: bin/*
	./bin/
	


# ====================== #

clean:
	rm -rf bin/* lib/*

.PHONY:
	clean