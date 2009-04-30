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
Font::Font(std::string name) :
symbols(100)
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
	holes(0), proportion(0)
{
}

/**
 * Finds the best match for a symbol
 * @param unknownSymbol statistics on an unknown symbol
 * @return best matching symbol
 */
char Font::bestMatch(const Symbol & unknownSymbol) const
{
	Symbol bestMatch;
	unsigned bestMatchScore = UINT_MAX, currentScore;
	for (std::map<char, Symbol>::const_iterator i = symbols.begin(); i
			!= symbols.end(); ++i)
		if ((currentScore = i->first.match(unknownSymbol)) < bestMatchScore)
		{
			bestMatchScore = currentScore;
			bestMatch = i->second;
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
