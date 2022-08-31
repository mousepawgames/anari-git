/** Colors [Anari]
 * Version: 0.1
 *
 * Store and convert between color formats.
 *
 * Author(s): Muhammad Adeel Hussain, Graham Mix
 */

/* LICENSE
 * Copyright (C) 2020 MousePaw Media.
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

#ifndef ANARI_StaticLayer_HPP
#define ANARI_StaticLayer_HPP

#include "pawlib/flex_array.hpp"

#include "colors.hpp"
#include "geometry.hpp"

class StaticLayer
{
private:
	/// The color of the outline.
	Color stroke_color;
	/// The color for the fill.
	Color fill_color;

	/// The geometric data for the static layer.
	Curve curve;

public:
	/** Default Constructor
	 */
	StaticLayer();  // Defaults Registration Points to 0,0
	StaticLayer(float red,
				float green,
				float blue,
				float alpha);  // Sets registration Points
	~StaticLayer();

	/* TODO: Would it be worth having an Attribute class that
	 * stores Stroke Color, Fill color, and anything else that
	 * we add to Attributes later? (This can be done in a later
	 * Differential).
	 */

	/** Get stroke color
	 * \return the color of the stroke
	 */
	const Color& get_stroke_color() const noexcept;

	/** Get Fill Color
	 * \return color of the fill
	 */
	const Color& get_fill_color() const noexcept;

	/** Returns the curve stored in this static layer.
	 * \return curve object
	 */
	const Curve& get_geometry() const noexcept;
};

#endif