CC=gcc
LIBRARIES=-lraylib -lm
LIBCHUNK_DIR=libchunk
BUILD_DIR=build
build: main.c libchunk/*.c
	mkdir -p $(BUILD_DIR)
	$(CC) -g main.c $(LIBCHUNK_DIR)/*.c $(LIBRARIES) -o $(BUILD_DIR)/game
run:
	./$(BUILD_DIR)/game
clean:
	rm $(BUILD_DIR)/game