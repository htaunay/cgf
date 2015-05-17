CC = g++
CFLAGS = -std=c++11 -Wall -m64
INCLUDES = -Isrc/include/
SRCS = $(wildcard src/*.cpp test/*cpp)
TARGET = run-tests

build: $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

run:
	@./$(TARGET)

clean:
	@rm -f *.o $(TARGET)

check: clean build
	@valgrind ./$(TARGET) test/input/hexagon.txt

build_and_run: clean build run
