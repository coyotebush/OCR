/**
 * @file Page.h
 * @author Corey Ford <fordco@sonoma.edu>
 * @date Spring 2009
 * @brief The interface and documentation of the Page class.
 * @see Page.cpp for the implementation.
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

#ifndef OCR_PAGE_H_
#define OCR_PAGE_H_
#include <deque>
#include <string>
#include "EasyBMP/EasyBMP.h"
#include "Line.h"

namespace OCR
{
class Page
{
public:
	/**
	 * Initializes the class
	 * @param img BMP image to use
	 * @param f   font to use
	 */
	Page(BMP & img, const Font & f);

	/**
	 * Initializes the object as a copy of another
	 * @param other a Page object
	 */
	Page(const Page & other);

	/**
	 * Copies the members of another object
	 * @param other a Page object
	 */
	Page & operator =(const Page & other);

	/**
	 * Processes the image.
	 * @return text of the image.
	 */
	std::string Read();

private:
	/// the image
	BMP & image;
	/// the lines of text
	std::deque<Line> lines;
	/// The resulting text
	std::string result;
	/// The font to use
	const Font & font;
};

} // namespace OCR
#endif /*OCR_PAGE_H_*/
