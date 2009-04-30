/**
 * @file learn.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief An application program using the OCR library to create font data files.
 * @version $Id$
 */
/*
 * Copyright 2009 Corey Ford
 *
 * This file is part of Omophagic Content Reader.
 *
 * Omophagic Content Reader is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Omophagic Content Reader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Omophagic Content Reader.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "EasyBMP/EasyBMP.h"
#include "Font.h"
#include "Page.h"

const std::string letters =
        "./0123456789?@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
int main(int argc, char * argv[])
{
	using OCR::Font;

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <font image>...\n";
		return 1;
	}

	// Average symbol information
	std::map<char, Font::Symbol> average;
	// Image
	BMP img;

	// Load a non-existent font
	OCR::Font bogus("BOGUS");

	// Load each line and read its statistics
	for (int fileNum = 1; fileNum < argc; ++fileNum)
	{
		// Create line
		img.ReadFromFile(argv[fileNum]);
		OCR::Line line(img, bogus);
		// Create vector for symbol info
		std::vector<Font::Symbol> symbols;
		symbols.reserve(letters.size());
		// Do the reading
		line.Read(&symbols);
		// Loop through and add to the "average"
		std::vector<Font::Symbol>::iterator itr = symbols.begin();
		for (unsigned charIndex = 0; itr != symbols.end() && charIndex
		        < letters.size(); ++itr, ++charIndex)
		{
			average[letters[charIndex]] += *itr;
		}

		// DEBUG - dump symbol information
		/*std::cout << std::endl;
		for (std::map<char, Font::Symbol>::iterator itr = average.begin(); itr
		        != average.end(); ++itr)
		{
			std::cout << itr->first << ' ' << itr->second << std::endl;
		}*/
	}

	// Now divide the total statistics by the number of lines,
	// and print information
	for (std::map<char, Font::Symbol>::iterator itr = average.begin(); itr
	        != average.end(); ++itr)
	{
		itr->second /= (argc - 1);
		std::cout << itr->first << ' ' << itr->second << std::endl;
	}

	return 0;
}
