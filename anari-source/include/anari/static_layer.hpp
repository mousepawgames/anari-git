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

#ifndef ANARI_STATIC_LAYER_HPP
#define ANARI_STATIC_LAYER_HPP

class static_layer
{
private:
    struct points{
        float x;
        float y;
    };

    struct offset{
        float x;
        float y;
        float angle;
    };

    struct colorAttributes{
        float hue;
        float saturation;
        float brightness;
    };


public:
    static_layer(/* args */);
    ~static_layer();

    /*functions related to child classes*/

    virtual void geometryInstantiation();
    virtual void setOffset();
    virtual offset getOffset();
    virtual void colorCurves();
    virtual void setRegistrationPoints();
    virtual void getRegistationPoints();
    virtual colorAttributes getcolorAttributes();
    virtual void setcolorAttributes();
};


#endif