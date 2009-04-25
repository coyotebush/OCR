/**
 * @file Font.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation for the Font class.
 * @see Font.cpp for the interface.
 */

#include "Font.h"

namespace OCR
{

/**
 * Loads font information from a file
 * @param name
 * @return
 */
Font::Font(const std::string name)
{
	std::ifstream infile(name.c_str());
	Symbol incoming;
	while (infile >> incoming)
		symbols.push_back(incoming);
	infile.close();
}

/**
 * Initializes the data fields
 */
Font::Symbol::Symbol() :
	holes(0), proportion(0), density(0), borderDensity(0),
			quadrants(0, 0, 0, 0)
{
}

/**
 * Sets the data fields
 * @param h number of holes
 * @param p proportion
 * @param d overall density
 * @param b border density
 * @param q quadrant densities
 * @param c character
 */
Font::Symbol::Symbol(unsigned char h, double p, double d, double b, qDense q,
		char c) :
	holes(h), proportion(p), density(d), borderDensity(b), quadrants(q)
{
}

/**
 * Finds the best match for a symbol
 * @param unknownSymbol statistics on an unknown symbol
 * @return best matching symbol
 */
Font::Symbol Font::bestMatch(const Symbol & unknownSymbol) const
{
	Symbol bestMatch;
	unsigned bestMatchScore = UINT_MAX, currentScore;
	for (std::deque<Symbol>::const_iterator i = symbols.begin(); i
			!= symbols.end(); ++i)
		if ((currentScore = i->match(unknownSymbol)) < bestMatchScore)
		{
			bestMatchScore = currentScore;
			bestMatch = *i;
		}
	return bestMatch;
}

/**
 * Compares this to another
 * @param other another Symbol
 * @return match score, lower is better
 */
unsigned Font::Symbol::match(const Font::Symbol & other) const
{
	unsigned score = 0;
	score += abs(holes - other.holes) * 1000000;
	score += fabs(density - other.density) * 1000;
	score += fabs(proportion - other.proportion) * 1000;
	score += fabs(borderDensity - other.borderDensity) * 1000;
	score += fabs(quadrants.a - other.quadrants.a) * 1000;
	score += fabs(quadrants.b - other.quadrants.b) * 1000;
	score += fabs(quadrants.c - other.quadrants.c) * 1000;
	score += fabs(quadrants.d - other.quadrants.d) * 1000;
	return score;
}

/**
 * Reads symbol information from an input stream
 * @param ins input stream
 * @param s   symbol
 * @return input stream
 */
std::istream & operator>>(std::istream & ins, Font::Symbol & s)
{
	ins >> s.what >> s.holes >> s.proportion >> s.density >> s.borderDensity
			>> s.quadrants.a >> s.quadrants.b >> s.quadrants.c >> s.quadrants.d;
	return ins;
}

}
