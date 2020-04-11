.. _colors:

Colors
################################

.. _colors_types:

Types Of Colors
================================

Color can handle multiple color formats. Each color format is defined by a
separate class. Presently, Anari can handle the following color formats.

- RGBA
- CMYK
- HSV
- Hex
- RGBA Float


.. _colors_types_rgba:

RGBA
--------------------------------

:abbr:`RGBA (red-green-blue-alpha)` colors are specified with the constructor
:code:`RGBA()`, passing the red, green, blue, and alpha values to the
constructor as integers:

..  code-block:: c++

    int red = 10;
    int green = 50;
    int blue = 90;
    int alpha = 255;
    RGBA mycolor = RGBA(blue, green, blue, alpha);

The RGBA object can be used by itself to represent a constant RGBA color.
However, it's most commonly used when defining or changing a :code:`Color`
value.



.. _colors_types_cmyk:

CMYK
--------------------------------

:abbr:`CMYK (Cyan-Magenta-Yellow-Key)` colors are specified with the constructor
:code:`CMYK()`, passing the Cyan, Magenta, Yellow, and Key values to the
constructor as double:

..  code-block:: c++

    float cyan = 0.5;
    float magenta = 0.4;
    float yellow = 0.3;
    float key = 0.8;
    CMYK cmykColor = CMYK(cyan, magent, yellow, key);

The CMYK object can be used by itself to represent a constant CMYK color.
However, it's most commonly used when defining or changing a :code:`Color`
value. Or when converting between different color types.

.. _colors_types_hsl:

HSL
--------------------------------

:abbr:`HSL (Hue-Saturation-Luminace)` colors are specified with the constructor
:code:`HSL()`, passing the Hue, Saturation, and Luminace values to the
constructor as double:

..  code-block:: c++

    float hue = 0.5;
    float saturation = 0.4;
    float luminace = 0.3;
    HSL hslColor = HSL(hue, saturation, luminace);

The HSL object can be used by itself to represent a constant HSL color.
However, it's most commonly used when defining or changing a :code:`Color`
value. Or when converting between different color types.

.. _colors_types_Hex:

Hex
--------------------------------

:abbr:`Hex()` colors are specified with the constructor
:code:`Hex()`, passing the unsigned int as hex to initialize:

..  code-block:: c++

    unsigned int hexColor = 0x004422AAF;
    Hex(hexColor);

The Hex object can be used by itself to represent a constant Hex color.
Or when converting between different color types. It's common use would
be to provide user to choose color in preferred format.


.. _colors_types_rgbaDouble:

RGBADouble
--------------------------------

:abbr:`RGBADouble (red-green-blue-alpha)` colors are specified with the constructor
:code:`RGBADouble()`, passing the red, green, blue, and alpha values to the
constructor as doubles that will be dealt with by:

..  code-block:: c++

    double red = 10;
    double green = 50;
    double blue = 90;
    double alpha = 255;
    RGBADouble mycolor = RGBADouble(blue, green, blue, alpha);

The RGBADouble object can be used by itself to represent a constant RGBADouble color.
However, it's most commonly used when defining or changing a :code:`Color`
value. And also in rendering
