/**
 * @file main.cpp
 * @date Spring 2009
 * @author corey
 * @brief An application program using the GraphemeResolver library.
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
#include "TextPage.h"
using namespace OCR;
using namespace std;

int main (int argc, char * argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << "<filename>\n";
		return 1;
	}

	// Load the page from a bitmap file
	BMP i;
	i.ReadFromFile(argv[1]);

	// Read it!
	TextPage p (i);
	string s = p.Read();

	cout << s << endl;
	return 0;
}
