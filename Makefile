CC = clang
CFLAGS = -std=c11 -Wall
SOURCES = src/main.c
EXECUTABLE = CourseWork1
OBJECTS = $(SOURCES:.c=.o)


# Core library
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Run
run: $(EXECUTABLE)
	./$(EXECUTABLE)


# Report
# <blank>


# Utility
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)


.PHONY: clean test
