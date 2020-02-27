#ifndef ANARI_TEST_RENDERER_HPP
#define ANARI_TEST_RENDERER_HPP
#include "anari/renderer.hpp"


class TestRenderer : public Renderer
{
    public:
        TestRenderer();
        ~TestRenderer();

        /// SDL Related calls
        void createTexture(const int, const int) override;
        bool hasHardwareAcceleration() const override;
        void bindRenderer(SDL_Window*) override;
        void initializeDrawingSurface(const int, const int) override;
        void render() override;
        int updateTexture() override;
        void terminateRenderer() override;
        bool isTestRenderer() const override;

        /// Cairo related calls
        void bindSurfaceAndContext() override;
        unsigned char* getSurfaceData() const override;
        void drawCurve(Curve&) override;
        void setLineWidth(const double) override;
        void cleanup() override;
        void sendToDrawingBuffer() override;
        void setDrawingColor(const double, const double, const double, const double) override;
};
#endif