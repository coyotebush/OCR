/**
 * @file OCR.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface and documentation of functions global to the OCR
 * namespace.
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
#include "Box.h"
#include "EasyBMP/EasyBMP.h"

namespace OCR
{

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
