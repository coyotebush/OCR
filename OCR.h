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

namespace OCR
{

/**
 * R, G, B must be < this for a foreground pixel
 */
const int FG_THRESHOLD = 85;

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

} // namespace OCR
