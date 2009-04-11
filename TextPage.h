/**
 * @file TextPage.h
 * @author Corey Ford <fordco@sonoma.edu>
 * @date Spring 2009
 * @brief The interface and documentation of the TextPage class.
 * @see TextPage.cpp for the implementation.
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

#ifndef TEXTPAGE_H_
#define TEXTPAGE_H_
#include <queue>
#include <vector>
#include <string>
#include "EasyBMP/EasyBMP.h"
#include "TextLine.h"

namespace OCR
{
class TextPage
{
public:
	/**
	 * Initializes the class with a BMP image
	 */
	TextPage(BMP & img);

	/**
	 * Processes the image.
	 * @return text of the image.
	 */
	std::string Read();

private:
	/// the image
	BMP & image;
	/// the lines of text
	std::vector<TextLine> lines;
	/// The resulting text
	std::string result;
};

} // namespace OCR
#endif /*TEXTPAGE_H_*/
