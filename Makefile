# @file Makefile
# @author Corey Ford <fordco@sonoma.edu>

all:

# Documentation
doc:
	doxygen Doxyfile

clean:
	rm -rf *.o ocr