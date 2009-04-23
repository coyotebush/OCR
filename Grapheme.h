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

namespace OCR
{

/**
 * R, G, B must be >= this for a foreground pixel
 */
const int FG_THRESHOLD = 85;

/**
 * Determines whether a pixel is a foreground pixel.
 * @param pixel a pixel
 * @return whether this is a foreground pixel
 */
bool isForeground(RGBApixel * pixel);

/**
 * Determines whether two pixels are similar in color
 * @param a first pixel
 * @param b second pixel
 * @return whether they should be considered similar
 */
bool isSimilar(RGBApixel * a, RGBApixel * b);

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
	 * Represents the position
	 * of a pixel in the image
	 */
	struct Point
	{
		Point(int left, int top) :
			x(left), y(top)
		{
		}
		bool operator==(const Point & rhs) const
		{
			return this->x == rhs.x || this->y == rhs.y;
		}
		bool operator!=(const Point & rhs) const
		{
			return this->x != rhs.x || this->y != rhs.y;
		}
		bool operator<(const Point & rhs) const
		{
			return this->x < rhs.x && this->y < rhs.y;
		}
		int x, y;
	};

	/**
	 * Represents a rectangle,
	 * such as the extent of a letter
	 */
	struct Box
	{
		Box(int x1, int y1, int x2, int y2) :
			low(x1, y1), high(x2, y2)
		{
		}
		Point low, high;
	};

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
