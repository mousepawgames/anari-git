#include <cairo/cairo.h>

#include "pawlib/flex_array.hpp"

struct Segment
{
    double x1, y1;
    double cx1, cy1;
    double x2, y2;
    double cx2, cy2;

    // Setter for start points of the curve
    void start(double x, double y, double cx, double cy)
    {
        x1 = x;
        y1 = y;
        cx1 = cx;
        cy1 = cy;
    }
    // Setter for the end points of the curve
    void end(double x, double y, double cx, double cy)
    {
        x2 = x;
        y2 = y;
        cx2 = cx;
        cy2 = cy;
    }
};

typedef FlexArray<Segment> Curve;

class Drawing
{
    private:
        //const int width, height;
        cairo_t* context;
        cairo_surface_t* surface;

    public:
        Drawing(const int, const int);
        virtual ~Drawing();
        unsigned char* getSurfaceData();
        void drawCurve(Curve&);
        void setLineWidth(const double);
        void cleanup();
        void sendToBuffer();
        void setDrawingColor(double, double, double, double);
};