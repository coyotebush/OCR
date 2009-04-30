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
#include <map>
#include "EasyBMP/EasyBMP.h"
#include "Font.h"
#include "Page.h"

int main(int argc, char * argv[])
{
	using OCR::Font::Symbol;

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <font image>...\n";
		return 1;
	}
	
	// Average symbol information
	std::map<char, Symbol> average;
	// Image
	BMP img;

	// Load a non-existent font
	OCR::Font bogus("BOGUS");

	// Load each line and read its statistics
	for (int fileNum = 1; fileNum < argc; ++fileNum)
	{
		img.ReadFromFile(argv[fileNum]);
		OCR::Line line(img, bogus);
		std::vector<Symbol> symbols(100);
		line.Read(&symbols);
		for(std::vector<Symbol>::iterator itr=symbols.begin(), char character='!';
			itr!=symbols.end();++itr,++character)
		{
			average[character] += *itr;
		}
	}
	
	// Now divide the total statistics by the number of lines, and print information
	for (std::map<char, Symbol>::iterator itr=average.begin(); itr != average.end(); ++itr)
	{
		(*it).second /= argc - 1;
		std::cout << (*it).first << ' ' << (*it).second << std::endl;
	}

	return 0;
}
