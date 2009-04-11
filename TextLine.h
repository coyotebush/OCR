/**
 * @file TextLine.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface and documentation for the TextLine class.
 * @see TextLine.cpp for the implementation.
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
	 * @param[in] img reference to BMP
	 * @param[in] y1  top coordinate
	 * @param[in] y2  bottom coordinate
	 */
	TextLine(const BMP & img, int y1, int y2);

	/**
	 * Initializes the object as a copy of another
	 * @param other a TextLine object
	 */
	TextLine(const TextLine & other);

	/**
	 * Recognizes the text.
	 * @return text of the line.
	 */
	std::string Read();

private:
	/// The letters
	std::vector<Grapheme> letters;
	/// The resulting string
	std::string result;
	/// The image
	BMP & image;
	/// The part of the image
	int top, bottom;
};
} // namespace OCR

#endif /* TEXTLINE_H_ */
