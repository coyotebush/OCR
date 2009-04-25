/**
 * @file Font.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief The interface for the Font class.
 * @see Font.cpp for the implementation.
 */

#ifndef OCR_FONT_H_
#define OCR_FONT_H_
#include <string>
#include <deque>

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
	struct SymbolInfo
	{
		/// The character
		char what;
		/// Number of holes
		unsigned char holes;
		/// Height / width
		double proportion;
		/// Foreground pixels / total pixels
		double density;
		/// Density of each quadrant
		// a  b
		// c  d
		struct
		{
			double a, b, c, d;
		} quadrants;
		/// Density of border pixels
		double borderDensity;

		/**
		 * Compares this to another
		 * @param other another SymbolInfo
		 * @return match score, lower is better
		 */
		unsigned match(const SymbolInfo & other) const;
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
	SymbolInfo bestMatch (const SymbolInfo & unknownSymbol);
private:
	/// The letters of this font
	const std::deque<SymbolInfo> letters;
};

}

#endif /*OCR_FONT_H_*/
