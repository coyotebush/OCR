// This file contains old unused functions for reference while reconstructing them

bool TextPage::isForeground(Pixel point)
{
	RGBApixel * pixel = inputImage(point.x, point.y);
	return (pixel->Red < 100 && pixel->Green < 100 && pixel->Blue < 100);
}

bool TextPage::isVisited(TextPage::Pixel p)
{
	if (visited[p.x][p.y])
		return true;
	visited[p.x][p.y] = true;
	return false;
}

TextPage::Pixel TextPage::nextNeighbor(TextPage::Pixel p)
{
	static int lowY, highX, highY, currentX, currentY;
	static Pixel thePixel(-1, -1);

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
	return Pixel(currentX, currentY);
}

TextPage::Box TextPage::findContiguousShape(TextPage::Pixel start)
{
	// Initialize queue and box
	std::queue<Pixel> Q;
	Box letter(start.x, start.y, start.x, start.y);
	// The pixel to be used as a template for coloring visited pixels
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
		*(outputImage(p.x, p.y)) = visitedTemplate;
		// Extend the current letter Box if necessary
		if (p.x < letter.low.x)
			letter.low.x = p.x;
		if (p.x > letter.high.x)
			letter.high.x = p.x;
		if (p.y < letter.low.y)
			letter.low.y = p.y;
		if (p.y > letter.high.y)
			letter.high.y = p.y;
		// Get all its neighbors
		for (int i = 0; i < 9; i++)
		{
			Pixel n = nextNeighbor(p);
			if (!isVisited(n) && isForeground(n))
				Q.push(n);
		}
	}
	return letter;
}

/**
 * Performs a breadth-first search among similar pixels
 * @param start starting pixel
 * @param searchtype see Search_Type
 * @param[out] extent extent of search
 * @param end ending pixel for TO_PIXEL
 * @return whether destination (if any) reached
 */
bool Grapheme::breadthFirstSearch(const Point start, Search_Type searchtype,
		Box& extent, const Point end)
{
	// Initialize queue and box
	std::queue<Point> Q;
	// Keep track of which pixels have been visited
	int width = right - left;
	std::vector<bool> visited(width * (bottom - top));

	// Add the starting pixel to the queue
	Q.push(start);

	while (!Q.empty())
	{
		// Take a pixel
		Point p = Q.front();
		Q.pop();
		// Is this an ending point
		if (p.x == left || p.x == right - 1 || p.y == top || p.y == bottom - 1)
			return true; // Yay
		// Extend the current extent Box if necessary
		if (p.x < extent.low.x)
			extent.low.x = p.x;
		if (p.x > extent.high.x)
			extent.high.x = p.x;
		if (p.y < extent.low.y)
			extent.low.y = p.y;
		if (p.y > extent.high.y)
			extent.high.y = p.y;
		// Get all its neighbors
		int lowX = (p.x - 1 > left ? p.x - 1 : left);
		int highX = (p.x + 1 < right - 1 ? p.x + 1 : right - 1);
		int lowY = (p.y - 1 > top ? p.y - 1 : top);
		int highY = (p.y + 1 < bottom - 1 ? p.y + 1 : bottom);
		for (int x = lowX; x <= highX; ++x)
		{
			for (int y = lowY; y <= highY; ++y)
			{
				Point n(x, y);
				if (!visited[width * (y - top) + (x - left)] && isSimilar(
						image(start.x, start.y), image(n.x, n.y)))
				{
					Q.push(n);
					visited[width * (y - top) + (x - left)] = true;
				}
			}
		}
	}
	return false;
}
/**
 * Finds the extent of a contiguous shape
 * starting at a certain point
 * @param start starting Point
 * @return extent of shape
 */
Box Grapheme::findContiguousShape(const Point start)
{
	// Initialize queue and box
	std::queue<Point> Q;
	Box extent(start.x, start.y, start.x, start.y);
	// Keep track of which pixels have been visited
	int width = right - left;
	std::vector<bool> visited(width * (bottom - top));

	// Add the starting pixel to the queue
	Q.push(start);

	while (!Q.empty())
	{
		// Take a pixel
		Point p = Q.front();
		Q.pop();
		// Extend the current extent Box if necessary
		if (p.x < extent.low.x)
			extent.low.x = p.x;
		if (p.x > extent.high.x)
			extent.high.x = p.x;
		if (p.y < extent.low.y)
			extent.low.y = p.y;
		if (p.y > extent.high.y)
			extent.high.y = p.y;
		// Get all its neighbors
		int lowX = (p.x - 1 > left ? p.x - 1 : left);
		int highX = (p.x + 1 < right - 1 ? p.x + 1 : right - 1);
		int lowY = (p.y - 1 > top ? p.y - 1 : top);
		int highY = (p.y + 1 < bottom - 1 ? p.y + 1 : bottom);
		for (int x = lowX; x <= highX; ++x)
		{
			for (int y = lowY; y <= highY; ++y)
			{
				Point n(x, y);
				if (!visited[width * (y - top) + (x - left)] && isSimilar(
						image(start.x, start.y), image(n.x, n.y)))
				{
					Q.push(n);
					visited[width * (y - top) + (x - left)] = true;
				}
			}
		}
	}
	return extent;
}

/**
 * Determines whether one point is reachable
 * from another using pixels of similar color.
 * @param start starting point
 * @param end   starting point
 * @return
 */
bool Grapheme::isReachable(Point start, Point end)
{
	// Initialize queue
	std::queue<Point> Q;
	// Keep track of which pixels have been visited
	int width = right - left;
	std::vector<bool> visited(width * (bottom - top));

	// Add the starting pixel to the queue
	Q.push(start);

	while (!Q.empty())
	{
		// Take a pixel
		Point p = Q.front();
		Q.pop();
		// Is this the pixel we wanted?
		if (p == end)
			return true; // Yay
		// Get all its neighbors
		int lowX = (p.x - 1 > left ? p.x - 1 : left);
		int highX = (p.x + 1 < right - 1 ? p.x + 1 : right - 1);
		int lowY = (p.y - 1 > top ? p.y - 1 : top);
		int highY = (p.y + 1 < bottom - 1 ? p.y + 1 : bottom);
		for (int x = lowX; x <= highX; ++x)
		{
			for (int y = lowY; y <= highY; ++y)
			{
				Point n(x, y);
				if (!visited[width * (y - top) + (x - left)] && isSimilar(
						image(start.x, start.y), image(n.x, n.y)))
				{
					Q.push(n);
					visited[width * (y - top) + (x - left)] = true;
				}
			}
		}
	}
	// Now we have looked at all similar pixels reachable
	// from the starting point and have not found the end point
	return false;
}

/**
 * Determines whether a pixel at the edge of the bounding box
 * is reachable from another pixel
 * @param start starting point
 * @return whether edge reachable
 */
bool Grapheme::isEdgeReachable(const Point start)
{
	// Initialize queue
	std::queue<Point> Q;
	// Keep track of which pixels have been visited
	int width = right - left;
	std::vector<bool> visited(width * (bottom - top));

	// Add the starting pixel to the queue
	Q.push(start);

	while (!Q.empty())
	{
		// Take a pixel
		Point p = Q.front();
		Q.pop();
		// Is this at the edge?
		if (p.x == left || p.x == right - 1 || p.y == top || p.y == bottom - 1)
			return true; // Yay
		// Get all its neighbors
		int lowX = (p.x - 1 > left ? p.x - 1 : left);
		int highX = (p.x + 1 < right - 1 ? p.x + 1 : right - 1);
		int lowY = (p.y - 1 > top ? p.y - 1 : top);
		int highY = (p.y + 1 < bottom - 1 ? p.y + 1 : bottom);
		for (int x = lowX; x <= highX; ++x)
		{
			for (int y = lowY; y <= highY; ++y)
			{
				Point n(x, y);
				if (!visited[width * (y - top) + (x - left)] && isSimilar(
						image(start.x, start.y), image(n.x, n.y)))
				{
					Q.push(n);
					visited[width * (y - top) + (x - left)] = true;
				}
			}
		}
	}
	// Now we have looked at all similar pixels reachable
	// from the starting point and have not found the end point
	return false;
}

