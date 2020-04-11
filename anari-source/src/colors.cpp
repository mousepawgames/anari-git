#include "anari/colors.hpp"

RGBA Color::from_cmyk(CMYK cmykcolor) noexcept
{
    // Initiating RGBA Colortype
    RGBA rgbacolor;
    //https://www.rapidtables.com/convert/color/cmyk-to-rgb.html
    // Dividing by 100 as the numbers are provided in percentage
    cmykcolor.cyan = cmykcolor.cyan/100;
    cmykcolor.magenta = cmykcolor.magenta/100;
    cmykcolor.yellow = cmykcolor.yellow/100;
    cmykcolor.key = cmykcolor.key/100;
    // Calculating Red Green Blue using the provided formulas
    //R = 255 × (1-C) × (1-K)
    rgbacolor.red = 255*(1 - cmykcolor.cyan)*(1 - cmykcolor.key);
    //G = 255 × (1-M) × (1-K)
    rgbacolor.green = 255*(1 - cmykcolor.magenta)*(1 - cmykcolor.key);
    //B = 255 × (1-Y) × (1-K)
    rgbacolor.blue = 255*(1 - cmykcolor.yellow)*(1 - cmykcolor.key);
    //Setting Alpha to 255 right now for maximum opacity.
    rgbacolor.alpha = 255;
    return rgbacolor;
}

CMYK Color::to_cmyk(RGBA rgbacolor) noexcept
{
    //https://www.rapidtables.com/convert/color/rgb-to-cmyk.html
    // Initiating a CMYK Color type
    CMYK cmykcolor;
    // Dividing by 255 as RGBA is in range of 1 to 255 and formulas require them
    // to be between one and zero
    float red_val = (float(rgbacolor.red) / 255);
    float green_val = (float(rgbacolor.green) / 255);
    float blue_val = (float(rgbacolor.blue) / 255);
    // Using the provided formulas to get the values of Cyan, Magenta, Yellow and Key.

    //K = 1-max(R', G', B')
    cmykcolor.key = 1- MathUtils::maxFloat(red_val,green_val,blue_val);
    //C = (1-R'-K) / (1-K)
    cmykcolor.cyan = (1-red_val-cmykcolor.key) / (1-cmykcolor.key);
    // M = (1-G'-K) / (1-K)
    cmykcolor.magenta = (1-green_val-cmykcolor.key) / (1-cmykcolor.key);
    //Y = (1-B'-K) / (1-K)
    cmykcolor.yellow = (1-blue_val-cmykcolor.key) / (1-cmykcolor.key);
    // Multiplying by 100 and then Rounding off to get the numbers in percentage
    cmykcolor.key = round(cmykcolor.key*100);
    cmykcolor.yellow = round(cmykcolor.yellow*100);
    cmykcolor.magenta = round(cmykcolor.magenta*100);
    cmykcolor.cyan = round(cmykcolor.cyan*100);
    return cmykcolor;
}

HSL Color::to_hsl(RGBA rgbacolor) noexcept
{
    // Initiating hslcolor type
    HSL hslcolor;
    // Converting RGBA values between 0 and 1 by dividing by 255
    float red_val = (float(rgbacolor.red) / 255);
    float green_val = (float(rgbacolor.green) / 255);
    float blue_val = (float(rgbacolor.blue) / 255);
    // Finding minimum and Maximum of RGB values
    float minvalue = MathUtils::minFloat(red_val,green_val,blue_val);
    float maxvalue = MathUtils::maxFloat(red_val,green_val,blue_val);
    // Calculating difference between Maximum and Minimum Values as
    // it is required by the conversion formulas
    float delta = maxvalue-minvalue;
    // Calculating Luminace
    // L = (Cmax + Cmin) / 2
    hslcolor.luminace = MathUtils::roundtoone(((minvalue+maxvalue)/2)*100);
    // Calculating saturation as it depends on minimum and maximum value
    // if maximum and minimum are equal i_e delta equal to zero
    // eqFloat as from Mathutils as it is not possible to compare float directly
    if (MathUtils::eqFloat(minvalue,maxvalue))
    {
        hslcolor.saturation = 0;
    }
    // if there is a difference
    else
    {
        hslcolor.saturation = ((delta/(1-std::abs((2*hslcolor.luminace))-1))*100);
        hslcolor.saturation = MathUtils::roundtoone(abs(round(hslcolor.saturation*100)));
    }

    // Calculating Hue as it depends on minimum and maximum value
    // it is different for different maximums and minimums
    if (maxvalue == red_val)
    {
        hslcolor.hue = MathUtils::roundtoone((abs((green_val-blue_val)/delta)) * 60);
    }
    else if (maxvalue == green_val)
    {
        hslcolor.hue = MathUtils::roundtoone((2.0 + ((blue_val-red_val)/delta)) * 60);
    }
    else if (maxvalue == blue_val)
    {
        hslcolor.hue = MathUtils::roundtoone((4.0 + ((red_val-green_val)/delta)) * 60);
    }
    return hslcolor;
}

RGBA Color::from_hsl(HSL hslcolor) noexcept
{
    // https://dystopiancode.blogspot.com/2012/06/hsv-rgb-conversion-algorithms-in-c.html
    RGBA rgbacolor;
    // Dividing by 100 as the representation is in percentage and the functions deals with values in between 0 and 1
    hslcolor.luminace = hslcolor.luminace / 100;
    hslcolor.saturation = hslcolor.saturation / 100;
    // C = (1 - |2L - 1|) × S
    float chroma = (1-(abs((2*hslcolor.luminace)-1))) * hslcolor.saturation;
    // RGB component with the smallest value
    float minColor = hslcolor.luminace - (chroma/2);
    // Intermediary value used in conversation
    float x = chroma*(1 - abs(fmod((hslcolor.hue / 60), 2.0) - 1 ));

    // All color vawill be at LEAST equal to the smallest RGB component
    float red_val = minColor;
    float green_val = minColor;
    float blue_val = minColor;

    // Adjust color values based on hue
    if (hslcolor.hue >= 0 && hslcolor.hue < 60)
    {
        red_val += chroma;
        green_val += x;
    }
    else if (hslcolor.hue >= 60 && hslcolor.hue < 120)
    {
        red_val += x;
        green_val += chroma;
    }
    else if (hslcolor.hue >= 120 && hslcolor.hue < 180)
    {
        green_val += chroma;
        blue_val += x;
    }
    else if (hslcolor.hue >= 180 && hslcolor.hue < 240)
    {
        green_val += x;
        blue_val += chroma;
    }
    else if (hslcolor.hue >= 240 && hslcolor.hue < 300)
    {
        red_val += x;
        blue_val += chroma;
    }
    else if (hslcolor.hue >= 300 && hslcolor.hue <= 360)
    {
        red_val += chroma;
        blue_val += x;
    }

    // Round all color values up to the next integer.
    rgbacolor.red = round(red_val * 255);
    rgbacolor.green = round(green_val * 255);
    rgbacolor.blue = round(blue_val * 255);
    rgbacolor.alpha = 255;
    return rgbacolor;
}

RGBA Color::from_rgbadouble(RGBADouble rgbadouble) noexcept
{
    // This function is used to divide RGBA values by 255 to move them
    // towards the drawing phase
    RGBA output;
    output.red = round(rgbadouble.red * 255);
    output.green = round(rgbadouble.green * 255);
    output.blue = round(rgbadouble.blue * 255);
    output.alpha = round(rgbadouble.alpha * 255);
    return output;
}

RGBADouble Color::to_rgbadouble(RGBA rgbacolor) noexcept
{
    // This function is used to convert RGBADouble values that are received from
    // the drawing end to values between 1 and 255
    RGBADouble outputRGBA;
    outputRGBA.red = MathUtils::roundtothree((double(rgbacolor.red))/255);
    outputRGBA.green = MathUtils::roundtothree((double(rgbacolor.green))/255);
    outputRGBA.blue = MathUtils::roundtothree((double(rgbacolor.blue))/255);
    outputRGBA.alpha = MathUtils::roundtothree((double(rgbacolor.alpha))/255);
    return outputRGBA;
}
RGBA Color::from_hex(unsigned int hex) noexcept
{
    // To convert HEX color to RGBA this function uses bitshifting for conversion
    RGBA output;
    output.red = (hex >> 24) & 0xFF;
    output.green = (hex >> 16) & 0xFF;
    output.blue = (hex >> 8) & 0xFF;
    output.alpha = (hex) & 0xFF;
    return output;
}

unsigned int Color::to_hex(RGBA rgbacolor) noexcept
{
    // To Convert RGBA to hex this function uses bitshifting
    unsigned int hex = 0;
    hex += (rgbacolor.red << 24);
    hex += (rgbacolor.green << 16);
    hex += (rgbacolor.blue << 8);
    hex += (rgbacolor.alpha);
    return hex;

}

// this function is used to overload the equality operator for RGBA colortype
bool Color::operator==(const RGBA& rhs) const noexcept
{

    if (this->color.red == rhs.red
        && this->color.green == rhs.green
        && this->color.blue == rhs.blue
        && this->color.alpha == rhs.alpha)
    {
        return true;
    }
    return false;
}
// this function is used to overload the equality operator for CMYK colortype
bool Color::operator==(const CMYK& rhs) const noexcept
{
    RGBA rgba = Color::from_cmyk(rhs);
    return (*(this) == rgba);
}
// this function is used to overload the equality operator for HSL colortype
bool Color::operator==(const HSL& rhs) const noexcept
{
    RGBA rgba = Color::from_hsl(rhs);
    return (*(this) == rgba);
}
// this function is used to overload the equality operator for RGBADouble colortype
bool Color::operator==(const RGBADouble& rhs) const noexcept
{
    RGBA rgba = Color::from_rgbadouble(rhs);
    return (*(this) == rgba);
}
// this function is used to overload the equality operator for HEX Type
bool Color::operator==(const unsigned int& rhs) const noexcept
{
    RGBA rgba = Color::from_hex(rhs);
    return (*(this) == rgba);
}
// this function is used to overload the inequality operator for RGBA Type
bool Color::operator!=(const RGBA& rhs) const noexcept
{
    return !(*(this) == rhs);
}

// this function is used to overload the inequality operator for CMYK Type
bool Color::operator!=(const CMYK& rhs) const noexcept
{
    return !(*(this) == rhs);
}

// this function is used to overload the inequality operator for HSL Type
bool Color::operator!=(const HSL& rhs) const noexcept
{
    return !(*(this) == rhs);
}

// this function  used to overload the inequality operator for RGBADouble Type
bool Color::operator!=(const RGBADouble& rhs) const noexcept
{
    return !(*(this) == rhs);
}
// this function is used to overload the inequality operator for HEX Type
bool Color::operator!=(const unsigned int& rhs) const noexcept
{
    return !(*(this) == rhs);
}
// Checking Equality for RGBA
bool operator==(const RGBA& lhs, const Color& rhs) noexcept
{
    return rhs == lhs;
}
// Checking Equality for CMYK
bool operator==(const CMYK& lhs, const Color& rhs) noexcept
{
    return rhs == lhs;
}
// Checking Equality for HSL
bool operator==(const HSL& lhs, const Color& rhs) noexcept
{
    return rhs == lhs;
}
// Checking Equality for RGBADouble
bool operator==(const RGBADouble& lhs, const Color& rhs) noexcept
{
    return rhs == lhs;
}
// // Checking Equality for Hex
bool operator==(const unsigned int& lhs, const Color& rhs) noexcept
{
    return rhs == lhs;
}

// Checking inequality for RGBA
bool operator!=(const RGBA& lhs, const Color& rhs) noexcept
{
    return rhs != lhs;
}
// Checking inequality for CMYK
bool operator!=(const CMYK& lhs, const Color& rhs) noexcept
{
    return rhs != lhs;
}
// Checking inequality for HSL
bool operator!=(const HSL& lhs, const Color& rhs) noexcept
{
    return rhs != lhs;
}
// Checking inequality for RGBADouble
bool operator!=(const RGBADouble& lhs, const Color& rhs) noexcept
{
    return rhs != lhs;
}
// Checking inequality for Hex
bool operator!=(const unsigned int& lhs, const Color& rhs) noexcept
{
    return rhs != lhs;
}