# @file Makefile
# @author Corey Ford <fordco@sonoma.edu>

# Main
all: ocr

# Compilation flags
flags = -g -Wall

# Main program
ocr: app.o reader.o
	g++ $(flags) -o ocr app.o reader.o

# Application program
app.o: main.cpp Reader.h
	g++ $(flags) -c -o app.o main.cpp

# Reader class
reader.o: Reader.cpp Reader.h
	g++ $(flags) -c -o reader.o Reader.cpp

# Documentation
doc:
	doxygen Doxyfile

# Clean
clean:
	rm -rf *.o ocr