CC=gcc
LIBRARIES=-lraylib
LIBCHUNK_DIR=libchunk
BUILD_DIR=build
build: main.c libchunk/chunk.c
	mkdir -p $(BUILD_DIR)
	$(CC) main.c $(LIBCHUNK_DIR)/chunk.c $(LIBRARIES) -o $(BUILD_DIR)/game
run:
	./$(BUILD_DIR)/game
clean:
	rm $(BUILD_DIR)/game