#ifndef ANARI_RENDERER_HPP
#define ANARI_RENDERER_HPP

#include <SDL2/SDL.h>
#include <cairo/cairo.h>

#include "anari/geometry.hpp"
#include "anari/window.hpp"

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
	virtual void setDrawingColor(const double,
								 const double,
								 const double,
								 const double) = 0;
};

#endif