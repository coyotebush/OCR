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

#ifndef GRAPHEME_H_
#define GRAPHEME_H_
#include <vector>
#include <queue>
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
	 * Types of breadth first search.
	 * - TO_END: Stop only when out of pixels to search.
	 * - TO_EDGE: Stop when reaching an edge pixel
	 * - TO_PIXEL: Stop when reaching a particular pixel
	 */
	enum Search_Type
	{
		TO_END, TO_EDGE, TO_PIXEL
	};

	/**
	 * Performs a breadth-first search among similar pixels
	 * @param start starting pixel
	 * @param searchtype see Search_Type
	 * @param[out] extent extent of search
	 * @param end ending pixel for TO_PIXEL
	 * @return whether destination (if any) reached
	 */
	bool breadthFirstSearch(const Point start, Search_Type searchtype,
			Box& extent, const Point end = Point(0, 0));

	/**
	 * Sets the left, right, bottom, and top coordinates
	 * such that they surround the foreground pixels contained
	 */
	void pareDown();

	/**
	 * Finds the extent of a contiguous shape
	 * starting at a certain point
	 * @param start starting Point
	 * @return extent of shape
	 */
	Box findContiguousShape(const Point start);

	/**
	 * Determines whether one point is reachable
	 * from another using pixels of similar color.
	 * @param start starting point
	 * @param end   starting point
	 * @return
	 */
	bool isReachable(Point start, Point end);

	/**
	 * Determines whether a pixel at the edge of the bounding box
	 * is reachable from another pixel
	 * @param start starting point
	 * @return whether edge reachable
	 */
	bool isEdgeReachable(const Point start);

	/**
	 * Counts the number of "holes" in the letter
	 * @return number of holes
	 */
	unsigned short countHoles();

	/**
	 * Finds the straight lines in the letter
	 * @return angles of straight lines
	 */
	std::vector<unsigned short> findStraightLines();

	/// The image
	BMP & image;
	/// The part of the image to use
	int left, right, bottom, top;
	/// The resulting character
	char result;
};

} // namespace OCR

#endif /* GRAPHEME_H_ */
