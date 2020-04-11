/** Colors [Anari]
 * Version: 0.1
 *
 * Store and convert between color formats.
 *
 * Author(s): Muhammad Adeel Hussain
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

#ifndef ANARI_COLORS_HPP
#define ANARI_COLORS_HPP

#include <math.h>
#include "anari/math.hpp"

struct CMYK
{
    float cyan;
    float magenta;
    float yellow;
    float key;

    CMYK()
    : cyan(0.0), magenta(0.0), yellow(0.0), key(1.0)
    {}

    CMYK(float cyan, float magenta, float yellow, float key)
    : cyan(cyan), magenta(magenta), yellow(yellow), key(key)
    {}
};

struct RGBA
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;

    RGBA()
    : red(0), green(0), blue(0), alpha(255)
    {}

    RGBA(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
    : red(red), green(green), blue(blue), alpha(alpha)
    {}

    RGBA(const RGBA& cpy)
    : red(cpy.red), green(cpy.green), blue(cpy.blue), alpha(cpy.alpha)
    {}

    RGBA& operator=(const RGBA& cpy)
    {
        red = cpy.red;
        green = cpy.green;
        blue = cpy.blue;
        alpha= cpy.alpha;
        return *(this);
    }
};
struct RGBADouble
{
    double red;
    double green;
    double blue;
    double alpha;

    RGBADouble()
    : red(0.0), green(0.0), blue(0.0), alpha(1.0)
    {}

    RGBADouble(double red, double green, double blue, double alpha)
    : red(red), green(green), blue(blue), alpha(alpha)
    {}
};

struct HSL
{
    float hue;
    float saturation;
    float luminace;

    HSL()
    : hue(0), saturation(0), luminace(0)
    {}

    HSL(float hue, float saturation, float luminace)
    : hue(hue), saturation(saturation), luminace(luminace)
    {}
};

class Color
{
    protected:
    RGBA color;
    /* defnition of different color systems
    RGB          Solid color (A=255)
    RBGA         A = Alpha = Transparency/Opacity (see-through)
    HSL (HSV)    Hue, Saturation, Lightness (Value)
    Hex          Another way to represent RGB/RGBA
                  (255,0,144,255) -> 0xFF 0x00 0x90 0xFF -> 0xFF0090FF
                  (255,0,144) -> 0xFF 0x00 0x90 -> 0xFF0090
    CMYK         Cyan, Magenta, Yellow, Key
    */
   public:
    /** Convert to CMYK
      * \param the color in RGBA
      */
    static CMYK to_cmyk (RGBA) noexcept;
    /** Convert from CMYK
      * \param the color in CMYK
      */
    static RGBA from_cmyk (CMYK) noexcept;
    /** Conver to HSL
      * \param the color in RGBA
      */
    static HSL to_hsl(RGBA) noexcept;
    /** Convert from HSL
      * \param the color in HSL
      */
    static RGBA from_hsl(HSL) noexcept;
    /** Convert from rgbadouble
      * \param the color in RGBADouble
      */
    static RGBA from_rgbadouble(RGBADouble) noexcept;
    /** Convert to RGBADouble
      * \param the color in RGBA
      */
    static RGBADouble to_rgbadouble(RGBA) noexcept;
    /** Convert from Hex
      * \param the color in Hex
      */
    static RGBA from_hex(unsigned int) noexcept;
    /** Convert to Hex
      * \param the color in RGBA
      */
    static unsigned int to_hex(RGBA) noexcept;

    /// Default constructor.
    Color()
    : color()
    {}

    /// Copy constructor
    explicit Color(const Color& cpy)
    : color(cpy.color)
    {}

    /** Initialize from RGBA
      * \param the color in RGBA
      */
    explicit Color (const RGBA& rgba)
    : color(rgba)
    {}

    /** Initialize from CMYK
      * \param the color in CMYK
      */
    explicit Color (const CMYK& cmyk)
    : color(Color::from_cmyk(cmyk))
    {}

    /** Initialize from RGBADouble
      * \param the color in RGBA as doubles
      */
    explicit Color (const RGBADouble& rgbadouble)
    : color(Color::from_rgbadouble(rgbadouble))
    {}

    /** Initialize from HSL
      * \param the color in HSL
      */
    explicit Color (const HSL& hsl)
    : color(Color::from_hsl(hsl))
    {}
    /** Initialize from HEX
      * \param the color in HEX
      */
    explicit Color (const unsigned int& hex)
    : color(Color::from_hex(hex))
    {}

    // Assignment operators
    Color& operator=(const RGBA& rhs) noexcept
    {
        this->color = rhs;
        return *this;
    }

    Color& operator=(const CMYK& rhs) noexcept
    {
        this->color = Color::from_cmyk(rhs);
        return *this;
    }

    Color& operator=(const HSL& rhs) noexcept
    {
        this->color = Color::from_hsl(rhs);
        return *this;
    }

    Color& operator=(const RGBADouble& rhs) noexcept
    {
        this->color = Color::from_rgbadouble(rhs);
        return *this;
    }

    Color& operator=(const unsigned int& rhs) noexcept
    {
        this->color = Color::from_hex(rhs);
        return *this;
    }

    // Copy Assignment Operator

    Color& operator=(const Color& rhs)
    {
        this->color = rhs;
        return *this;
    }

    // Casting operators
    operator RGBA() const noexcept
    {
        return this->color;
    }

    operator CMYK() const noexcept
    {
        return Color::to_cmyk(this->color);
    }

    operator HSL() const noexcept
    {
        return Color::to_hsl(this->color);
    }

    operator RGBADouble() const noexcept
    {
        return Color::to_rgbadouble(this->color);
    }

    operator unsigned int() const noexcept
    {
        return Color::to_hex(this->color);
    }

    // Comparison operators
    bool operator==(const RGBA& rhs) const noexcept;
    bool operator==(const CMYK& rhs) const noexcept;
    bool operator==(const HSL& rhs) const noexcept;
    bool operator==(const RGBADouble& rhs) const noexcept;
    bool operator==(const unsigned int& rhs) const noexcept;

    bool operator!=(const RGBA& rhs) const noexcept;
    bool operator!=(const CMYK& rhs) const noexcept;
    bool operator!=(const HSL& rhs) const noexcept;
    bool operator!=(const RGBADouble& rhs) const noexcept;
    bool operator!=(const unsigned int& rhs) const noexcept;

    friend bool operator==(const RGBA& lhs, const Color& rhs) noexcept;
    friend bool operator==(const CMYK& lhs, const Color& rhs) noexcept;
    friend bool operator==(const HSL& lhs, const Color& rhs) noexcept;
    friend bool operator==(const RGBADouble& lhs, const Color& rhs) noexcept;
    friend bool operator==(const unsigned int& lhs, const Color& rhs) noexcept;

    friend bool operator!=(const RGBA& lhs, const Color& rhs) noexcept;
    friend bool operator!=(const CMYK& lhs, const Color& rhs) noexcept;
    friend bool operator!=(const HSL& lhs, const Color& rhs) noexcept;
    friend bool operator!=(const RGBADouble& lhs, const Color& rhs) noexcept;
    friend bool operator!=(const unsigned int& lhs, const Color& rhs) noexcept;

    ~Color() = default;
};

#endif