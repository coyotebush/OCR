/**
 * @file Font.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The implementation for the Font class.
 * @see Font.cpp for the interface.
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
	char character;
	while (infile >> character >> incoming)
		symbols[character] = incoming;
	infile.close();
}

/**
 * Initializes the data fields
 */
Font::Symbol::Symbol() :
	holes(0), proportion(0), density()
{
}

/**
 * Finds the best match for a symbol
 * @param unknownSymbol statistics on an unknown symbol
 * @return best matching symbol
 */
char Font::bestMatch(const Symbol & unknownSymbol) const
{
	char bestMatch;
	unsigned bestMatchScore = UINT_MAX, currentScore;
	for (std::map<char, Symbol>::const_iterator i = symbols.begin(); i
	        != symbols.end(); ++i)
		if ((currentScore = (*i).second.match(unknownSymbol)) < bestMatchScore)
		{
			bestMatchScore = currentScore;
			bestMatch = i->first;
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
	score += abs(holes - other.holes) * 10000;
	score += fabs(density.total - other.density.total) * 100;
	score += fabs(proportion - other.proportion) * 100;
	score += fabs(density.border - other.density.border) * 100;
	score += fabs(density.q1 - other.density.q1) * 100;
	score += fabs(density.q2 - other.density.q2) * 100;
	score += fabs(density.q3 - other.density.q3) * 100;
	score += fabs(density.q4 - other.density.q4) * 100;
	score += fabs(density.mid1 - other.density.mid1) * 100;
	score += fabs(density.mid2 - other.density.mid2) * 100;
	return score;
}

/**
 * Adds another symbol's statistics
 * @param other other symbol
 * @return this
 */
Font::Symbol Font::Symbol::operator+=(const Symbol & other)
{
	holes += other.holes;
	proportion += other.proportion;
	density.total += other.density.total;
	density.border += other.density.border;
	density.q1 += other.density.q1;
	density.q2 += other.density.q2;
	density.q3 += other.density.q3;
	density.q4 += other.density.q4;
	density.mid1 += other.density.mid1;
	density.mid2 += other.density.mid2;
	return *this;
}

/**
 * Divides all statistics by an integer
 * @param divisor number to divide by
 * @return this
 */
Font::Symbol Font::Symbol::operator/=(int divisor)
{
	holes /= divisor;
	proportion /= divisor;
	density.total /= divisor;
	density.border /= divisor;
	density.q1 /= divisor;
	density.q2 /= divisor;
	density.q3 /= divisor;
	density.q4 /= divisor;
	density.mid1 /= divisor;
	density.mid2 /= divisor;
	return *this;
}

/**
 * Reads symbol information from an input stream
 * @param ins input stream
 * @param s   symbol
 * @return input stream
 */
std::istream & operator>>(std::istream & ins, Font::Symbol & s)
{
	ins >> s.holes >> s.proportion >> s.density.total
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
