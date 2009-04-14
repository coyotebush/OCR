/**
 * @file TextLine.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface and documentation for the TextLine class.
 * @see TextLine.cpp for the implementation.
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

#ifndef TEXTLINE_H_
#define TEXTLINE_H_
#include <vector>
#include <string>
#include <sstream>
#include "EasyBMP/EasyBMP.h"
#include "Grapheme.h"

namespace OCR
{
/**
 * A line of text in the image.
 */
class TextLine
{
public:
	/**
	 * Initializes the object using an entire image
	 * @param img reference to a BMP
	 */
	TextLine(BMP & img);

	/**
	 * Initializes the object using part of a BMP image
	 * @param img reference to BMP
	 * @param y1  top coordinate
	 * @param y2  bottom coordinate
	 */
	TextLine(BMP & img, int y1, int y2);

	/**
	 * Initializes the object as a copy of another
	 * @param other a TextLine object
	 */
	TextLine(const TextLine & other);

	/**
	 * Copies the members of another object
	 * @param other a TextLine object
	 */
	TextLine & operator =(const TextLine & other);

	/**
	 * Recognizes the text.
	 * @return text of the line.
	 */
	std::string Read();

	/**
	 * Recognizes the text to an output stream
	 * @param outs output stream
	 * @param t TextLine object
	 * @return the output stream
	 */
	friend std::ostream & operator <<(std::ostream & outs, const TextLine & t);

private:
	/// The image
	BMP & image;
	/// The part of the image
	int top, bottom;
};
} // namespace OCR

#endif /* TEXTLINE_H_ */
