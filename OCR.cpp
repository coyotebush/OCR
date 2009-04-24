/**
 * @file OCR.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation of functions global to the OCR namespace.
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
 * Performs a breadth-first search from a point using similar pixels
 * @param[in]     start     starting point
 * @param[in,out] visited   which pixels have been visited
 * @param[in]     limit     do not search beyond this box
 * @return                  extent of contiguous pixels found
 */
Box pSearch(const Point start, std::vector<std::vector<int> > & visited,
		const Box limit)
{
	// Initialize queue and box
	std::queue<Point> Q;
	Box extent(start.x, start.y, start.x, start.y);

	// Keep track of which pixels have been visited
	// @todo 2D vector or 2D dynamic array?
	int width = right - left;

	// Add the starting pixel to the queue
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
		int lowX = (p.x - 1 > left ? p.x - 1 : left);
		int highX = (p.x + 1 < right - 1 ? p.x + 1 : right - 1);
		int lowY = (p.y - 1 > top ? p.y - 1 : top);
		int highY = (p.y + 1 < bottom - 1 ? p.y + 1 : bottom);
		for (int x = lowX; x <= highX; ++x)
		{
			for (int y = lowY; y <= highY; ++y)
			{
				Point n(x, y);
				if (!visited[width * (y - top) + (x - left)] && isSimilar(
						image(start.x, start.y), image(n.x, n.y)))
				{
					Q.push(n);
					visited[width * (y - top) + (x - left)] = true;
				}
			}
		}
	}
	return extent;
}

} // namespace OCR
