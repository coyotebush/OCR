/**
 * @file Font.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface for the Font class.
 * @see Font.cpp for the implementation.
 * @version $Id$
 */

#ifndef OCR_FONT_H_
#define OCR_FONT_H_
#include <string>
#include <deque>
#include <fstream>
#include <iostream>
#include <cmath>

// For font generation
//#define FONTGEN 1

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
	struct Symbol
	{
		/// Number of holes
		unsigned short holes;
		/// Height / width
		double proportion;
		/// Foreground pixels / total pixels
		struct
		{
			double total, border, q1, q2, q3, q4, mid1, mid2;
		} density;


		/// The character
		char what;

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
		friend std::ostream & operator<<(std::ostream & outs, Font::Symbol & s);
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
	Symbol bestMatch(const Symbol & unknownSymbol) const;
private:
	/// The symbols of this font
	std::deque<Symbol> symbols;
};

/**
 * Reads symbol information from an input stream
 * @param ins input stream
 * @param s   symbol
 * @return input stream
 */
std::istream & operator>>(std::istream & ins, Font::Symbol & s);

/**
 * Writes symbol information to an output stream
 * @param outs output stream
 * @param s    symbol
 * @return output stream
 */
std::ostream & operator<<(std::ostream & outs, Font::Symbol & s);

} // namespace OCR

#endif /*OCR_FONT_H_*/
