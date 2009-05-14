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
 * Performs a flood-fill from a point using either foreground
 * or background pixels.
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
        const Box limit)
{
	// Initialize queue and box
	std::queue<Point> pointsToVisit;
	Box extentOfContiguousPixelsFound(start.x, start.y, start.x, start.y);

	// Add the starting pixel to the queue, if it has not been visited
	if (!visited[start.x - limit.low.x][start.y - limit.low.y])
		pointsToVisit.push(start);

	while (!pointsToVisit.empty())
	{
		// Take a pixel
		Point current = pointsToVisit.front();
		pointsToVisit.pop();

		// Extend the current extent Box if necessary
		extentOfContiguousPixelsFound.extendToInclude(current);

		// Get all its neighbors
		Box neighbors(
				(current.x - 1 > limit.low.x ? current.x - 1 : limit.low.x),
				(current.y - 1 > limit.low.y ? current.y - 1 : limit.low.y),
				(current.x + 1 < limit.high.x ? current.x + 1 : limit.high.x),
				(current.y + 1 < limit.high.y ? current.y + 1 : limit.high.y));
		for (Point neighbor(neighbors.low); neighbor.x <= neighbors.high.x; ++neighbor.x)
		{
			for (neighbor.y = neighbors.low.y; neighbor.y <= neighbors.high.y; ++neighbor.y)
			{
				if (!visited[neighbor.x - limit.low.x][neighbor.y - limit.low.y]
						&& (bg ^ isForeground(image(neighbor.x, neighbor.y))))
				{
					pointsToVisit.push(neighbor);
					visited[neighbor.x - limit.low.x][neighbor.y - limit.low.y]
							= true;
				}
			}
		}
	}
	return extentOfContiguousPixelsFound;
}

} // namespace OCR
