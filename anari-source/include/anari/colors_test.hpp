/** Colors Test [Anari]
 * Version: 0.1
 *
 * Tests for the color class
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
#ifndef ANARI_COLORS_TEST_HPP
#define ANARI_COLORS_TEST_HPP

#include "colors.hpp"
#include "pawlib/goldilocks.hpp"
#include "pawlib/goldilocks_assertions.hpp"

// A-tB0200
class Test_CMYKtoRGBA : public Test
{
    protected:
    RGBA rgba_goal;
    CMYK cmyk_start;

    public:
    Test_CMYKtoRGBA()
    :rgba_goal(10, 20, 30, 255),
     cmyk_start(67, 33, 0, 88)
    {}

    testdoc_t get_title() override
    {
        return "Convert CMYK to RGBA";
    }

    testdoc_t get_docs() override
    {
        return "Convert a CMYK value to an RGBA value.";
    }

    bool run() override
    {
        RGBA rgba_test = Color::from_cmyk(cmyk_start);
        PL_ASSERT_EQUAL(rgba_test.red, rgba_goal.red);
        PL_ASSERT_EQUAL(rgba_test.green, rgba_goal.green);
        PL_ASSERT_EQUAL(rgba_test.blue, rgba_goal.blue);
        PL_ASSERT_EQUAL(rgba_test.alpha, rgba_goal.alpha);
        return true;
    }
    ~Test_CMYKtoRGBA() = default;
};

// A-tb0201
class Test_RGBAtoCMYK : public Test
{
    protected:
    CMYK cmyk_goal;
    RGBA rgba_start;


    public:
    Test_RGBAtoCMYK()
    :cmyk_goal(67, 33, 0, 88),
     rgba_start(10, 20, 30, 255)
    {}

    testdoc_t get_title() override
    {
        return "Convert RGBA to CMYK";
    }

    testdoc_t get_docs() override
    {
        return "Convert an RGBA value to a CMYK value.";
    }

    bool run() override
    {
        CMYK cmyk_test = Color::to_cmyk(rgba_start);
        PL_ASSERT_EQUAL(cmyk_test.cyan, cmyk_goal.cyan);
        PL_ASSERT_EQUAL(cmyk_test.magenta, cmyk_goal.magenta);
        PL_ASSERT_EQUAL(cmyk_test.yellow, cmyk_goal.yellow);
        PL_ASSERT_EQUAL(cmyk_test.key, cmyk_goal.key);
        return true;
    }
    ~Test_RGBAtoCMYK() = default;
};

// A-tb0202
class Test_HSLtoRGBA : public Test
{
    protected:
    RGBA rgba_goal;
    HSL hsl_start;

    public:
    Test_HSLtoRGBA()
    :rgba_goal(10, 20, 30, 255),
     hsl_start(210.0,50.0,7.8)
    {}

    testdoc_t get_title() override
    {
        return "Convert HSL to RGBA";
    }

    testdoc_t get_docs() override
    {
        return "Convert an HSL value to an RGBA value.";
    }

    bool run() override
    {
        RGBA rgba_test = Color::from_hsl(hsl_start);
        PL_ASSERT_EQUAL(rgba_test.red, rgba_goal.red);
        PL_ASSERT_EQUAL(rgba_test.green, rgba_goal.green);
        PL_ASSERT_EQUAL(rgba_test.blue,rgba_goal.blue);
        PL_ASSERT_EQUAL(rgba_test.alpha, rgba_goal.alpha);
        return true;
    }

    ~Test_HSLtoRGBA() = default;
};

// A-tb0203
class Test_RGBAtoHSL : public Test
{
    protected:
    HSL hsl_goal;
    RGBA rgba_start;


    public:
    Test_RGBAtoHSL()
    :hsl_goal(210.0, 50.0, 7.8),
     rgba_start(10, 20, 30, 255)
    {}

    testdoc_t get_title() override
    {
        return "Convert RGBA to HSL";
    }

    testdoc_t get_docs() override
    {
        return "Convert an RGBA value to an HSL value.";
    }

    bool run() override
    {
        HSL hsl_test = Color::to_hsl(rgba_start);
        PL_ASSERT_EQUAL(hsl_test.hue, hsl_goal.hue);
        PL_ASSERT_EQUAL(hsl_test.saturation, hsl_goal.saturation);
        PL_ASSERT_EQUAL(hsl_test.luminace, hsl_goal.luminace);
        return true;
    }

    ~Test_RGBAtoHSL() = default;
};

// A-tb0204
class Test_RGBADoubletoRGBA : public Test
{
    protected:
    RGBA rgba_goal;
    RGBADouble rgbadouble_start;

    public:
    Test_RGBADoubletoRGBA()
    :rgba_goal(10, 20, 30, 255),
     rgbadouble_start(0.039, 0.078, 0.118, 1.0)
    {}

    testdoc_t get_title() override
    {
        return "Convert RGBADouble to RGBA";
    }

    testdoc_t get_docs() override
    {
        return "Convert an RGBADouble value to an RGBA value.";
    }

    bool run() override
    {
        RGBA rgba_test = Color::from_rgbadouble(rgbadouble_start);
        PL_ASSERT_EQUAL(rgba_test.red, rgba_goal.red);
        PL_ASSERT_EQUAL(rgba_test.green, rgba_goal.green);
        PL_ASSERT_EQUAL(rgba_test.blue,rgba_goal.blue);
        PL_ASSERT_EQUAL(rgba_test.alpha, rgba_goal.alpha);
        return true;
    }

    ~Test_RGBADoubletoRGBA() = default;
};

// A-tb0205
class Test_RGBAtoRGBADouble : public Test
{
    protected:
    RGBADouble rgbadouble_goal;
    RGBA rgba_start;


    public:
    Test_RGBAtoRGBADouble()
    :rgbadouble_goal(0.039, 0.078, 0.118, 1.0),
     rgba_start(10, 20, 30, 255)
    {}

    testdoc_t get_title() override
    {
        return "Convert RGBA to RGBADouble";
    }

    testdoc_t get_docs() override
    {
        return "Convert an RGBA value to an RGBADouble value.";
    }

    bool run() override
    {
        RGBADouble rgbadouble_test = Color::to_rgbadouble(rgba_start);
        PL_ASSERT_EQUAL(rgbadouble_test.red, rgbadouble_goal.red);
        PL_ASSERT_EQUAL(rgbadouble_test.green, rgbadouble_goal.green);
        PL_ASSERT_EQUAL(rgbadouble_test.blue, rgbadouble_goal.blue);
        PL_ASSERT_EQUAL(rgbadouble_test.alpha, rgbadouble_goal.alpha);
        return true;
    }

    ~Test_RGBAtoRGBADouble() = default;
};

// A-tb0206
class Test_HEXtoRGBA : public Test
{
    protected:
    RGBA rgba_goal;
    unsigned int rgba_start;

    public:
    Test_HEXtoRGBA()
    :rgba_goal(10, 20, 30, 255),
     rgba_start(0xA141EFF)
    {}

    testdoc_t get_title() override
    {
        return "Convert HEX to RGBA";
    }

    testdoc_t get_docs() override
    {
        return "Convert a HEX value to an RGBA value.";
    }

    bool run() override
    {
        RGBA rgba_test = Color::from_hex(rgba_start);
        PL_ASSERT_EQUAL(rgba_test.red, rgba_goal.red);
        PL_ASSERT_EQUAL(rgba_test.green, rgba_goal.green);
        PL_ASSERT_EQUAL(rgba_test.blue,rgba_goal.blue);
        PL_ASSERT_EQUAL(rgba_test.alpha, rgba_goal.alpha);
        return true;
    }

    ~Test_HEXtoRGBA() = default;
};

// A-tb0207
class Test_RGBAtoHEX : public Test
{
    protected:
    unsigned int hex_goal;
    RGBA rgba_start;


    public:
    Test_RGBAtoHEX()
    :hex_goal(0xA141EFF),
     rgba_start(10, 20, 30, 255)
    {}

    testdoc_t get_title() override
    {
        return "Convert RGBA to HEX";
    }

    testdoc_t get_docs() override
    {
        return "Convert an RGBA value to a HEX value.";
    }

    bool run() override
    {
        unsigned int hex_test = Color::to_hex(rgba_start);
        PL_ASSERT_EQUAL(hex_test, hex_goal);
        return true;
    }

    ~Test_RGBAtoHEX() = default;
};


// A-tB0208
class Test_RGBAConstructor : public Test
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int alpha;

    public:
    Test_RGBAConstructor()
    :   red(10), green(20),blue(30), alpha(255)
{}

    testdoc_t get_title() override
    {
        return "Check RGBA Constructor";
    }

    testdoc_t get_docs() override
    {
        return "See if the values sent to the constructor are what it returns.";
    }

    bool run() override
    {
        RGBA rgba_test = RGBA(10,20,30,255);
        PL_ASSERT_EQUAL(rgba_test.red, red);
        PL_ASSERT_EQUAL(rgba_test.green, green);
        PL_ASSERT_EQUAL(rgba_test.blue, blue);
        PL_ASSERT_EQUAL(rgba_test.alpha, alpha);
        return true;
    }
    ~Test_RGBAConstructor() = default;
};

// A-tB0209
class Test_CMYKConstructor : public Test
{
    protected:
    float cyan;
    float magenta;
    float yellow;
    float key;

    public:
    Test_CMYKConstructor()
    :cyan(10.0),magenta(20.0),yellow(30.0), key(15.0)
    {}

    testdoc_t get_title() override
    {
        return "Check CMYK Constructor";
    }

    testdoc_t get_docs() override
    {
        return "See if the values sent to the constructor are what it returns.";
    }

    bool run() override
    {
        CMYK cmyk_test = CMYK(10.0,20.0,30.0,15.0);
        PL_ASSERT_EQUAL(cmyk_test.cyan, cyan);
        PL_ASSERT_EQUAL(cmyk_test.magenta,magenta);
        PL_ASSERT_EQUAL(cmyk_test.yellow, yellow);
        PL_ASSERT_EQUAL(cmyk_test.key,key);
        return true;
    }
    ~Test_CMYKConstructor() = default;
};

// A-tB0210
class Test_HSLConstructor : public Test
{
    protected:
    float hue;
    float saturation;
    float luminace;

    public:
    Test_HSLConstructor()
    :hue(10.0),saturation(20.0),luminace(30.0)
    {}

    testdoc_t get_title() override
    {
        return "Check HSL Constructor";
    }

    testdoc_t get_docs() override
    {
        return "See if the values sent to the constructor are what it returns.";
    }

    bool run() override
    {
        HSL hsl_test = HSL(10.0,20.0,30.0);
        PL_ASSERT_EQUAL(hsl_test.hue, hue);
        PL_ASSERT_EQUAL(hsl_test.saturation, saturation);
        PL_ASSERT_EQUAL(hsl_test.luminace, luminace);
        return true;
    }
    ~Test_HSLConstructor() = default;
};

// A-tB0210
class Test_RGBADoubleConstructor : public Test
{
    protected:
    double red;
    double green;
    double blue;
    double alpha;

    public:
    Test_RGBADoubleConstructor()
    :red(0.5),green(0.4),blue(0.3),alpha(1.0)
    {}

    testdoc_t get_title() override
    {
        return "Check RGBADouble Constructor";
    }

    testdoc_t get_docs() override
    {
        return "See if the values sent to the constructor are what it returns.";
    }

    bool run() override
    {
        RGBADouble rgbadouble_test = RGBADouble(0.5,0.4,0.3,1.0);
        PL_ASSERT_EQUAL(rgbadouble_test.red, red);
        PL_ASSERT_EQUAL(rgbadouble_test.green, green);
        PL_ASSERT_EQUAL(rgbadouble_test.blue, blue);
        PL_ASSERT_EQUAL(rgbadouble_test.alpha, alpha);
        return true;
    }
    ~Test_RGBADoubleConstructor() = default;
};

class TestSuite_Colors : public TestSuite
{
    public:
    TestSuite_Colors() = default;

    testdoc_t get_title() override
    {
        return "Colors Tests";
    }

    void load_tests() override;

    ~TestSuite_Colors() = default;
};


#endif