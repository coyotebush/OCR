/**
 * @file Line.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation of the Line class.
 * @see Line.h for the interface and documentation.
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

#include "Line.h"
namespace OCR
{

/// The minimum width, relative to height, of a space character
const double Line::SPACE = 0.28;

/**
 * Initializes the object using an entire image
 * @param img reference to a BMP
 * @param f font to use
 */
Line::Line(BMP & img, const Font & f) :
	image(img), top(0), font(f)
{
	bottom = image.TellHeight() - 1;
}

/**
 * Initializes the object using part of a BMP image
 * @param img reference to BMP
 * @param y1  top coordinate
 * @param y2  bottom coordinate
 * @param f font to use
 */
Line::Line(BMP & img, int y1, int y2, const Font & f) :
	image(img), top(y1), bottom(y2), font(f)
{
}

/**
 * Initializes the object as a copy of another
 * @param other a Line object
 */
Line::Line(const Line & other) :
	image(other.image), top(other.top), bottom(other.bottom), font(other.font)
{
}

/**
 * Copies the members of another object
 * @param other a Line object
 */
Line & Line::operator =(const Line & other)
{
	image = other.image;
	top = other.top;
	bottom = other.bottom;
	return *this;
}

/**
 * Recognizes the text.
 * @param symData optionally store symbol data in a vector
 * @return text of the line.
 */
std::string Line::Read(std::vector<Font::Symbol> * symData)
{
	const unsigned short VARIANCE = 10;
	std::string result = "";
	// Initialize visited array
	bool ** visited = new bool *[image.TellWidth()];
	for (unsigned i = 0; i < image.TellWidth(); ++i)
	{
		visited[i] = new bool[bottom - top + 1];
		for (unsigned j = 0; j < bottom - top + 1; ++j)
			visited[i][j] = false;
	}
	// Other variables
	Box limit(0,top,image.TellWidth(), bottom), currentLetter, temp;
	// Find a foreground pixel
	for (Point p(0,top); p.x < image.TellWidth(); ++p.x)
	{
		for (p.y = top; p.y < bottom;++p.y)
		{
			if (isForeground(image(p.x,p.y)))
			{
				// Do a flood-fill from it
				temp = floodFill(image, p,false,visited,limit);
				
				// If close, add to the current box
				if (currentLetter.hasSimilarXMidpoint(temp, VARIANCE))
					currentLetter.extendToInclude(temp);
				else
				{
					// Read the current letter
					Grapheme sym(image, currentLetter, font);
					result += sym.Read();
					// Replace currentLetter with the new box
					currentLetter = temp;
				}
			}
		}
	}
	return result;
}

/*{
	std::string result = "";
	// Divide into symbols
	int left = 0, right = 0; // of the current grapheme
	bool inSymbol = false; // Whether in a symbol

	// Split horizontally into letters, read each and concatenate
	for (int col = 0; col < image.TellWidth(); ++col)
	{
		// Search for a foreground pixel in this column
		bool fgFound = false;
		for (int row = top; row <= bottom && !fgFound; ++row)
			if (isForeground(image(col, row)))
				fgFound = true;

		if (fgFound && !inSymbol)
		// Starting a new symbol
		{
			left = col;
			if (left - right > SPACE * (bottom - top))
				// Large space, add a space character to the result
				result += ' ';
			inSymbol = true;
		}
		else if (!fgFound && inSymbol)
		// End of a symbol
		{
			right = col + 1;
			Grapheme sym(image, left, top, right, bottom, font);
			result += sym.Read();
			// If storing symbol data, add this
			if (symData)
				symData->push_back(sym.theSymbol);
			inSymbol = false;
		}
	}

	return result;
}*/

} // namespace OCR
