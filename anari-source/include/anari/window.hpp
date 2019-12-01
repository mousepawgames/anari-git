#include <SDL2/SDL.h>
class Window
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect rect;
        SDL_Texture* texture;
        int windowWidth, windowHeight;
        const int BYTES_PER_PIXEL = 4;
        const int PITCH;

    public:
        Window(const int, const int);
        virtual ~Window();
        void createWindow();
        void createTexture();
        void createRenderer();
        void createDrawingSurface();
        void terminateProgram();
        void render();
        int updateTexture(unsigned char*);
        bool checkHardwareAcceleration();
};