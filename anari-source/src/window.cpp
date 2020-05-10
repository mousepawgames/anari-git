#include "anari/window.hpp"
#include "anari/hardcoded.hpp"


/** Constructor. Initializes window, renderer, texture and drawing surface
 * \param resolution of the window
 * \return the drawing surface instance
 */
Window::Window(Resolution res)
: m_Res(res)
{
    createWindow();
}

/// Copy Constructor
Window::Window(const Window& rhs)
{
    this->m_Window = rhs.m_Window;
    this->m_Res = rhs.m_Res;
}

/// Copy Assignment operator
Window& Window::operator=(const Window& rhs) = default;

/// Destructor
Window::~Window()
{
    terminateWindow();
}

/// Creates of a given width and height
void Window::createWindow()
{
    this->m_Window = SDL_CreateWindow(
        hardcoded::WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_Res.width,
        m_Res.height,
        SDL_WINDOW_RESIZABLE
    );
    // TODO: Make sure it throws an exception when it fails
}


/// Destroys window and terminates the program.
void Window::terminateWindow()
{
    SDL_DestroyWindow(this->m_Window);
    SDL_Quit();
}

/** Gets a pointer to the window handler
 * \return The window
 */
SDL_Window* Window::getWindowHandle() const
{
    return m_Window;
}

/** Gets window width and height
 * \return struct containing width and height
 */
Resolution Window::getWindowSize() const
{
    return m_Res;
}