CC = clang
CFLAGS = -std=c11 -Wall -D_POSIX_C_SOURCE=199309L
LFLAGS = -lm
SOURCES = src/main.c src/ClarkeWright.c
EXECUTABLE = CourseWork1
TESTDATA = data/rand00010prob.csv
OUTPUT = solution.csv
OBJECTS = $(SOURCES:.c=.o)


# Core library
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Run
run: $(EXECUTABLE)
	./$(EXECUTABLE) $(TESTDATA) $(OUTPUT)

# Release (aka SANIC MODE)
release: CFLAGS += -O3
release: CC = gcc
release: clean $(EXECUTABLE)
	time ./$(EXECUTABLE) $(TESTDATA) $(OUTPUT)

# Debug
debug: CFLAGS += -ggdb -pg
debug: clean $(EXECUTABLE)
	gdb -tui --args $(EXECUTABLE) $(TESTDATA) $(OUTPUT)

# Report
# <blank>


# Utility
clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(OUTPUT)


.PHONY: clean run debug
