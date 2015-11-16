CC = clang
CFLAGS = -std=c11 -Wall
LFLAGS = -lm
SOURCES = src/main.c src/ClarkeWright.c
EXECUTABLE = CourseWork1
TESTDATA = data/rand00010prob.csv
OBJECTS = $(SOURCES:.c=.o)


# Core library
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Run
run: $(EXECUTABLE)
	./$(EXECUTABLE) $(TESTDATA)

# Debug
debug: CFLAGS += -ggdb
debug: clean $(EXECUTABLE)
	gdb --args $(EXECUTABLE) $(TESTDATA)

# Report
# <blank>


# Utility
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)


.PHONY: clean test debug
