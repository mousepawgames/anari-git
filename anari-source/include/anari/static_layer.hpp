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

#include "colors.hpp"
#include "nimbly/flexarray.hpp"
#include "geometry.hpp"

class StaticLayer
{
private:

    Color object_color;
    FlexArray<Coordinate> transformation_points;
    FlexArray<Coordinate> object_points;

public:
    StaticLayer(/* args */); // Defaults Registration Points to 0,0
    StaticLayer(float red, float green, float blue, float alpha); // Sets registration Points
    ~StaticLayer();

    //functions related to child classes
    Color& get_color();
    FlexArray<Coordinate> get_transformation_points();
    FlexArray<Coordinate> get_object_points();

};//
/*
[x1y1, x1y2, x1y3]
*/


#endif