/**
 * @file Font.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface for the Font class.
 * @see Font.cpp for the implementation.
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

#ifndef OCR_FONT_H_
#define OCR_FONT_H_
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>

namespace OCR
{

/**
 * Represents a font
 */
class Font
{
public:

	/**
	 * Information about a symbol
	 */
	class Symbol
	{
	public:
		/// Number of holes
		unsigned short holes;
		/// Height / width
		double proportion;
		/// Foreground pixels / total pixels
		struct dense
		{
			dense() :
				total(0), border(0), q1(0), q2(0), q3(0), q4(0), mid1(0), mid2(
				        0)
			{
			}
			double total, border, q1, q2, q3, q4, mid1, mid2;
		} density;

		/**
		 * Initializes the data fields
		 */
		Symbol();

		/**
		 * Compares this to another
		 * @param other another Symbol
		 * @return match score, lower is better
		 */
		unsigned match(const Symbol & other) const;

		/**
		 * Adds another symbol's statistics
		 * @param other other symbol
		 * @return this
		 */
		Symbol operator+=(const Symbol & other);

		/**
		 * Divides all statistics by an integer
		 * @param divisor number to divide by
		 * @return this
		 */
		Symbol operator/=(int divisor);

		/**
		 * Reads symbol information from an input stream
		 * @param ins input stream
		 * @param s   symbol
		 * @return input stream
		 */
		friend std::istream & operator>>(std::istream & ins, Symbol & s);

		/**
		 * Writes symbol information to an output stream
		 * @param outs output stream
		 * @param s    symbol
		 * @return output stream
		 */
		friend std::ostream & operator<<(std::ostream & outs, const Font::Symbol & s);
	};

	/**
	 * Loads font information from a file
	 * @param name
	 * @return
	 */
	Font(std::string name);

	/**
	 * Finds the best match for a symbol
	 * @param unknownSymbol statistics on an unknown symbol
	 * @return best matching symbol
	 */
	char bestMatch(const Symbol & unknownSymbol) const;
private:
	/// The symbols of this font
	std::map<char, Symbol> symbols;
};

} // namespace OCR

#endif /*OCR_FONT_H_*/
