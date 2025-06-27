CC=gcc
LIBRARIES=-lraylib -lm
LIBCHUNK_DIR=libchunk
GUI_DIR=GUI
BUILD_DIR=build
UI_UX_DIR=UI_UX
build: main.c libchunk/*.c GUI/*.c UI_UX/*.c
	mkdir -p $(BUILD_DIR)
	$(CC) -g main.c $(LIBCHUNK_DIR)/*.c $(GUI_DIR)/*.c $(UI_UX_DIR)/*.c  $(LIBRARIES) -o $(BUILD_DIR)/game
run:
	./$(BUILD_DIR)/game
clean:
	rm $(BUILD_DIR)/game