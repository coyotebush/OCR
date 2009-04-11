# @file Makefile
# @author Corey Ford <fordco@sonoma.edu>
# @date Spring 2009

# Primary target
all: ocr

# List all object files
OBJS = build/main.o build/TextPage.o build/TextLine.o \
	build/Grapheme.o build/EasyBMP.o

# Main program
ocr: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ocr $(OBJS)

# Application program
build/main.o: main.cpp TextPage.h
	$(CXX) $(CXXFLAGS) -c -o build/main.o main.cpp

# EasyBMP
build/EasyBMP.o: EasyBMP/EasyBMP.cpp EasyBMP/EasyBMP.h
	$(CXX) $(CXXFLAGS) -c -o build/EasyBMP.o EasyBMP/EasyBMP.cpp

# TextPage
build/TextPage.o: TextPage.cpp TextPage.h TextLine.h Grapheme.h
	$(CXX) $(CXXFLAGS) -c -o build/TextPage.o TextPage.cpp

# TextLine
build/TextLine.o: TextLine.cpp TextLine.h Grapheme.h
	$(CXX) $(CXXFLAGS) -c -o build/TextLine.o TextLine.cpp

# Grapheme
build/Grapheme.o: Grapheme.cpp Grapheme.h
	$(CXX) $(CXXFLAGS) -c -o build/Grapheme.o Grapheme.cpp

# General rules for classes
#build/%.o: %.cpp %.h
#	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Documentation
doc: *.cpp *.h
	doxygen Doxyfile

# Clean
clean-all: clean clean-doc

clean-doc: doc
	$(RM) -r doc/

clean:
	$(RM) -r build/*.o *.o ocr