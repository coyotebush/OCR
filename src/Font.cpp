/**
 * @file Font.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation for the Font class.
 * @see Font.cpp for the interface.
 * @version $Id$
 */

#include "Font.h"

namespace OCR
{

/**
 * Loads font information from a file
 * @param name font name
 */
Font::Font(std::string name)
{
	name = "font/" + name + ".font";
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
			quadrants(0, 0, 0, 0), what(' ')
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
Font::Symbol::Symbol(unsigned short h, double p, double d, double b, qDense q,
		char c) :
	holes(h), proportion(p), density(d), borderDensity(b), quadrants(q),
			what(c)
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
	score += abs(holes - other.holes) * 1000;
	score += fabs(density - other.density) * 100;
	//score += fabs(proportion - other.proportion) * 1000;
	score += fabs(borderDensity - other.borderDensity) * 100;
	score += fabs(quadrants.a - other.quadrants.a) * 100;
	score += fabs(quadrants.b - other.quadrants.b) * 100;
	score += fabs(quadrants.c - other.quadrants.c) * 100;
	score += fabs(quadrants.d - other.quadrants.d) * 100;
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
/**
 * Writes symbol information to an output stream
 * @param outs output stream
 * @param s    symbol
 * @return output stream
 */
std::ostream & operator<<(std::ostream & outs, Font::Symbol & s)
{
	outs << (int) s.holes << ' ' << s.proportion << ' '
			<< s.density << ' ' << s.borderDensity << ' ' << s.quadrants.a
			<< ' ' << s.quadrants.b << ' ' << s.quadrants.c << ' '
			<< s.quadrants.d;
	return outs;
}

}
