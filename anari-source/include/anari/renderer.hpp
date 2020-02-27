#ifndef ANARI_RENDERER_HPP
#define ANARI_RENDERER_HPP

#include <SDL2/SDL.h>
#include <cairo/cairo.h>
#include "anari/window.hpp"
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

class Renderer
{
    protected:
        const Window* m_WindowHandle;
        static const int BYTES_PER_PIXEL = 4;
        int m_WindowWidth;
        int m_WindowHeight;
        const int PITCH;
        SDL_Renderer* m_Renderer;
        SDL_Texture* m_Texture;
        SDL_Rect m_DrawingSurface;
        cairo_t* m_Context;
        cairo_surface_t* m_Surface;

    public:
        Renderer();
        explicit Renderer(const Window*);
        virtual ~Renderer();
        /// SDL Related calls
        virtual void createTexture(const int, const int) = 0;
        virtual bool hasHardwareAcceleration() const = 0;
        virtual void bindRenderer(SDL_Window*) = 0;
        virtual void initializeDrawingSurface(const int, const int) = 0;
        virtual void render() = 0;
        virtual int updateTexture() = 0;
        virtual void terminateRenderer() = 0;
        virtual bool isTestRenderer() const = 0;

        /// Cairo related calls
        virtual void bindSurfaceAndContext() = 0;
        virtual unsigned char* getSurfaceData() const;
        virtual void drawCurve(Curve&) = 0;
        virtual void setLineWidth(const double) = 0;
        virtual void cleanup() = 0;
        virtual void sendToDrawingBuffer() = 0;
        virtual void setDrawingColor(const double, const double, const double, const double) = 0;
};

#endif