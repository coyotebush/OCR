

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

