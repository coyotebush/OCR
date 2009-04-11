/**
 * @file Grapheme.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation of the Grapheme class.
 * @see Grapheme.h for the interface and documentation.
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

#include "Grapheme.h"
namespace OCR
{

/**
 * Determines whether a pixel is a foreground pixel.
 * @param pixel a pixel
 * @return whether this is a foreground pixel
 */
bool isForeground(RGBApixel * pixel)
{
	return (pixel->Red < 100 && pixel->Green < 100 && pixel->Blue < 100);
}

/**
 * Initializes the object using an entire image
 * @param img reference to a BMP
 */
Grapheme::Grapheme(BMP & img) :
	image(img)
{
}

/**
 * Initializes the object using part of a BMP image
 * @param[in] img reference to BMP
 * @param[in] x1  left coordinate
 * @param[in] y1  top coordinate
 * @param[in] x2  right coordinate
 * @param[in] y2  bottom coordinate
 */
Grapheme::Grapheme(BMP & img, int x1, int y1, int x2, int y2) :
	image(img), left(x1), right(x2), bottom(y2), top(y1)
{
}

/**
 * Initializes the object as a copy of another
 * @param other a Grapheme object
 */
/**
 * Initializes the object as a copy of another
 * @param other a Grapheme object
 */
Grapheme::Grapheme(const Grapheme & other) :
	image(other.image), left(other.left), right(other.right), bottom(
			other.bottom), top(other.top)
{
}

/**
 * Copies the members of another object
 * @param other a Grapheme object
 */
Grapheme & Grapheme::operator =(const Grapheme & other)
{
	image = other.image;
	left = other.left;
	right = other.right;
	bottom = other.bottom;
	top = other.top;
	return *this;
}

} // namespace GraphemeResolver
