#include "anari/window.hpp"
#include "anari/hardcoded.hpp"


/** Constructor. Initializes window, renderer, texture and drawing surface
 * \param width of the window
 * \param height of the window
 * \return the drawing surface instance
 */
Window::Window(const int width, const int height)
: windowWidth(width), windowHeight(height)
{
    createWindow();
}

/// Copy Constructor
Window::Window(const Window& rhs)
{
    this->window = rhs.window;
    this->windowWidth = rhs.windowWidth;
    this->windowHeight = rhs.windowHeight;
}

/// Copy Assignment operator
Window& Window::operator=(const Window&) noexcept = default;

/// Destructor
Window::~Window()
{
    terminateWindow();
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


/// Destroys window and terminates the program.
void Window::terminateWindow()
{
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

/** Gets a pointer to the window handler
 * \return The window
 */
SDL_Window* Window::getWindowHandle() const
{
    return window;
}

/** Gets window width and height
 * \return struct containing width and height
 */
Window::Dimensions Window::getWindowSize() const
{
    return Dimensions{windowWidth, windowHeight};
}