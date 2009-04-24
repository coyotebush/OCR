/**
 * @file Grapheme.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface and documentation of the Grapheme class.
 * @see Grapheme.cpp for the implementation.
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

#ifndef OCR_GRAPHEME_H_
#define OCR_GRAPHEME_H_
#include <cmath>
#include <set>
#include "EasyBMP/EasyBMP.h"
#include "OCR.h"

namespace OCR
{

/**
 * A character in the image.
 */
class Grapheme
{
public:
	/**
	 * Initializes the object using an entire image
	 * @param img reference to a BMP
	 */
	Grapheme(BMP & img);

	/**
	 * Initializes the object using part of a BMP image
	 * @param[in] img reference to BMP
	 * @param[in] x1  left coordinate
	 * @param[in] y1  top coordinate
	 * @param[in] x2  right coordinate
	 * @param[in] y2  bottom coordinate
	 */
	Grapheme(BMP & img, int x1, int y1, int x2, int y2);

	/**
	 * Initializes the object as a copy of another
	 * @param other a Grapheme object
	 */
	Grapheme(const Grapheme & other);

	/**
	 * Copies the members of another object
	 * @param other a Grapheme object
	 */
	Grapheme & operator =(const Grapheme & other);

	/**
	 * Recognizes the character.
	 * @return the character.
	 */
	char Read();

private:

	/**
	 * Sets the left, right, bottom, and top coordinates
	 * such that they surround the foreground pixels contained
	 */
	void pareDown();

	/**
	 * Counts the number of "holes" in the letter
	 * @return number of holes
	 */
	unsigned short countHoles() const;

	/**
	 * Finds the straight lines in the letter
	 * @return angles of straight lines
	 */
	std::set<unsigned short> findStraightLines() const;

	/**
	 * Checks for a line of foreground pixels
	 * @param x X-coordinate of midpoint of line
	 * @param angle Angle of line
	 * @return Length of longest dark line
	 */
	unsigned int checkLine (unsigned int x, unsigned short angle) const;

	/// The image
	BMP & image;
	/// The part of the image to use
	Box part;
	/// The resulting character
	char result;
};

} // namespace OCR

#endif /*OCR_GRAPHEME_H_*/
