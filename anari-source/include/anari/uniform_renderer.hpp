#ifndef ANARI_UNIFORM_RENDERER_HPP
#define ANARI_UNIFORM_RENDERER_HPP

#include "renderer.hpp"

class UniformRenderer : public Renderer
{
    private:
        /// SDL Calls
        void bindRenderer(SDL_Window*) override;
        void createTexture(const int, const int) override;
        bool hasHardwareAcceleration() const override;
        void initializeDrawingSurface(const int, const int) override;

        /// Cairo calls
        unsigned char* getSurfaceData() const override;
        void sendToDrawingBuffer() override;
        void bindSurfaceAndContext() override;

    public:
        explicit UniformRenderer(const Window*);
        virtual ~UniformRenderer();

        /// SDL Related calls
        void render() override;
        int updateTexture() override;
        void terminateRenderer() override;
        bool isTestRenderer() const override;

        /// Cairo related calls
        void drawCurve(Curve&) override;
        void setLineWidth(const double) override;
        void setDrawingColor(const double, const double, const double, const double) override;
        void cleanup() override;
};

#endif