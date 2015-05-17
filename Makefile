CC = g++
CFLAGS = -std=c++11 -Wall -m64
INCLUDES = -Isrc/include/
SRCS = $(filter-out src/Main.cpp, $(wildcard src/*.cpp))
TARGET = opposites

CORNER_TEST = test/TestCornerTable.cpp
CHE_TEST = test/TestCHETable.cpp
TEST_RUNNER = run-tests

default: clean
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) src/Main.cpp -o $(TARGET)

corner-table-test: clean
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(CORNER_TEST) -o $(TEST_RUNNER)
	@valgrind ./$(TEST_RUNNER)

che-table-test: clean
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(CHE_TEST) -o $(TEST_RUNNER)
	@valgrind ./$(TEST_RUNNER)

clean:
	@rm -f *.o $(TEST_RUNNER)
