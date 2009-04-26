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
#include "Font.h"

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
	 * @param f font to use
	 */
	Grapheme(BMP & img, const Font & f);

	/**
	 * Initializes the object using part of a BMP image
	 * @param[in] img reference to BMP
	 * @param[in] x1  left coordinate
	 * @param[in] y1  top coordinate
	 * @param[in] x2  right coordinate
	 * @param[in] y2  bottom coordinate
	 * @param[in] f   font to use
	 */
	Grapheme(BMP & img, int x1, int y1, int x2, int y2, const Font & f);

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
	unsigned char countHoles() const;

	/**
	 * Finds the straight lines in the letter
	 * @return angles of straight lines
	 */
	std::set<unsigned char> findStraightLines() const;

	/**
	 * Checks the density of foreground pixels along a line.
	 * @param start     edge point on the line
	 * @param angle     angle of the line (0 <= angle < 180)
	 * @return density of foreground pixels along the line specified
	 */
	double checkLine(Point start, unsigned char angle) const;

	/**
	 * Checks the density of foreground pixels within an area
	 * @param area area to check
	 * @return density of foreground pixels
	 */
	double areaDensity(Box area) const;

	/// The image
	BMP & image;
	/// The part of the image to use
	Box part;
	/// The font to use
	const Font & font;
};

} // namespace OCR

#endif /*OCR_GRAPHEME_H_*/
