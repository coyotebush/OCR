/**
 * @file Line.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface and documentation for the Line class.
 * @see Line.cpp for the implementation.
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

#ifndef OCR_LINE_H_
#define OCR_LINE_H_
#include <vector>
#include <string>
#include "EasyBMP/EasyBMP.h"
#include "Grapheme.h"

namespace OCR
{
/**
 * A line of text in the image.
 */
class Line
{
public:
	/**
	 * Initializes the object using an entire image
	 * @param img reference to a BMP
	 */
	Line(BMP & img);

	/**
	 * Initializes the object using part of a BMP image
	 * @param img reference to BMP
	 * @param y1  top coordinate
	 * @param y2  bottom coordinate
	 */
	Line(BMP & img, int y1, int y2);

	/**
	 * Initializes the object as a copy of another
	 * @param other a Line object
	 */
	Line(const Line & other);

	/**
	 * Copies the members of another object
	 * @param other a Line object
	 */
	Line & operator =(const Line & other);

	/**
	 * Recognizes the text.
	 * @return text of the line.
	 */
	std::string Read();

private:
	/// The minimum relative width of a space character
	static const double SPACE;
	/// The image
	BMP & image;
	/// The part of the image (inclusive)
	int top, bottom;
};
} // namespace OCR

#endif /*OCR_LINE_H_*/
