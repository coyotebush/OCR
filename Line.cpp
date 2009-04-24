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

/// The relative width of a space character
const double Line::SPACE = 0.2;

/**
 * Initializes the object using an entire image
 * @param img reference to a BMP
 */
Line::Line(BMP & img) :
	image(img), top(0)
{
	bottom = image.TellHeight();
}

/**
 * Initializes the object using part of a BMP image
 * @param[in] img reference to BMP
 * @param[in] y1  top coordinate
 * @param[in] y2  bottom coordinate
 */
Line::Line(BMP & img, int y1, int y2) :
	image(img), top(y1), bottom(y2)
{
}

/**
 * Initializes the object as a copy of another
 * @param other a Line object
 */
Line::Line(const Line & other) :
	image(other.image), top(other.top), bottom(other.bottom)
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
 * @return text of the line.
 */
std::string Line::Read()
{
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
			Grapheme sym(image, left, top, right, bottom);
			result += sym.Read();
			inSymbol = false;
		}
	}

	return result;
}

} // namespace OCR
