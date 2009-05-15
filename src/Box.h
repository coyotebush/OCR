/**
 * @file Box.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The Box and Point classes.
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
#ifndef OCR_BOX_H_
#define OCR_BOX_H_

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
class Box
{
public:
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
	Box(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0) :
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
	 * Determines whether two boxes have a similar x midpoint.
	 * @param other     another box
	 * @param tolerance how close they must be
	 */
	bool hasSimilarXMidpoint (const Box & other, unsigned short tolerance)
	{
		int diff = ((high.x - low.x)/2 - (other.high.x - other.low.x)/2);
		if (diff < 0)
			diff = -diff;
		return diff <= tolerance;
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
	 * Extends the box to include another box
	 * @param b Box that should be included
	 */
	void extendToInclude(const Box & b)
	{
		extendToInclude(b.low);
		extendToInclude(b.high);
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
	edge_iterator(const Box & b) :
		box(b), current(b.low), first(true)
	{
	}

	/**
	 * Dereference operator
	 * @return current Point
	 */
	Point operator*() const
	{
		return current;
	}
	
	Point* operator -> ()
	{
		return &current;
	}

	/**
	 * Increments the current Point clockwise around the edge.
	 * @return this
	 */
	edge_iterator operator++()
	{
		// Top edge
		if (current.y == box.low.y && current.x < box.high.x)
			++current.x;

		// Right edge
		else if (current.x == box.high.x && current.y < box.high.y)
			++current.y;

		// Bottom edge
		else if (current.y == box.high.y && current.x > box.low.x)
			--current.x;

		// Left edge
		else if (current.x == box.low.x && current.y > box.low.y)
			--current.y;

		first = false;
		return *this;
	}

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
	operator bool() const
	{
		return (current == box.low && !first) || (current.x == box.high.x
		        && box.height() == 1) || (current.y == box.high.y
		        && box.width() == 1);
	}

private:
	/// The box
	Box box;
	/// Current location
	Point current;
	/// Whether this is still the starting point.
	bool first;

};

}

#endif /*OCR_BOX_H_*/
