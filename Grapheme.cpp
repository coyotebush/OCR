/**
 * @file Grapheme.cpp
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation of the Grapheme class.
 * @see Grapheme.h for the interface and documentation.
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

#include "Grapheme.h"
namespace OCR
{

/**
 * Initializes the object using an entire image
 * @param img reference to a BMP
 */
Grapheme::Grapheme(BMP & img) :
	image(img), left(0), top(0)
{
	right = image.TellWidth();
	bottom = image.TellHeight();
}

/**
 * Initializes the object using part of a BMP image
 * @param[in] img reference to BMP
 * @param[in] x1  left coordinate
 * @param[in] y1  top coordinate
 * @param[in] x2  right coordinate
 * @param[in] y2  bottom coordinate
 */
Grapheme::Grapheme(BMP & img, int x1, int y1, int x2, int y2) :
	image(img), left(x1), right(x2), bottom(y2), top(y1)
{
}

/**
 * Initializes the object as a copy of another
 * @param other a Grapheme object
 */
Grapheme::Grapheme(const Grapheme & other) :
	image(other.image), left(other.left), right(other.right), bottom(
			other.bottom), top(other.top)
{
}

/**
 * Copies the members of another object
 * @param other a Grapheme object
 */
Grapheme & Grapheme::operator =(const Grapheme & other)
{
	image = other.image;
	left = other.left;
	right = other.right;
	bottom = other.bottom;
	top = other.top;
	return *this;
}

/**
 * Recognizes the character.
 * @return the character
 * @todo Implement! This is the tricky part.
 */
char Grapheme::Read()
{
	pareDown();
	unsigned short holes = countHoles();
	std::cout << "Holes: " << holes << std::endl;
	//std::vector<unsigned short> angles = findStraightLines();
	return 'a';
}

/**
 * Sets the left, right, bottom, and top coordinates
 * such that they surround the foreground pixels contained
 */
void Grapheme::pareDown()
{
	bool fgFound;
	// Pare top
	for (fgFound = false; top <= bottom && !fgFound; ++top)
		for (int col = left; col <= right; ++col)
			if (isForeground(image(col, top)))
				fgFound = true;
	// Pare bottom
	for (fgFound = false; bottom >= top && !fgFound; --bottom)
		for (int col = left; col <= right; ++col)
			if (isForeground(image(col, top)))
				fgFound = true;
	// Pare left
	for (fgFound = false; left <= right && !fgFound; ++left)
		for (int row = top; row <= bottom; ++row)
			if (isForeground(image(left, row)))
				fgFound = true;
	// Pare right
	for (fgFound = false; right >= left && !fgFound; --right)
		for (int row = top; row <= bottom; ++row)
			if (isForeground(image(right, row)))
				fgFound = true;
}

/**
 * Counts the number of "holes" in the letter
 * @return number of holes
 */
unsigned short Grapheme::countHoles()
{
	// Try only some pixels
	int spacing = (right - left) / 5;
	if (spacing < 1)
		spacing = 1;
	// Determine which of these are unreachable
	std::set<Point> unreachables;
	Point corner(left, top);
	for (int x = left; x < right; x += spacing)
	{
		for (int y = top; y < bottom; y += spacing)
		{
			if (!isForeground(image(x, y)))
			{
				Point current(x, y);
				if (!isEdgeReachable(current))
					unreachables.insert(current);
			}
		}
	}
	// Check whether any of these pixels are reachable from each other (N! time)
	for (std::set<Point>::iterator i = unreachables.begin(); i
			!= unreachables.end();)
	{
		// Make a copy of the iterator, then advance it
		std::set<Point>::iterator subject = i;
		++i;
		// Check all pixels from this point
		for (std::set<Point>::iterator j = i; j != unreachables.end(); ++j)
		{
			// and check whether they are reachable from the subject
			if (isReachable(*subject, *j))
			{
				unreachables.erase(*subject);
				break;
			}
		}
	}
	return unreachables.size();
}

/**
 * Finds the straight lines in the letter
 * @return angles of straight lines
 * @todo implement
 */
std::vector<unsigned short> Grapheme::findStraightLines()
{
}

} // namespace GraphemeResolver
