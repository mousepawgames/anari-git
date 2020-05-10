#include "anari/demo.hpp"
#include <memory>

int Demo::renderDemo()
{
    // Resolution m_winRes(600, 800);
    // Window m_Window(m_winRes);
    /** NOTE: NOT REQUIRED FOR THIS DEMO
     * The main window handler
     * Window mainWindow();
     * Create the renderer and initialize it
     */
    Renderer* renderer = new TestRenderer(/* &m_Window */);
    /// Set color and width
    renderer->setDrawingColor(0.3, 0.2, 0.7, 1.0);
    renderer->setLineWidth(2);
    Curve curve;
    // Set start points of the curve
    curve.start(100, 100, 30, 200);
    // Set endpoints of the curve
    curve.add(113, 110, 200, 500);
    /// Draw everythign in the buffer
    renderer->drawCurve(curve);
    /// Updates the texture
    renderer->updateTexture();
    /// Main program loop that listens for events
    bool testing = renderer->isTestRenderer();
    while (!testing)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            // m_Window.terminateWindow();
            renderer->terminateRenderer();
            renderer->cleanup();
            break;
        }
        renderer->render();
    }
    delete renderer;
    return 0;
}

void Demo::colors_demo()
{
    RGBA x;
    HSL z;
    z.hue = 210.0;
    z.saturation = 50.0;
    z.luminace = 7.8;
    Color obj;
    x = obj.from_hsl(z);
    ioc << IOFormatTextFG::red << x.red << IOCtrl::endl;
    ioc << IOFormatTextFG::green <<x.green << IOCtrl::endl;
    ioc << IOFormatTextFG::blue <<x.blue << IOCtrl::endl;
}