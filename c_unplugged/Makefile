CC = gcc
CFLAGS = -Wall -Wextra -I./headers

SRC = src/assigment2.c src/playlist.c src/library.c src/command_processor.c
OBJ = obj/assigment2.o obj/playlist.o obj/library.o obj/command_processor.o

TARGET = music_player

all: obj $(TARGET)

obj:
	mkdir -p obj

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o $(TARGET)