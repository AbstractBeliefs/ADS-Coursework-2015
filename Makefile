CC = clang
CFLAGS = -std=c11 -Wall -D_POSIX_C_SOURCE=199309L
LFLAGS = -lm
SOURCES = src/main.c src/ClarkeWright.c
EXECUTABLE = CourseWork1
TESTDATA = data/rand00010prob.csv
OUTPUT = solution.csv
REPORT = report.pdf
OBJECTS = $(SOURCES:.c=.o)


# Core library
all: $(EXECUTABLE) $(REPORT)

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
report: $(REPORT)
$(REPORT): report/report.tex report/report.bib
	cd report && \
	pdflatex report.tex && \
	bibtex report && \
	pdflatex report.tex && \
	pdflatex report.tex		# Required to generate ToC


# Utility
clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(OUTPUT)
	rm -f report/*.aux report/*.toc report/*.log report/*.pdf report/*.bcf report/*.xml report/*.bbl report/*.blg


.PHONY: clean all run debug release
