#include <SDL2/SDL.h>
class Window
{
    private:
        SDL_Window* window;
        int windowWidth, windowHeight;


        struct Dimensions
        {
            int width;
            int height;

            /// Guaranteed to have correct values, no need for checks
            Dimensions(int w, int h)
            {
                width = w;
                height = h;
            }
        };

    public:
        Window(const int, const int);
        virtual ~Window();
        void createWindow();
        void terminateWindow();
        SDL_Window* getWindowHandle() const;
        Dimensions getWindowSize() const;

};