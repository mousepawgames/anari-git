#ifndef ANARI_WINDOW_HPP
#define ANARI_WINDOW_HPP

#include <SDL2/SDL.h>
#include "anari/geometry.hpp"
class Window
{
    private:
        SDL_Window* m_Window;
        Resolution m_Res;

    public:
        explicit Window(Resolution);
        Window(const Window&);
        Window& operator=(const Window&);
        virtual ~Window();
        void createWindow();
        void terminateWindow();
        SDL_Window* getWindowHandle() const;
        Resolution getWindowSize() const;
};

#endif
