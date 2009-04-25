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
#include <cmath>

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
		/// The character
		char what;
		/// Number of holes
		unsigned char holes;
		/// Height / width
		double proportion;
		/// Foreground pixels / total pixels
		double density;
		/// Density of border pixels
		double borderDensity;
		/// Density of each quadrant
		// a  b
		// c  d
		struct qDense
		{
			qDense(int m, int n, int o, int p) :
				a(m), b(n), c(o), d(p)
			{
			}
			double a, b, c, d;
		} quadrants;

		/**
		 * Initializes the data fields
		 */
		Symbol();

		/**
		 * Sets the data fields
		 * @param h number of holes
		 * @param p proportion
		 * @param d overall density
		 * @param b border density
		 * @param q quadrant densities
		 * @param c character
		 */
		Symbol(unsigned char h, double p, double d, double b, qDense q, char c =
				' ');

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
	};

	/**
	 * Loads font information from a file
	 * @param name
	 * @return
	 */
	Font(const std::string name);

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

} // namespace OCR

#endif /*OCR_FONT_H_*/
