#include "anari/drawing.hpp"
#include <cairo/cairo.h>

/**
 * \param window width
 * \param window height
 */
Drawing::Drawing(const int width, const int height)
//: width(width), height(height)
{
    this->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    this->context = cairo_create(surface);
}

/// Destroys context and surface for cleanup
void Drawing::cleanup()
{
    cairo_destroy(this->context);
    cairo_surface_destroy(this->surface);
}

/** Gets surface data required for SDL to update the texture
 * \return the data for updating the texture
 */
unsigned char* Drawing::getSurfaceData()
{
    return cairo_image_surface_get_data(this->surface);
}

/** Sets the width of the line for drawing
 * \param line width
 */
void Drawing::setLineWidth(const double width)
{
    cairo_set_line_width(this->context, width);
}

/** Sets the color
 * \param red (0.0 to 1.0)
 * \param green (0.0 to 1.0)
 * \param blue (0.0 to 1.0)
 * \param alpha (0.0 to 1.0)
 */
void Drawing::setDrawingColor(
        double red,
        double green,
        double blue,
        double alpha
    )
{
    cairo_set_source_rgba(this->context, red, green, blue, alpha);
}

/// Draws everything in the current cairo buffer
void Drawing::sendToBuffer()
{
    cairo_stroke(this->context);
}

/** Draws curves
 * \param FlexArray containing the curve segments. (typedef as Curve)
 */
void Drawing::drawCurve(Curve& curve)
{
    cairo_move_to(context, curve[0].x1, curve[0].y1);
    cairo_curve_to(
        context,
        curve[0].cx1,
        curve[0].cy1,
        curve[0].cx2,
        curve[0].cy2,
        curve[0].x2,
        curve[0].y2
        );
    /// Draw all curves within the flexArray
    for (size_t i = 1; i < curve.length(); ++i)
    {
        cairo_curve_to(
            this->context,
            curve[i].cx1,
            curve[i].cy1,
            curve[i].cx2,
            curve[i].cy2,
            curve[i].x2,
            curve[i].y2
        );
    }
    sendToBuffer();
}

Drawing::~Drawing()
{
    this->cleanup();
}
