/**
 * @file Reader.h
 * @author Corey Ford <fordco@sonoma.edu>
 * @date Spring 2009
 * @brief The interface and documentation of the Reader class.
 * @see Reader.h for the implementation.
 */
/*
 * Copyright 2009 Corey Ford
 *
 * This file is part of Ocular Conformation Resolver.
 *
 * Ocular Conformation Resolver is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ocular Conformation Resolver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ocular Conformation Resolver.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OCR_H_
#define OCR_H_
#include <queue>
#include <string>
using std::string;
#include "EasyBMP/EasyBMP.h"

class Reader
{
public:
	/**
	 * Initializes the class.
	 */
	Reader();

	/**
	 * Initializes the class and loads the image
	 * from the specified file
	 * @param[in] filename Filename of existing BMP file
	 * @see LoadFile
	 */
	Reader(string filename);

	/**
	 * Loads the image from the specified file
	 * @param[in] filename Filename of existing BMP file
	 */
	void LoadFile (string filename);

	/**
	 * Writes the resulting image
	 * to the specified file.
	 * @param[in] filename Filename for new BMP file
	 */
	void WriteOut (string filename);

	/* Recognize
	 * Processes the input image.
	 * Returns the number of letters in the input image.
	 * The output image will also be modified,
	 * with foreground pixels colored
	 * and bounding boxes drawn around the letters
	 */
	int Recognize ();

private:
	/* Pixel class
	 * Represents the position
	 * of a pixel in the image
	 */
	struct Pixel
	{
		Pixel (int left, int top) : x (left), y(top) {}
		bool operator!= (const Pixel & rhs) const
		{ return this->x != rhs.x || this->y != rhs.y; }
		int x, y;
	};

	/* Box class
	 * Represents a rectangle,
	 * such as the extent of a letter
	 */
	struct Box
	{
		Box (int x1, int y1, int x2, int y2) :
			low (x1, y1), high (x2, y2) {}
		Pixel low, high;
	};

	/* isForeground
	 * Returns whether the specified Pixel
	 * is a foreground pixel.
	 */
	bool isForeground (Pixel point);

	/* isVisited
	 * Returns whether the specified Pixel
	 * has been marked as visited, and marks
	 * it as visited if it is not.
	 */
	bool isVisited (Pixel p);

	/* nextNeighbor
	 * Returns the next neighbor of the specified Pixel
	 */
	Pixel nextNeighbor (Pixel p);

	/* processLetter
	 * Finds the extent of a letter, starting
	 * at the specified Pixel.
	 * Returns a Box representing the extent
	 * of the letter
	 */
	Box processLetter (Pixel start);

	/* drawBoundingBox
	 * Draws a box surrounding the
	 * specified Box,
	 * on the output image.
	 * The Box may extend to the edge of the image,
	 * but it is assumed not to extend beyond
	 * the edge of the image.
	 */
	void drawBoundingBox (Box box);

	BMP inputImage; // the input image
	BMP outputImage;// the output image
	bool ** visited;// array indicating which pixels have been visited
};

#endif /*OCR_H_*/
