/**
 * @file Letter.h
 * @date Spring 2009
 * @author Corey Ford <fordco@sonoma.edu>
 * @brief
 */
/*
 * Copyright 2009 Corey Ford
 *
 * This file is part of Omophagic Content Reader.
 *
 * Omophagic Content Reader is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Omophagic Content Reader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Omophagic Content Reader.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LETTER_H_
#define LETTER_H_
namespace OCR
{

/**
 * A letter in the image.
 */
class Letter
{
public:
	Letter();
	virtual ~Letter();
};

}; // namespace GraphemeResolver

#endif /* LETTER_H_ */
