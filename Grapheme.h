/**
 * @file Grapheme.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface and documentation of the Grapheme class.
 * @see Grapheme.cpp for the implementation.
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

#ifndef GRAPHEME_H_
#define GRAPHEME_H_
#include "EasyBMP/EasyBMP.h"
namespace OCR
{

/**
 * A character in the image.
 */
class Grapheme
{
public:
	/**
	 * Initializes the class with a part of a BMP image
	 * @param[in] img reference to BMP
	 * @param[in] x1  left coordinate
	 * @param[in] y1  top coordinate
	 * @param[in] x2  right coordinate
	 * @param[in] y2  bottom coordinate
	 */
	Grapheme(BMP & img, int x1, int y1, int x2, int y2);
};

}; // namespace GraphemeResolver

#endif /* GRAPHEME_H_ */
