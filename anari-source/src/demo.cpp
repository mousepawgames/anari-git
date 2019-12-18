#include "anari/demo.hpp"

int Demo::renderDemo()
{
    /// The main window handler
    Window mainWindow(hardcoded::WINDOW_WIDTH, hardcoded::WINDOW_HEIGHT);
    /// Create the renderer
    Renderer* renderer = new Renderer(mainWindow);
    renderer->createTexture(hardcoded::WINDOW_WIDTH, hardcoded::WINDOW_HEIGHT);
    /// Initializing object for Cairo draw calls
    Drawing draw(hardcoded::WINDOW_WIDTH, hardcoded::WINDOW_HEIGHT);
    // Set color
    draw.setDrawingColor(0.7, 0.2, 0.2, 1.0);
    draw.setLineWidth(2);
    Segment segment;
    // Set start points of the curve
    segment.start(100, 100, 30, 200);
    // Set endpoints of the curve
    segment.end(113, 110, 200, 500);
    // Create the FlexArray to put the curves into the buffer.
    Curve curve;
    curve.push(segment);
    /// Draw everythign in the buffer
    draw.drawCurve(curve);
    /// Get necessary surface data for updating the texture
    unsigned char* data = draw.getSurfaceData();
    /// Update the texture
    renderer->updateTexture(data);
    /// Main program loop that listens for events
    while (1)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                /// Order here is important
                renderer->terminateRenderer();
                mainWindow.terminateWindow();
                break;
            }
        }
        renderer->render();
    }
    return 0;
}