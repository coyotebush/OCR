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
 * @param f font to use
 */
Grapheme::Grapheme(BMP & img, const Font & f) :
	image(img), part(0, 0, image.TellWidth() - 1, image.TellHeight() - 1),
	        font(f)
{
}

/**
 * Initializes the object using part of a BMP image
 * @param[in] img reference to BMP
 * @param[in] x1  left coordinate
 * @param[in] y1  top coordinate
 * @param[in] x2  right coordinate
 * @param[in] y2  bottom coordinate
 * @param[in] f   font to use
 */
Grapheme::Grapheme(BMP & img, int x1, int y1, int x2, int y2, const Font & f) :
	image(img), part(x1, y1, x2, y2), font(f)
{
}

/**
 * Initializes the object using part of a BMP image
 * @param[in] img reference to BMP
 * @param[in] box part of image
 * @param[in] f   font to use
 */
Grapheme::Grapheme(BMP & img, const Box & box, const Font & f) :
	image(img), part(box), font(f)
{
}

/**
 * Initializes the object as a copy of another
 * @param other a Grapheme object
 */
Grapheme::Grapheme(const Grapheme & other) :
	image(other.image), part(other.part), font(other.font)
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
 */
char Grapheme::Read()
{
	pareDown();

	theSymbol.holes = countHoles();

	// Get height/width ratio
	theSymbol.proportion = part.height() / (double) part.width();

	// Find density
	theSymbol.density.total = areaDensity(part);

	// Find density of border
	unsigned pixelCount = 0;
	unsigned foregroundCount = 0;
	for (Box::edge_iterator i(part); !i; ++i, ++pixelCount)
		if (isForeground(image(i->x, i->y)))
			++foregroundCount;
	theSymbol.density.border = foregroundCount / (double) pixelCount;

	// Find density of each quadrant
	unsigned midWidth = part.low.x + ((part.high.x - part.low.x) / 2);
	unsigned midHeight = part.low.y + ((part.high.y - part.low.y) / 2);
	theSymbol.density.q2 = areaDensity(Box(
	        part.low.x,
	        part.low.y,
	        midWidth,
	        midHeight));
	theSymbol.density.q1 = areaDensity(Box(
	        midWidth,
	        part.low.y,
	        part.high.x,
	        midHeight));
	theSymbol.density.q3 = areaDensity(Box(
	        part.low.x,
	        midHeight,
	        midWidth,
	        part.high.y));
	theSymbol.density.q4 = areaDensity(Box(
	        midWidth,
	        midHeight,
	        part.high.x,
	        part.high.y));

	// Find density of diagonals
	/*theSymbol.density.diag1 = checkLine(part.high, atan(part.height()
	 / (-part.width())));
	 theSymbol.density.diag2 = checkLine(Point(part.low.x, part.high.y), atan(
	 part.height() / part.width()));*/

	// Find density of middle points
	theSymbol.density.mid1 = areaDensity(Box(
	        midWidth,
	        part.low.y,
	        midWidth,
	        part.high.y));
	theSymbol.density.mid2 = areaDensity(Box(
	        part.low.x,
	        midHeight,
	        part.high.x,
	        midHeight));

	// Find best match
	return font.bestMatch(theSymbol);
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
		for (unsigned col = part.low.x; col <= part.high.x && !fgFound; ++col)
			if (isForeground(image(col, part.low.y)))
				fgFound = true;
		if (fgFound)
			break;
	}
	// Pare bottom
	for (fgFound = false; part.high.y >= part.low.y && !fgFound; --part.high.y)
	{
		for (unsigned col = part.low.x; col <= part.high.x && !fgFound; ++col)
			if (isForeground(image(col, part.high.y)))
				fgFound = true;
		if (fgFound)
			break;
	}
	// Pare left
	for (fgFound = false; part.low.x <= part.high.x; ++part.low.x)
	{
		for (unsigned row = part.low.y; row <= part.high.y && !fgFound; ++row)
			if (isForeground(image(part.low.x, row)))
				fgFound = true;
		if (fgFound)
			break;
	}
	// Pare right
	for (fgFound = false; part.high.x >= part.low.x; --part.high.x)
	{
		for (unsigned row = part.low.y; row <= part.high.y && !fgFound; ++row)
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
unsigned char Grapheme::countHoles() const
{
	unsigned char holeCount = 0;
	// Initialize visited array
	bool ** visited = new bool *[part.width()];
	for (int i = 0; i < part.width(); ++i)
	{
		visited[i] = new bool[part.height()];
		for (int j = 0; j < part.height(); ++j)
			visited[i][j] = false;
	}

	// Do a breadth-first search from each unvisited background edge pixel
	for (Box::edge_iterator i(part); !i; ++i)
		if (!isForeground(image(i->x, i->y)) && !visited[(*i).x
		        - part.low.x][i->y - part.low.y])
			floodFill(image, *i, true, visited, part);

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
				floodFill(image, current, true, visited, part);
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
 * Checks the density of foreground pixels within an area
 * @param area area to check
 * @return density of foreground pixels
 */
double Grapheme::areaDensity(Box area) const
{
	unsigned pixelCount = 0, foregroundCount = 0;
	Point current(area.low);
	for (; current.x <= area.high.x; ++current.x)
		for (current.y = area.low.y; current.y <= area.high.y; ++current.y, ++pixelCount)
			if (isForeground(image(current.x, current.y)))
				++foregroundCount;
	return foregroundCount / (double) pixelCount;
}

} // namespace OCR
