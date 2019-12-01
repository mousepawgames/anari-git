#include "anari/window.hpp"
#include "anari/hardcoded.hpp"

/** Constructor. Initializes window, renderer, texture and drawing surface
 * \param width of the window
 * \param height of the window
 * \return the drawing surface instance
 */
Window::Window(const int width, const int height)
: windowWidth(width), windowHeight(height), PITCH(windowWidth * BYTES_PER_PIXEL)
{
    createWindow();
    createRenderer();
    createTexture();
    createDrawingSurface();
}

Window::~Window()
{
    terminateProgram();
}

/// Creates of a given width and height
void Window::createWindow()
{
    this->window = SDL_CreateWindow(
        hardcoded::WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->windowWidth,
        this->windowHeight,
        SDL_WINDOW_RESIZABLE
    );
    // TODO: Make sure it throws an exception when it fails
}

/// Creates renderer, if it fails, logs the error and terminates the program
void Window::createRenderer()
{
    if (checkHardwareAcceleration())
    {
        this->renderer = SDL_CreateRenderer(
            this->window,
            SDL_RENDERER_ACCELERATED,
            SDL_RENDERER_TARGETTEXTURE
        );
    }
    else
    {
        this->renderer = SDL_CreateRenderer(
            this->window,
            0,
            SDL_RENDERER_TARGETTEXTURE
        );
    }
    // TODO: Make sure it throws an exception when it fails
}

/// Initializes the SDL Texture with the appropriate flags and size
void Window::createTexture()
{
    texture = SDL_CreateTexture(
        this->renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        this->windowWidth,
        this->windowHeight
    );
    // TODO: Make sure it throws an exception when it fails
}

/// Initializes the SDL Rectangle with the appropriate size
void Window::createDrawingSurface()
{
    this->rect = { 0, 0, this->windowWidth, this->windowHeight };
}

/// Destroys renderer and window and terminates the program.
void Window::terminateProgram()
{
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}

/** Updates the SDL Texture
 * \param surface data from getSurfaceData (class Drawing)
 * \param pitch
 */
int Window::updateTexture(unsigned char* surfaceData)
{
    return SDL_UpdateTexture(
        this->texture,
        &(this->rect),
        surfaceData,
        PITCH
    );
}
/// Makes the necessary render calls for the SDL Window to function
void Window::render()
{
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

/// Check if hardware acceleration setting is enabled, for now it defaults to true
bool Window::checkHardwareAcceleration()
{
    return hardcoded::hardwareAcceleration;
}