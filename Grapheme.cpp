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
{ 'A', 1, 1.5, 0.265 },
{ 'B', 2, 1.875, 0.383333 },
{ 'C', 0, 1.57895, 0.222807 },
{ 'D', 1, 1.57895, 0.307018 },
{ 'E', 0, 2, 0.308889 },
{ 'F', 0, 2.30769, 0.274359 },
{ 'G', 0, 1.5, 0.263333 },
{ 'H', 0, 1.66667, 0.3 },
{ 'I', 0, 6, 0.473333 },
{ 'J', 0, 3.75, 0.4 },
{ 'K', 0, 1.66667, 0.294444 },
{ 'L', 0, 2.14286, 0.242857 },
{ 'M', 0, 1.42857, 0.365079 },
{ 'N', 0, 1.66667, 0.377778 },
{ 'O', 1, 1.42857, 0.260317 },
{ 'P', 1, 2, 0.304444 },
{ 'Q', 1, 1.42857, 0.284127 },
{ 'R', 1, 1.66667, 0.311111 },
{ 'S', 0, 1.875, 0.2875 },
{ 'T', 0, 1.5, 0.171667 },
{ 'U', 0, 1.66667, 0.281481 },
{ 'V', 0, 1.5, 0.23 },
{ 'W', 0, 1.03448, 0.28046 },
{ 'X', 0, 1.36364, 0.221212 },
{ 'Y', 0, 1.42857, 0.166667 },
{ 'Z', 0, 1.57895, 0.259649 },
{ 'a', 1, 1.66667, 0.362667 },
{ 'b', 1, 1.9375, 0.330645 },
{ 'c', 0, 1.78571, 0.251429 },
{ 'd', 1, 1.9375, 0.330645 },
{ 'e', 1, 1.5625, 0.315 },
{ 'f', 0, 2.81818, 0.272727 },
{ 'g', 1, 1.5625, 0.46 },
{ 'h', 0, 2.06667, 0.305376 },
{ 'i', 0, 10.3333, 0.709677 },
{ 'j', 0, 5.16667, 0.483871 },
{ 'k', 0, 2.06667, 0.296774 },
{ 'l', 0, 10.3333, 0.774194 },
{ 'm', 0, 1, 0.3104 },
{ 'n', 0, 1.66667, 0.330667 },
{ 'o', 1, 1.5625, 0.32 },
{ 'p', 1, 1.5625, 0.4125 },
{ 'q', 1, 1.5625, 0.4125 },
{ 'r', 0, 2.5, 0.288 },
{ 's', 0, 1.92308, 0.32 },
{ 't', 0, 2.63636, 0.285266 },
{ 'u', 0, 1.66667, 0.328 },
{ 'v', 0, 1.47059, 0.24 },
{ 'w', 0, 1.08696, 0.302609 },
{ 'x', 0, 1.5625, 0.275 },
{ 'y', 0, 1.5625, 0.3075 },
{ 'z', 0, 1.78571, 0.288571 },
{ '0', 1, 1.4375, 0.410326 },
{ '1', 0, 1.76923, 0.374582 },
{ '2', 0, 1.53333, 0.376812 },
{ '3', 0, 1.53333, 0.356522 },
{ '4', 1, 1.4375, 0.388587 },
{ '5', 0, 1.53333, 0.382609 },
{ '6', 1, 1.4375, 0.429348 },
{ '7', 0, 1.53333, 0.281159 },
{ '8', 2, 1.4375, 0.464674 },
{ '9', 1, 1.4375, 0.404891 },
{ ';', 0, 6, 0.34375 },
{ '.', 0, 4, 0.333333 },
{ '|', 0, 10.6667, 1 },
{ '!', 0, 10.3333, 0.645161 },
{ '@', 1, 1.07143, 0.333333 },
{ '#', 1, 1.40909, 0.244868 },
{ '$', 2, 2.13333, 0.339583 },
{ '%', 2, 1.14815, 0.237754 },
{ '^', 0, 1.72222, 0.0949821 },
{ '&', 1, 1.40909, 0.266862 },
{ '*', 0, 2.21429, 0.165899 },
{ '(', 0, 4.57143, 0.352679 },
{ ')', 0, 4.57143, 0.352679 },
{ '_', 0, 0.117647, 1 },
{ '+', 0, 1.4, 0.167857 },
{ '-', 0, 2.25, 0.111111 },
{ '=', 0, 1.15, 0.173913 } };

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

	// Find best match
	char bestMatch;
	long double bestMatchScore = UINT_MAX;

	for (unsigned int i = 0; i < (sizeof(syms)/sizeof(syms[0])); ++i)
	{
		long double currentScore = 0;
		currentScore += abs(syms[i].holes - theSymbol.holes);
		currentScore += abs(syms[i].proportion - theSymbol.proportion);
		currentScore += abs(syms[i].density - theSymbol.density);
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
	/*for (Point current(part.low.x, part.low.y); current.x <= part.high.x; ++current.x)
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
	 bfSearch(image, current, true, visited, part);*/

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
	static const double PI = atan(1.0) * 4.0;
	static const double DEG2RAD = 180.0 / PI;
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
