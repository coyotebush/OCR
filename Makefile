# @file Makefile
# @author Corey Ford <fordco@sonoma.edu>
# @date Spring 2009

# Primary target
all: ocr

# List all object files
OBJS = build/main.o build/reader.o build/easybmp.o

# Main program
ocr: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ocr $(OBJS)

# Application program
build/main.o: main.cpp Reader.h
	$(CXX) $(CXXFLAGS) -c -o build/main.o main.cpp

# EasyBMP
build/easybmp.o: EasyBMP/EasyBMP.cpp EasyBMP/EasyBMP.h
	$(CXX) $(CXXFLAGS) -c -o build/easybmp.o EasyBMP/EasyBMP.cpp

# General rules
build/%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Documentation
doc:
	doxygen Doxyfile

# Clean
clean-all: clean clean-doc

clean-doc: doc
	$(RM) -r doc/

clean:
	$(RM) -r build/*.o ocr