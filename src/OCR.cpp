/**
 * @file OCR.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation of functions global to the OCR namespace,
 *        as well as OCR::Box::edge_iterator.
 * @see OCR.h for the interface and documentation.
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

#include "OCR.h"

namespace OCR
{

// OCR::Box::edge_iterator members
/**
 * Constructor
 * @param b Box to iterate around
 */
Box::edge_iterator::edge_iterator(const Box & b) :
	box(b), current(b.low), first(true)
{
}

/**
 * Constructor
 * @param b Box to iterate around
 * @param p starting point, should be on b's edge
 */
Box::edge_iterator::edge_iterator(const Box & b, const Point & p) :
	box(b), current(p), first(true)
{
}

/**
 * Copy constructor
 * @param other another edge_iterator
 */
Box::edge_iterator::edge_iterator(const edge_iterator & other) :
	box(other.box), current(other.current), first(other.first)
{
}

/**
 * Dereference operator
 * @return current Point
 */
Point Box::edge_iterator::operator*() const
{
	return current;
}

/**
 * Increments the current Point clockwise around the edge.
 * @return this
 */
Box::edge_iterator Box::edge_iterator::operator++()
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
bool Box::edge_iterator::operator==(const Point & p) const
{
	return current == p;
}

/**
 * Compares the current position to a Point.
 * @param p Point to compare to
 * @return whether current position and p are unequal
 */
bool Box::edge_iterator::operator!=(const Point & p) const
{
	return current != p;
}

/**
 * Determines whether the iterator is done
 * @return whether complete
 */
bool Box::edge_iterator::done() const
{
	return (current == box.low && !first) || (current.x == box.high.x
	        && box.height() == 1) || (current.y == box.high.y && box.width()
	        == 1);
}

/**
 * Returns an iterator set to the position after the current one
 * @return an iterator
 */
Box::edge_iterator Box::edge_iterator::next()
{
	edge_iterator theNext = *this;
	++theNext;
	return theNext;
}

// End OCR::Box::edge_iterator member functions


/**
 * Determines whether a pixel is a foreground pixel.
 * @param pixel a pixel
 * @return whether this is a foreground pixel
 */
bool isForeground(RGBApixel * pixel)
{
	return (pixel->Red < FG_THRESHOLD && pixel->Green < FG_THRESHOLD
	        && pixel->Blue < FG_THRESHOLD);
}

/**
 * Determines whether two pixels are similar in color
 * @param a first pixel
 * @param b second pixel
 * @return whether they should be considered similar
 */
bool isSimilar(RGBApixel * a, RGBApixel * b)
{
	int red = a->Red - b->Red;
	int green = a->Green - b->Green;
	int blue = a->Blue - b->Blue;
	if (red < 0)
		red = -red;
	if (green < 0)
		green = -green;
	if (blue < 0)
		blue = -blue;
	return (red < SIMILAR_THRESHOLD && green < SIMILAR_THRESHOLD && blue
	        < SIMILAR_THRESHOLD);
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
Box bfSearch(BMP & image, const Point start, bool bg, bool ** visited,
        const Box limit)
{
	// Initialize queue and box
	std::queue<Point> Q;
	Box extent(start.x, start.y, start.x, start.y);

	// Add the starting pixel to the queue, if it has not been visited
	if (!visited[start.x - limit.low.x][start.y - limit.low.y])
		Q.push(start);

	while (!Q.empty())
	{
		// Take a pixel
		Point p = Q.front();
		Q.pop();

		// Extend the current extent Box if necessary
		if (p.x < extent.low.x)
			extent.low.x = p.x;
		if (p.x > extent.high.x)
			extent.high.x = p.x;
		if (p.y < extent.low.y)
			extent.low.y = p.y;
		if (p.y > extent.high.y)
			extent.high.y = p.y;
		// Get all its neighbors
		Box neighbors(
		        (p.x - 1 > limit.low.x ? p.x - 1 : limit.low.x),
		        (p.y - 1 > limit.low.y ? p.y - 1 : limit.low.y),
		        (p.x + 1 < limit.high.x ? p.x + 1 : limit.high.x),
		        (p.y + 1 < limit.high.y ? p.y + 1 : limit.high.y));

		for (Point current(neighbors.low); current.x <= neighbors.high.x; ++current.x)
		{
			for (current.y = neighbors.low.y; current.y <= neighbors.high.y; ++current.y)
			{
				if (!visited[current.x - limit.low.x][current.y - limit.low.y]
				        && (bg ^ isForeground(image(current.x, current.y))))
				{
					Q.push(current);
					visited[current.x - limit.low.x][current.y - limit.low.y]
					        = true;
				}
			}
		}
	}
	return extent;
}

} // namespace OCR
