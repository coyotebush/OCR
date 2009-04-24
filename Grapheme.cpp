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
	image(img), part(0, 0, image.TellWidth() - 1, image.TellHeight() - 1)
{
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
	image(img), part(x1, y1, x2, y2)
{
}

/**
 * Initializes the object as a copy of another
 * @param other a Grapheme object
 */
Grapheme::Grapheme(const Grapheme & other) :
	image(other.image), part(other.part)
{
}

/**
 * Copies the members of another object
 * @param other a Grapheme object
 */
Grapheme & Grapheme::operator =(const Grapheme & other)
{
	image = other.image;
	part = other.part;
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
	//std::cout << holes << ' ';
	//std::set<unsigned short> angles = findStraightLines();
	return '0' + holes;
}

/**
 * Sets the left, right, bottom, and top coordinates
 * such that they surround the foreground pixels contained
 */
void Grapheme::pareDown()
{
	bool fgFound;
	// Pare top
	for (fgFound = false; part.low.y <= part.high.y; ++part.low.y)
	{
		for (int col = part.low.x; col <= part.high.x && !fgFound; ++col)
			if (isForeground(image(col, part.low.y)))
				fgFound = true;
		if (fgFound)
			break;
	}
	// Pare bottom
	for (fgFound = false; part.high.y >= part.low.y && !fgFound; --part.high.y)
	{
		for (int col = part.low.x; col <= part.high.x && !fgFound; ++col)
			if (isForeground(image(col, part.low.y)))
				fgFound = true;
		if (fgFound)
			break;
	}
	// Pare left
	for (fgFound = false; part.low.x <= part.high.x; ++part.low.x)
	{
		for (int row = part.low.y; row <= part.high.y && !fgFound; ++row)
			if (isForeground(image(part.low.x, row)))
				fgFound = true;
		if (fgFound)
			break;
	}
	// Pare part.high.x
	for (fgFound = false; part.high.x >= part.low.x; --part.high.x)
	{
		for (int row = part.low.y; row <= part.high.y && !fgFound; ++row)
			if (isForeground(image(part.high.x, row)))
				fgFound = true;
		if (fgFound)
			break;
	}
}

/**
 * Counts the number of "holes" in the letter
 * @return number of holes
 */
unsigned short Grapheme::countHoles() const
{
	int holeCount = 0;
	// Initialize visited array
	bool ** visited = new bool *[part.width()];
	for (int i = 0; i < part.width(); ++i)
	{
		visited[i] = new bool[part.height()];
		for (int j = 0; j < part.height(); ++j)
			visited[i][j] = false;
	}

	// Do a breadth-first search from each background edge pixel
	for (Point current(part.low.x, part.low.y); current.x <= part.high.x; ++current.x)
		if (!isForeground(image(current.x, current.y)))
			bfSearch(image, current, true, visited, part);
	for (Point current(part.low.x, part.high.y); current.x <= part.high.x; ++current.x)
		if (!isForeground(image(current.x, current.y)))
			bfSearch(image, current, true, visited, part);
	for (Point current(part.low.x, part.low.y); current.y <= part.high.y; ++current.y)
		if (!isForeground(image(current.x, current.y)))
			bfSearch(image, current, true, visited, part);
	for (Point current(part.high.x, part.low.y); current.y <= part.high.y; ++current.y)
		if (!isForeground(image(current.x, current.y)))
			bfSearch(image, current, true, visited, part);

	// Loop through every inner pixel
	for (Point current(part.low.x + 1, part.low.y + 1); current.x < part.high.x; ++current.x)
	{
		for (current.y = part.low.y; current.y < part.high.y; ++current.y)
		{
			if (!visited[current.x - part.low.x][current.y - part.low.y]
					&& !isForeground(image(current.x, current.y)))
			{
				// If it is an unvisited background pixel,
				// perform a breadth-first search from it
				bfSearch(image, current, true, visited, part);
				// increment hole count
				++holeCount;
			}
		}
	}
	// Deallocate visited array
	for (int i = 0; i < part.width(); ++i)
		delete[] visited[i];
	delete[] visited;

	return holeCount;
}

/**
 * Finds the straight lines in the letter
 * @return angles of straight lines
 * @todo implement
 */
std::set<unsigned short> Grapheme::findStraightLines() const
{
}

/**
 * Checks for a line of foreground pixels
 * @param x X-coordinate of midpoint of line
 * @param angle Angle of line
 * @return Length of longest dark line
 */
unsigned int Grapheme::checkLine(unsigned int x, unsigned short angle) const
{
	double dY = sin(angle);
	double dX = cos(angle);
	unsigned int lineLength = 0;
	struct
	{
		double x, y;
	} current;

	bool done = false;
	for (current.x = part.width() / 2, current.y = part.height() / 2; !done; current.x
			+= dX, current.y += dY)
	{

	}
}

} // namespace OCR
