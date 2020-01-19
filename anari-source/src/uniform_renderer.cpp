#include "anari/uniform_renderer.hpp"
#include "anari/hardcoded.hpp"

/** Constructor. Initializes data fields and makes crucial function calls
 * \param window to bind to
 */
UniformRenderer::UniformRenderer(const Window* windowHandle)
: Renderer(windowHandle)
{
    bindRenderer(m_WindowHandle->getWindowHandle());
    createTexture(m_WindowWidth, m_WindowHeight);
    initializeDrawingSurface(m_WindowWidth, m_WindowHeight);
    bindSurfaceAndContext();
}

/** Initializes the SDL texture of given size with appropriate flags
* \param width
* \param height
*/
void UniformRenderer::createTexture(const int width, const int height)
{
    m_Texture = SDL_CreateTexture(
        this->m_Renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
    );
}

/** Checks if hardware acceleration is enabled by the user
 * \return true if enabled, false otherwise
 */
bool UniformRenderer::hasHardwareAcceleration() const
{
    return hardcoded::hardwareAcceleration;
}

/** Creates the renderer on a given SDL Window
* \param pointer to the window
*/
void UniformRenderer::bindRenderer(SDL_Window* window)
{
    if (hasHardwareAcceleration())
    {
        this->m_Renderer = SDL_CreateRenderer(
            window,
            SDL_RENDERER_ACCELERATED,
            SDL_RENDERER_TARGETTEXTURE
        );
    }
    else
    {
        this->m_Renderer = SDL_CreateRenderer(
            window,
            0,
            SDL_RENDERER_TARGETTEXTURE
        );
    }
}

/** Initializes a drawing surface of a given size (call only once)
* \param width
* \param height
*/
void UniformRenderer::initializeDrawingSurface(const int width, const int height)
{
    m_DrawingSurface = { 0, 0, width, height };
}

/// Makes the necessary render calls
void UniformRenderer::render()
{
    SDL_RenderClear(m_Renderer);
    SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
    SDL_RenderPresent(m_Renderer);
}

/** Updates the texture, should be called before render
* \param cairo surface data
* \return 0 on success, -1 on failure
*/
int UniformRenderer::updateTexture()
{
    /// This is a fairly slow function call, do not overuse unless specifically required
    return SDL_UpdateTexture(
        this->m_Texture,
        &(this->m_DrawingSurface),
        getSurfaceData(),
        this->PITCH
    );
}

/// Destructor
UniformRenderer::~UniformRenderer() {}

/// Terminates the renderer
void UniformRenderer::terminateRenderer()
{
    SDL_DestroyTexture(m_Texture);
    SDL_DestroyRenderer(m_Renderer);
}

/// Binds the surface and context
void UniformRenderer::bindSurfaceAndContext()
{
    this->m_Surface = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32,
        m_WindowWidth,
        m_WindowHeight
    );
    this->m_Context = cairo_create(m_Surface);
}

/** Gets the necessary data for cairo's draw calls
 * \return surface data
 */
unsigned char* UniformRenderer::getSurfaceData()
{
    return cairo_image_surface_get_data(m_Surface);
}

/** Draws curves
 * \param FlexArray containing the curve segments. (typedef as Curve)
 */
void UniformRenderer::drawCurve(Curve& curve)
{
    cairo_move_to(this->m_Context, curve[0].x1, curve[0].y1);
    cairo_curve_to(
        this->m_Context,
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
            this->m_Context,
            curve[i].cx1,
            curve[i].cy1,
            curve[i].cx2,
            curve[i].cy2,
            curve[i].x2,
            curve[i].y2
        );
    }
    sendToDrawingBuffer();
}

/// Draws everything in the current buffer
void UniformRenderer::sendToDrawingBuffer()
{
    cairo_stroke(m_Context);
}

/** Sets the width of the line for drawing
 * \param line width
 */
void UniformRenderer::setLineWidth(const double width)
{
    cairo_set_line_width(m_Context, width);
}

/** Sets the color
 * \param red (0.0 to 1.0)
 * \param green (0.0 to 1.0)
 * \param blue (0.0 to 1.0)
 * \param alpha (0.0 to 1.0)
 */
void UniformRenderer::setDrawingColor(
    const double red,
    const double green,
    const double blue,
    const double alpha
)
{
    cairo_set_source_rgba(m_Context, red, green, blue, alpha);
}

/// Destroys the context and surface for cleanup
void UniformRenderer::cleanup()
{
    cairo_destroy(m_Context);
    cairo_surface_destroy(m_Surface);
}