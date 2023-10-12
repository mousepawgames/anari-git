/** Math Utilities [Anari]
 * Version: 0.1
 *
 * Generic math functions for use throughout Anari.
 *
 * Author(s): Muhammad Adeel Hussain, Jason C. McDonald
 */

/* LICENSE
 * Copyright (C) 2019 MousePaw Media.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ANARI_MATH_HPP
#define ANARI_MATH_HPP

#include <math.h>

class MathUtils
{
public:
	/** Return the largest of three float values.
	 * \param first float value to compare
	 * \param second float value to compare
	 * \param third float value to compare
	 * \return the largest of the three float values.
	 */
	static float maxFloat(float, float, float);

	/** Return the smallest of three float values.
	 * \param first float value to compare
	 * \param second float value to compare
	 * \param third float value to compare
	 * \return the smallest of the three float values.
	 */
	static float minFloat(float, float, float);

	/** Compares two floats.
	 * \param first float value to compare
	 * \param second float value to compare
	 * \return 0 if equal, -1 if first float is greater, 1 if second float is
	 * greater
	 */
	static int cmpFloat(float, float);

	/** Checks if two floats are equal, accounting for epsilon.
	 * \param first float value to compare
	 * \param second float value to compare
	 */
	static bool eqFloat(float, float);

	/** Round of to three decimal places
	 * \param first float or double value to round of
	 */

	static float roundtothree(float);
	static double roundtothree(double);
	static float roundtoone(float);
	static double roundtoone(double);
};

#endif