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

const Grapheme::SymbolInfo Grapheme::syms[] =
{
#include "font.cpp"
		};

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

#define ARRAYSIZE(a) ((sizeof(a))/(sizeof(a[0])))
/**
 * Recognizes the character.
 * @return the character
 */
char Grapheme::Read()
{
	pareDown();

	SymbolInfo theSymbol;
	theSymbol.holes = countHoles();
	//std::set<unsigned char> angles = findStraightLines();

	// Get height/width ratio
	theSymbol.proportion = part.height() / (double) part.width();

	// Find density
	unsigned int pixelCount = 0, foregroundCount = 0;
	for (int x = part.low.x; x <= part.high.x; ++x)
		for (int y = part.low.y; y <= part.high.y; ++y, ++pixelCount)
			if (isForeground(image(x, y)))
				++foregroundCount;
	theSymbol.density = foregroundCount / (double) pixelCount;

	//std::cout << "{' ', " << (int) theSymbol.holes << ", "
	//		<< theSymbol.proportion << ", " << theSymbol.density << "},\n";
	// Find best match
	char bestMatch = '~';
	unsigned bestMatchScore = UINT_MAX;

	for (unsigned int i = 0; i < ARRAYSIZE(syms); ++i)
	{
		unsigned int currentScore = 0;
		currentScore += (abs(syms[i].holes - theSymbol.holes)) * 10000000.0;
		currentScore += (fabs(syms[i].proportion - theSymbol.proportion))
				* 100000.0;
		currentScore += (fabs(theSymbol.density - syms[i].density)) * 10000.0;
		if (currentScore < bestMatchScore)
		{
			bestMatchScore = currentScore;
			bestMatch = syms[i].sym;
		}
	}

	return bestMatch;
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
	// Pare right
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

	// Do a breadth-first search from each background edge pixel
	for (Box::edge_iterator i(part); !i.done(); ++i)
		if (!isForeground(image((*i).x, (*i).y)))
			bfSearch(image, *i, true, visited, part);

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
 */
std::set<unsigned char> Grapheme::findStraightLines() const
{
	static const double SIGNIFICANT_LINE = 0.8;
	std::set<unsigned char> lines;
	unsigned char angle;
	Point current(part.low);
	bool foundLastTime;

	// Check angle 0 with points on the left edge
	for (angle = 0, current = part.low, foundLastTime = false; current.y
			<= part.high.y; ++current.y)
	{
		if (checkLine(current, angle) > SIGNIFICANT_LINE && !foundLastTime)
		{
			lines.insert(angle);
			foundLastTime = true;
		}
		else
			foundLastTime = false;
	}

	// Check angle 90 with points on the bottom edge
	for (angle = 90, current.x = part.low.x, current.y = part.high.y, foundLastTime
			= false; current.x <= part.high.x; ++current.x)
	{
		if (checkLine(current, angle) > SIGNIFICANT_LINE && !foundLastTime)
		{
			lines.insert(angle);
			foundLastTime = true;
		}
		else
			foundLastTime = false;
	}
	// Check angles between 0 and 90 with points on the bottom and left edges
	for (angle = 5; angle < 90; angle += 5)
	{
		foundLastTime = false;
		for (Box::edge_iterator i(part, part.high); i != part.low; ++i)
		{
			if (checkLine(*i, angle) > SIGNIFICANT_LINE && !foundLastTime)
			{
				lines.insert(angle);
				foundLastTime = true;
			}
			else
				foundLastTime = false;
		}
	}
	// Check angles between 90 and 180 with points on the bottom and right edges
	for (angle = 95; angle < 180; angle += 5)
	{

	}
	return lines;
}

/**
 * Checks the density of foreground pixels along a line.
 * @param start     edge point on the line
 * @param angle     angle of the line (0 <= angle < 180)
 * @return density of foreground pixels along the line specified
 */
double Grapheme::checkLine(Point start, unsigned char angle) const
{
	static const double DEG2RAD = 180.0 / (atan(1.0) * 4.0);
	unsigned int pixelCount = 0, foregroundCount = 0;

	// Determine X and Y increments
	double dY = sin(angle * DEG2RAD);
	double dX = cos(angle * DEG2RAD);
	// Increase one of these to 1
	if (dY > dX)
	{
		dX /= dY;
		dY = 1;
	}
	else
	{
		dY /= dX;
		dX = 1;
	}

	// Travel down the line
	for (double curX = start.x, curY = start.y; part.contains(Point(curX, curY)); curX
			+= dX, curY += dY)
	{
		++pixelCount;
		if (isForeground(image(curX, curY)))
			++foregroundCount;
	}
	return foregroundCount / (double) pixelCount;
}

} // namespace OCR
