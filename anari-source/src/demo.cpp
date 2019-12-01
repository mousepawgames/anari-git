#include "anari/demo.hpp"

int Demo::renderDemo()
{
    Window mainWindow(hardcoded::WINDOW_WIDTH, hardcoded::WINDOW_HEIGHT);
    Drawing master(hardcoded::WINDOW_WIDTH, hardcoded::WINDOW_HEIGHT);
    // Set color
    master.setDrawingColor(0.7, 0.2, 0.2, 1.0);
    master.setLineWidth(2);
    Segment segment;
    // Set start points of the curve
    segment.start(100, 100, 30, 200);
    // Set endpoints of the curve
    segment.end(113, 110, 200, 500);
    // Create the FlexArray to put the curves into the buffer.
    Curve curve;
    curve.push(segment);
    master.drawCurve(curve);
    // Get necessary surface data for updating the texture
    unsigned char* data = master.getSurfaceData();
    // Update
    mainWindow.updateTexture(data);
    while (1)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                mainWindow.terminateProgram();
                break;
            }
        }
        mainWindow.render();
    }
    return 0;
}