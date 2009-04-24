/**
 * @file main.cpp
 * @date Spring 2009
 * @author corey
 * @brief An application program using the GraphemeResolver library.
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
#include <string>
#include "EasyBMP/EasyBMP.h"
#include "Page.h"
using namespace std;

int main (int argc, char * argv[])
{
	string result;
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " [plc] <filename>\n";
		return 1;
	}

	// Load the page from a bitmap file
	BMP img;
	img.ReadFromFile(argv[2]);

	// Read it!
	if (string(argv[1]) == "p")
	{
		OCR::Page page(img);
		cout << page.Read() << endl;
	}
	else if (string(argv[1]) == "l")
	{
		OCR::Line line(img);
		cout << line.Read() << endl;
	}
	else if (string(argv[1]) == "c")
	{
		OCR::Grapheme letter(img);
		cout << letter.Read() << endl;
	}

	return 0;
}
