/**
 * @file OCR.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface and documentation of functions global to the OCR
 * namespace, as well as the Box and Point classes.
 * @see OCR.cpp for the implementation.
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

#include <vector>
#include <queue>
#include "EasyBMP/EasyBMP.h"

namespace OCR
{

/**
 * Represents the position
 * of a pixel in the image
 */
struct Point
{
	/**
	 * Initializes the point.
	 * @param left X coordinate
	 * @param top  Y coordinate
	 */
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
	/**
	 * Initializes the box.
	 * @param x1 Low X  (left)
	 * @param y1 Low Y  (top)
	 * @param x2 High X (right)
	 * @param y2 High Y (bottom)
	 * @return
	 */
	Box(int x1, int y1, int x2, int y2) :
		low(x1, y1), high(x2, y2)
	{
	}

	/**
	 * Get the width of the box
	 * @return box width
	 */
	int width() const
	{
		return (high.x - low.x) + 1;
	}

	/**
	 * Get the height of the box
	 * @return box height
	 */
	int height() const
	{
		return (high.y - low.y) + 1;
	}

	bool onEdge(const Point p) const
	{
		return low.x == p.x || low.y == p.y || high.x == p.x || high.y == p.y;
	}

	bool operator==(const Box & rhs) const
	{
		return this->low == rhs.low && this->high == rhs.high;
	}
	/// Corners (inclusive)
	Point low, high;
};

/**
 * R, G, B must be < this for a foreground pixel
 */
const int FG_THRESHOLD = 110;

/**
 * Difference in R, G, B must be < this for similar pixels
 */
const int SIMILAR_THRESHOLD = 10;

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
 * Performs a breadth-first search from a point using either foreground
 * or background pixels
 * @param[in]     image     the bitmap image
 * @param[in]     start     starting point
 * @param[in]     bg        whether to search background pixels
 *                          instead of foreground pixels
 * @param[in,out] visited   which pixels have been visited.
 *                          Should have the same dimensions as limit.
 * @param[in]     limit     do not search beyond this box
 * @return                  extent of contiguous pixels found
 */
Box bfSearch(BMP & image, const Point start, bool bg, bool ** visited, const Box limit);

} // namespace OCR
