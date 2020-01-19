#include "anari/demo.hpp"
#include <memory>

int Demo::renderDemo()
{
    /// The main window handler
    Window mainWindow(hardcoded::WINDOW_WIDTH, hardcoded::WINDOW_HEIGHT);
    /// Create the renderer and initialize it
    Renderer* renderer = new UniformRenderer(&mainWindow);
    /// Set color and width
    renderer->setDrawingColor(0.3, 0.2, 0.7, 1.0);
    renderer->setLineWidth(2);
    Segment segment;
    // Set start points of the curve
    segment.start(100, 100, 30, 200);
    // Set endpoints of the curve
    segment.end(113, 110, 200, 500);
    // Create the FlexArray to put the curves into the buffer.
    Curve curve;
    curve.push(segment);
    /// Draw everythign in the buffer
    renderer->drawCurve(curve);
    /// Updates the texture
    renderer->updateTexture();
    /// Main program loop that listens for events
    while (1)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                renderer->terminateRenderer();
                renderer->cleanup();
                mainWindow.terminateWindow();
                break;
            }
        }
        renderer->render();
    }
    delete renderer;
    return 0;
}