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

# Primary target
all: ocr

# all object files
objs = build/main.o build/Page.o build/Line.o build/Grapheme.o\
 build/EasyBMP.o build/OCR_common.o build/Font.o

# Main program
ocr: $(objs)
	$(CXX) $(objs) -o ocr $(CXXFLAGS) $(LDFLAGS)

# Application program
build/main.o: main.cpp Page.h Line.h Grapheme.h OCR.h Font.h
	$(CXX) main.cpp -c -o build/main.o $(CPPFLAGS) $(CXXFLAGS)

# EasyBMP
build/EasyBMP.o: EasyBMP/EasyBMP.cpp EasyBMP/EasyBMP.h
	$(CXX) EasyBMP/EasyBMP.cpp -c -o build/EasyBMP.o $(CPPFLAGS) $(CXXFLAGS)

# Page
build/Page.o: Page.cpp Page.h Line.h Grapheme.h OCR.h Font.h
	$(CXX) Page.cpp -c -o build/Page.o $(CPPFLAGS) $(CXXFLAGS)

# Line
build/Line.o: Line.cpp Line.h Grapheme.h OCR.h Font.h
	$(CXX) Line.cpp -c -o build/Line.o $(CPPFLAGS) $(CXXFLAGS)

# Grapheme
build/Grapheme.o: Grapheme.cpp Grapheme.h OCR.h Font.h
	$(CXX) Grapheme.cpp -c -o build/Grapheme.o $(CPPFLAGS) $(CXXFLAGS)

# OCR globals
build/OCR_common.o: OCR.cpp OCR.h
	$(CXX) OCR.cpp -c -o build/OCR_common.o  $(CPPFLAGS) $(CXXFLAGS)

# Font
build/Font.o: Font.cpp Font.h
	$(CXX) Font.cpp -c -o build/Font.o $(CPPFLAGS) $(CXXFLAGS)

# Documentation
doc: *.cpp *.h
	doxygen Doxyfile

# Clean
clean-all: clean clean-doc

clean-doc: doc
	$(RM) -r doc/

clean:
	$(RM) -r build/*.o *.o ocr
