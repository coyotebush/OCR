/**
 * @file OCR.h
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

#ifndef OCR_OCR_H_
#define OCR_OCR_H_
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

	/**
	 * Copy constructor
	 * @param other another Point
	 */
	Point(const Point & other) :
		x(other.x), y(other.y)
	{
	}

	/**
	 * Equality operator
	 * @param rhs another Point
	 * @return whether equal
	 */
	bool operator==(const Point & rhs) const
	{
		return this->x == rhs.x && this->y == rhs.y;
	}

	/**
	 * Inequality operator
	 * @param rhs another Point
	 * @return whether unequal
	 */
	bool operator!=(const Point & rhs) const
	{
		return this->x != rhs.x || this->y != rhs.y;
	}

	/**
	 * Less-than operator
	 * @param rhs another Point
	 * @return whether the other point has both greater x and greater y
	 */
	bool operator<(const Point & rhs) const
	{
		return this->x < rhs.x && this->y < rhs.y;
	}

	/// Coordinates
	unsigned x, y;
};

/**
 * Represents a rectangle,
 * such as the extent of a letter
 */
struct Box
{
	/**
	 * Iterates around the edge of a Box
	 */
	class edge_iterator;

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
	 * Copy constructor
	 * @param other another Box
	 */
	Box(const Box & other) :
		low(other.low), high(other.high)
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

	/**
	 * Get the area of the box
	 * @return number of pixels included in the box
	 */
	unsigned area() const
	{
		return width() * height();
	}

	/**
	 * Determines whether a Point is on the edge of this Box
	 * @param p a Point
	 * @return whether on the border
	 */
	bool onEdge(const Point & p) const
	{
		return low.x == p.x || low.y == p.y || high.x == p.x || high.y == p.y;
	}

	/**
	 * Determines whether this includes a given Point
	 * @param p a Point
	 * @return whether included in the Box
	 */
	bool contains(const Point & p) const
	{
		return p.x <= high.x && p.x >= low.x && p.y <= high.y && p.y >= low.y;
	}

	/**
	 * Extends the box to include a given Point
	 * @param p Point that should be included
	 */
	void extendToInclude(const Point & p)
	{
		if (p.x < low.x)
			low.x = p.x;
		if (p.x > high.x)
			high.x = p.x;
		if (p.y < low.y)
			low.y = p.y;
		if (p.y > high.y)
			high.y = p.y;
	}

	/**
	 * Compares this to another Box
	 * @param rhs another Box
	 * @return whether they refer to the same area.
	 */
	bool operator==(const Box & rhs) const
	{
		return this->low == rhs.low && this->high == rhs.high;
	}

	/// Corners (inclusive)
	Point low, high;
};

/**
 * Iterates around the edge of a Box
 */
class Box::edge_iterator
{
public:
	/**
	 * Constructor
	 * @param b Box to iterate around
	 */
	edge_iterator(const Box & b);

	/**
	 * Constructor
	 * @param b Box to iterate around
	 * @param p starting point, should be on b's edge
	 */
	edge_iterator(const Box & b, const Point & p);

	/**
	 * Copy constructor
	 * @param other another edge_iterator
	 */
	edge_iterator(const edge_iterator & other);

	/**
	 * Dereference operator
	 * @return current Point
	 */
	Point operator*() const
	{
		return current;
	}

	/**
	 * Increments the current Point clockwise around the edge.
	 * @return this
	 */
	edge_iterator operator++();

	/**
	 * Compares the current position to a Point.
	 * @param p Point to compare to
	 * @return whether current position and p are equal
	 */
	bool operator==(const Point & p) const
	{
		return current == p;
	}

	/**
	 * Compares the current position to a Point.
	 * @param p Point to compare to
	 * @return whether current position and p are unequal
	 */
	bool operator!=(const Point & p) const
	{
		return current != p;
	}

	/**
	 * Determines whether the iterator is done
	 * @return whether complete
	 */
	bool done() const;

	/**
	 * Returns an iterator set to the position after the current one
	 * @return an iterator
	 */
	edge_iterator next();
private:
	/// The box
	Box box;
	/// Current location
	Point current;
	/// Whether this is still the starting point.
	bool first;

};

/**
 * Difference in R, G, B must be < this for similar pixels
 */
const int SIMILAR_THRESHOLD = 10;

/**
 * Determines whether a pixel is a foreground pixel.
 * @param pixel a pixel
 * @return whether this is a foreground pixel
 */
inline bool isForeground(RGBApixel * pixel)
{
	const int FG_THRESHOLD = 110;
	return (pixel->Red < FG_THRESHOLD && pixel->Green < FG_THRESHOLD
	        && pixel->Blue < FG_THRESHOLD);
}

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
Box floodFill(BMP & image, const Point start, bool bg, bool ** visited,
        const Box limit);

} // namespace OCR

#endif /*OCR_OCR_H_*/
