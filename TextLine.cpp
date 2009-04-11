/**
 * @file TextLine.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation of the TextLine class.
 * @see TextLine.h for the interface and documentation.
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

#include "TextLine.h"
namespace OCR
{

/**
 * Initializes the object using an entire image
 * @param img reference to a BMP
 */
TextLine::TextLine(BMP & img) :
	image(img), top(0)
{
	bottom = image.TellWidth();
}

/**
 * Initializes the object using part of a BMP image
 * @param[in] img reference to BMP
 * @param[in] y1  top coordinate
 * @param[in] y2  bottom coordinate
 */
TextLine::TextLine(BMP & img, int y1, int y2) :
	image(img), top(y1), bottom(y2)
{
}

/**
 * Initializes the object as a copy of another
 * @param other a TextLine object
 */
TextLine::TextLine(const TextLine & other) :
	image(other.image), top(other.top), bottom(other.bottom)
{
}

/**
 * Copies the members of another object
 * @param other a TextLine object
 */
TextLine & TextLine::operator =(const TextLine & other)
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
std::string TextLine::Read()
{
	// TODO: Split horizontally into letters
	// TODO: Keep track of spaces
	// TODO: Read letters and concatenate for result
	return result;
}

} // namespace GraphemeResolver
