#include <SDL2/SDL.h>
#include <cairo/cairo.h>


class Renderer
{
    public:
        /** Constructor. Initializes the renderer
         * \param Window object (NOT SDL WINDOW*)
         * \return The renderer
         */
        explicit Renderer(Window window)
        : m_Texture(nullptr), PITCH(BYTES_PER_PIXEL * window.getWindowSize().width)
        {
            bindRenderer(window.getWindowHandle());
            initializeDrawingSurface(
                    window.getWindowSize().width,
                    window.getWindowSize().height
                );
        }
        /// Move constructor
        Renderer(Renderer&& lhs) = default;
        /// Copy consturctor, prevents copies
        /*
            Copy preventation is important because if one copy goes out of scope,
            it will call the destructor which would destroy the renderer and
            texture.
        */
        Renderer(const Renderer& rhs) = delete;

        virtual ~Renderer()
        {
            terminateRenderer();
        }

        /** Initializes the SDL texture of given size with appropriate flags
         * \param width
         * \param height
         */
        void createTexture(const int width, const int height)
        {
            m_Texture = SDL_CreateTexture(
                this->m_Renderer,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                width,
                height
            );
        }



        /// TODO: Will be pulled from user config in the future
        bool hasHardwareAcceleration()
        {
            return hardcoded::hardwareAcceleration;
        }



        /// Makes the necessary render calls
        void render()
        {
            SDL_RenderClear(this->m_Renderer);
            SDL_RenderCopy(this->m_Renderer, this->m_Texture, NULL, NULL);
            SDL_RenderPresent(this->m_Renderer);
        }

        /** Updates the texture, should be called before render
         * \param cairo surface data
         * \return 0 on success, -1 on failure
         */
        int updateTexture(unsigned char* surfaceData)
        {
            /// This is a fairly slow function call, do not overuse unless specifically required
            return SDL_UpdateTexture(
                this->m_Texture,
                &(this->m_DrawingSurface),
                surfaceData,
                this->PITCH
            );
        }

        /// Terminates the renderer, this call should happen before the window is terminated
        void terminateRenderer()
        {
            SDL_DestroyRenderer(this->m_Renderer);
            SDL_DestroyTexture(this->m_Texture);
        }

    protected:
        SDL_Renderer* m_Renderer;
        SDL_Texture* m_Texture;
        SDL_Rect m_DrawingSurface;
        static const int BYTES_PER_PIXEL = 4;
        const int PITCH;



        /** Creates the renderer on a given SDL Window
         * \param The window pointer
         */
        void bindRenderer(SDL_Window* window)
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
        void initializeDrawingSurface(const int width, const int height)
        {
            this->m_DrawingSurface = { 0, 0, width, height };
        }
};


class SDLRenderer : public Renderer
{

};