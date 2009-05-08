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
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "EasyBMP/EasyBMP.h"
#include "Font.h"
#include "Page.h"

/**
 * All supported characters.
 *
 * The input file should contain these characters in order,
 * or any initial part of this string.
 */
const std::string ALPHABET =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,?!/@_";

int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " <font name> <font image>...\n";
		return 1;
	}

	// Average symbol information
	std::map<char, OCR::Font::Symbol> average;

	// Image
	BMP img;

	// Load a non-existent font
	OCR::Font bogus("BOGUS");

	// Open file for output
	std::string outFileName = argv[1];
	outFileName = "font/" + outFileName + ".font";
	std::ofstream outFile(outFileName.c_str());

	// Load each line and read its statistics
	for (int fileNum = 2; fileNum < argc; ++fileNum)
	{
		// Create line
		img.ReadFromFile(argv[fileNum]);
		OCR::Line line(img, bogus);

		// Create vector for symbol info
		std::vector<OCR::Font::Symbol> symbols;
		symbols.reserve(ALPHABET.size());

		// Do the reading
		line.Read(&symbols);

		// Loop through and add to the "average"
		std::vector<OCR::Font::Symbol>::iterator itr = symbols.begin();
		for (unsigned charIndex = 0; itr != symbols.end() && charIndex
		        < ALPHABET .size(); ++itr, ++charIndex)
		{
			average[ALPHABET[charIndex]] += *itr;
		}
	}

	for (std::map<char, OCR::Font::Symbol>::iterator itr = average.begin(); itr
	        != average.end(); ++itr)
	{
		// Divide all statistics by number of lines read
		itr->second /= (argc - 2);
		// Print the character and its statistics to the file
		outFile << itr->first << ' ' << itr->second << std::endl;
	}

	outFile.close();
	return 0;
}
