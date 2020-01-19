#pragma once
#include "renderer.hpp"

class UniformRenderer : public Renderer
{
    private:
        /// SDL Calls
        void bindRenderer(SDL_Window*);
        void createTexture(const int, const int);
        bool hasHardwareAcceleration() const;
        void initializeDrawingSurface(const int, const int);

        /// Cairo calls
        unsigned char* getSurfaceData();
        void sendToDrawingBuffer();
        void bindSurfaceAndContext();

    public:
        explicit UniformRenderer(const Window*);
        virtual ~UniformRenderer();

        /// SDL Related calls
        void render();
        int updateTexture();
        void terminateRenderer();

        /// Cairo related calls
        void drawCurve(Curve&);
        void setLineWidth(const double);
        void setDrawingColor(const double, const double, const double, const double);
        void cleanup();
};