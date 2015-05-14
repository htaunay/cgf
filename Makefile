CC = g++
CFLAGS = -std=c++11 -Wall
INCLUDES = -Isrc/include/
SRCS = $(wildcard src/*.cpp)
TARGET = corner

build: $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

run:
	@./$(TARGET)

clean:
	@rm -f *.o $(TARGET)

check: clean build
	@valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

build_and_run: clean build run
