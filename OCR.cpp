/**
 * @file OCR.cpp
 * @author Corey Ford <fordco@sonoma.edu>
 * @date Spring 2009
 * @brief The implementation of the OCR class.
 * @see OCR.h for the interface and documentation.
 */
/*
 * Copyright 2009 Corey Ford
 *
 * This file is part of OCR.
 *
 * OCR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OCR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OCR.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "OCR.h"

/* Constructor */
OCR::OCR()
{
}

/* Constructor
 * Parameter: filename
 * Loads the image from the
 * specified file
 */
OCR::OCR(string filename)
{
	LoadFile (filename);
}

/* LoadFile
 * Loads the image from the
 * specified file
 */
void OCR::LoadFile (string filename)
{
	static bool visitedInitAlready = false;
	// Read file
	bool loadResult = inputImage.ReadFromFile (filename.c_str());

	// Deallocate memory if it has been allocated before
	if (visitedInitAlready)
	{
		for (int i = 0; i < inputImage.TellWidth(); ++i)
			delete [] visited[i];
		delete [] visited;
	}
	// Initialize visited array
	visited = new bool* [inputImage.TellWidth()];
	for (int i = 0; i < inputImage.TellWidth(); ++i)
	{
		visited[i] = new bool [inputImage.TellHeight()];
		for (int j = 0; j < inputImage.TellHeight(); ++j)
			visited[i][j] = false;
	}
	visitedInitAlready = true;
}

/* WriteOut
 * Writes the resulting image
 * to the specified file
 */
void OCR::WriteOut (string filename)
{
	outputImage.WriteToFile(filename.c_str());
}

/* Recognize
 * Processes the input image.
 * Returns the number of letters in the input image.
 * The output image will also be modified,
 * with foreground pixels colored
 * and bounding boxes drawn around the letters
 */
int OCR::Recognize ()
{
	// Initialize output image as a copy of the input image
	outputImage.SetSize(inputImage.TellWidth(), inputImage.TellHeight());
	RangedPixelToPixelCopy (inputImage,
			0, inputImage.TellWidth(), inputImage.TellHeight(), 0,
			outputImage,
			0, 0);
	// Initialize variables
	int letterCount = 0;
	bool ** visited = new bool* [inputImage.TellWidth()];
	for (int i = 0; i < inputImage.TellWidth(); i++)
	{
		visited[i] = new bool [inputImage.TellHeight()];
		for (int j = 0; j < inputImage.TellHeight(); j++)
			visited[i][j] = false;
	}
	// Start scanning
	for (int i = 0; i < inputImage.TellWidth(); i++)
		for (int j = 0; j < inputImage.TellHeight(); j++)
		{
			Pixel current (i, j);
			if (!isVisited(current) && isForeground (current))
			{
				letterCount++;
				Box letter = processLetter(current);
				drawBoundingBox(letter);
			}
		}
	return letterCount;
}

/* isForeground
 * Returns whether the specified Pixel
 * is a foreground pixel.
 */
bool OCR::isForeground (Pixel point)
{
	RGBApixel * pixel = inputImage(point.x, point.y);
	return (pixel->Red < 100 && pixel->Green < 100 && pixel->Blue < 100);
}

/* isVisited
 * Returns whether the specified Pixel
 * has been marked as visited, and marks
 * it as visited if it has not.
 */
bool OCR::isVisited (OCR::Pixel p)
{
	if (visited[p.x][p.y])
		return true;
	visited[p.x][p.y] = true;
	return false;
}

/* nextNeighbor
 * Returns the next neighbor of the specified Pixel
 */
OCR::Pixel OCR::nextNeighbor (OCR::Pixel p)
{
	static int lowY, highX, highY, currentX, currentY;
	static Pixel thePixel (-1, -1);

	if (p != thePixel)
	// New pixel, Recalculate boundaries
	{
		thePixel = p;
		lowY = (p.y > 0 ? p.y - 1 : p.y);
		highX = (p.x < outputImage.TellWidth() - 1 ? p.x + 1 : p.x);
		highY = (p.y < outputImage.TellHeight() - 1 ? p.y + 1 : p.y);
		currentX = (p.x > 0 ? p.x - 1 : p.x);
		currentY = lowY;
	}
	++currentY;
	if (currentY > highY)
	// We have passed the right-hand boundary,
	// reset Y and increment X.
	{
		currentY = lowY;
		if (currentX < highX)
			++currentX;
	}
	return Pixel (currentX, currentY);
}
/* processLetter
 * Finds the extent of a letter, starting
 * at the specified Pixel, then draws a box
 * around it
 */
OCR::Box OCR::processLetter (OCR::Pixel start)
{
	// Initialize queue and box
	std::queue<Pixel> Q;
	Box letter (start.x, start.y, start.x, start.y);
	// The pixel to be used as a template for coloring
	// visited pixels
	RGBApixel visitedTemplate;
	visitedTemplate.Red = 0;
	visitedTemplate.Green = 135;
	visitedTemplate.Blue = 0;
	visitedTemplate.Alpha = 0;

	// Add the starting pixel to the queue
	Q.push(start);

	while (!Q.empty())
	{
		// Take a pixel
		Pixel p = Q.front();
		Q.pop();
		// Color it green
		*(outputImage (p.x, p.y)) = visitedTemplate;
		// Extend the current letter Box if necessary
		if (p.x < letter.low.x)  letter.low.x  = p.x;
		if (p.x > letter.high.x) letter.high.x = p.x;
		if (p.y < letter.low.y)  letter.low.y  = p.y;
		if (p.y > letter.high.y) letter.high.y = p.y;
		// Get all its neighbors
		for (int i = 0; i < 9; i++)
		{
			Pixel n = nextNeighbor(p);
			if (!isVisited(n) && isForeground (n))
				Q.push (n);
		}
	}
	return letter;
}

/* drawBoundingBox
 * Draws a box surrounding the
 * specified Box,
 * on the output image.
 * The Box may extend to the edge of the image,
 * but it is assumed not to extend beyond
 * the edge of the image.
 */
void OCR::drawBoundingBox (OCR::Box box)
{
	RGBApixel borderTemplate;
	borderTemplate.Red = 255;
	borderTemplate.Green = 0;
	borderTemplate.Blue = 0;
	borderTemplate.Alpha = 0;

	// Draw top border
	if (box.low.y > 0)
		for (int i = box.low.x; i <= box.high.x; ++i)
			*(outputImage (i, box.low.y - 1)) = borderTemplate;
	// Draw bottom border
	if (box.high.y < outputImage.TellHeight() - 1)
		for (int i = box.low.x; i <= box.high.x; ++i)
			*(outputImage (i, box.high.y + 1)) = borderTemplate;
	// Draw left border
	if (box.low.x > 0)
		for (int i = box.low.y; i <= box.high.y; ++i)
			*(outputImage(box.low.x - 1, i)) = borderTemplate;
	// Draw right border
	if (box.high.x < outputImage.TellWidth() - 1)
		for (int i = box.low.y; i <= box.high.y; ++i)
			*(outputImage(box.high.x + 1, i)) = borderTemplate;
	// Draw corners
	if (box.low.x > 0 && box.low.y > 0)
		*(outputImage(box.low.x - 1, box.low.y - 1)) = borderTemplate;
	if (box.low.x > 0 && box.high.y < outputImage.TellHeight() - 1)
		*(outputImage(box.low.x - 1, box.high.y + 1)) = borderTemplate;
	if (box.high.x < outputImage.TellWidth() - 1 && box.low.y > 0)
		*(outputImage(box.high.x + 1, box.low.y - 1)) = borderTemplate;
	if (box.high.x < outputImage.TellWidth() - 1 && box.high.y < outputImage.TellHeight() - 1)
		*(outputImage(box.high.x + 1, box.high.y + 1)) = borderTemplate;
}
