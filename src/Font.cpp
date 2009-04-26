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
	holes(0), proportion(0), what(' ')
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
	score += fabs(density.total - other.density.total) * 100;
	score += fabs(proportion - other.proportion) * 1000;
	score += fabs(density.border - other.density.border) * 100;
	score += fabs(density.q1 - other.density.q1) * 100;
	score += fabs(density.q2 - other.density.q2) * 100;
	score += fabs(density.q3 - other.density.q3) * 100;
	score += fabs(density.q4 - other.density.q4) * 100;
	//score += fabs(density.diag1 - other.density.diag1) * 100;
	//score += fabs(density.diag1 - other.density.diag1) * 100;
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
	ins >> s.what >> s.holes >> s.proportion >> s.density.total
			>> s.density.border >> s.density.q1 >> s.density.q2 >> s.density.q3
			>> s.density.q4 >> s.density.mid1 >> s.density.mid2;
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
	outs << (int) s.holes << ' ' << s.proportion << ' ' << s.density.total
			<< ' ' << s.density.border << ' ' << s.density.q1 << ' '
			<< s.density.q2 << ' ' << s.density.q3 << ' ' << s.density.q4
			<< ' ' << s.density.mid1 << ' ' << s.density.mid2;
	return outs;
}

}
