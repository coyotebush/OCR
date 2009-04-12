/**
 * @file TextPage.cpp
 * @author Corey Ford <fordco@sonoma.edu>
 * @date Spring 2009
 * @brief The implementation of the TextPage class.
 * @see TextPage.h for the interface and documentation.
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

#include "TextPage.h"
namespace OCR
{

/**
 * Initializes the class with a BMP image
 */
TextPage::TextPage(BMP & img) :
	image(img)
{
}

/**
 * Initializes the object as a copy of another
 * @param other a TextPage object
 */
TextPage::TextPage(const TextPage & other) :
	image(other.image)
{
}

/**
 * Copies the members of another object
 * @param other a TextPage object
 */
TextPage & TextPage::operator =(const TextPage & other)
{
	image = other.image;
	return *this;
}

/**
 * Processes the image.
 * @return text of the image.
 */
std::string TextPage::Read()
{
	result = "";
	lines.clear();
	// Divide into lines
	int top = 0, bottom = 0; // of the current line of text
	bool inRow = false; // Whether in a row

	for (int row = 0; row < image.TellHeight(); ++row)
	{
		// Search for a foreground pixel in this row
		bool fgFound = false;
		for (int col = 0; col < image.TellWidth() && !fgFound; ++col)
			if (isForeground(image(col, row)))
				fgFound = true;

		if (fgFound && !inRow)
		// Starting a new row
		{
			top = row;
			inRow = true;
		}
		else if (!fgFound && inRow)
		// End of a row
		{
			bottom = row;
			lines.push_back(TextLine(image, top, bottom));
			inRow = false;
		}
	}
	// Read each line and concatenate results
	for (std::vector<TextLine>::iterator i = lines.begin(); i != lines.end(); ++i)
		result += i->Read() + '\n';
	return result;
}

} // namespace OCR
