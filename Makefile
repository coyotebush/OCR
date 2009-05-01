# @file Makefile
# @author Corey Ford <fordco@sonoma.edu>
# @date Spring 2009
# @brief The makefile for the OCR project
# @version $Id$

#
# Copyright 2009 Corey Ford
#
# This file is part of Omophagic Content Reader.
#
# Omophagic Content Reader is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Omophagic Content Reader is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Omophagic Content Reader.
# If not, see <http://www.gnu.org/licenses/>.
#

all: ocr ocr-learn

# all OCR library files
ocrobjs = build/Page.o build/Line.o build/Grapheme.o\
 build/EasyBMP.o build/OCR_common.o build/Font.o

# Main program
ocr: build/main.o $(ocrobjs)
	$(CXX) build/main.o $(ocrobjs) -o ocr $(CXXFLAGS) $(LDFLAGS)

# Learning program
ocr-learn: build/learn.o $(ocrobjs)
	$(CXX) build/learn.o $(ocrobjs) -o ocr-learn $(CXXFLAGS) $(LDFLAGS)





# Application program
build/main.o: src/main.cpp src/Page.h src/Line.h src/Grapheme.h src/OCR.h src/Font.h
	$(CXX) src/main.cpp -c -o build/main.o $(CPPFLAGS) $(CXXFLAGS)

# Learning application
build/learn.o: src/learn.cpp src/Page.h src/Line.h src/Grapheme.h src/OCR.h src/Font.h
	$(CXX) src/learn.cpp -c -o build/learn.o $(CPPFLAGS) $(CXXFLAGS)

# EasyBMP
build/EasyBMP.o: src/EasyBMP/EasyBMP.cpp src/EasyBMP/EasyBMP.h
	$(CXX) src/EasyBMP/EasyBMP.cpp -c -o build/EasyBMP.o $(CPPFLAGS) $(CXXFLAGS)

# Page
build/Page.o: src/Page.cpp src/Page.h src/Line.h src/Grapheme.h src/OCR.h src/Font.h
	$(CXX) src/Page.cpp -c -o build/Page.o $(CPPFLAGS) $(CXXFLAGS)

# Line
build/Line.o: src/Line.cpp src/Line.h src/Grapheme.h src/OCR.h src/Font.h
	$(CXX) src/Line.cpp -c -o build/Line.o $(CPPFLAGS) $(CXXFLAGS)

# Grapheme
build/Grapheme.o: src/Grapheme.cpp src/Grapheme.h src/OCR.h src/Font.h
	$(CXX) src/Grapheme.cpp -c -o build/Grapheme.o $(CPPFLAGS) $(CXXFLAGS)

# OCR globals
build/OCR_common.o: src/OCR.cpp src/OCR.h
	$(CXX) src/OCR.cpp -c -o build/OCR_common.o  $(CPPFLAGS) $(CXXFLAGS)

# Font
build/Font.o: src/Font.cpp src/Font.h
	$(CXX) src/Font.cpp -c -o build/Font.o $(CPPFLAGS) $(CXXFLAGS)

# Documentation
doc: src/*.cpp src/*.h
	doxygen Doxyfile

# Clean
clean-all: clean clean-doc

clean-doc:
	$(RM) -r doc/*

clean:
	$(RM) -r build/*.o *.o ocr
