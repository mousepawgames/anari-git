#include "anari/test_renderer.hpp"
#include "anari/hardcoded.hpp"
#include <thread>
#include <chrono>


TestRenderer::TestRenderer()
//: Renderer(m_WindowHandle)
{
    createTexture(m_WindowWidth, m_WindowHeight);
    initializeDrawingSurface(m_WindowWidth, m_WindowHeight);
    bindSurfaceAndContext();
}

/// Destructor
TestRenderer::~TestRenderer() {}

/** Logs texture width and height
 * \param width of texture
 * \param length of texture
 */
void TestRenderer::createTexture(const int width, const int height)
{
    std::cout << "Texture Width: "<< width
              << "\nTexture Height: " << height << '\n';
}

void TestRenderer::bindRenderer(SDL_Window* dummy)
{
    /// NOTE: Doesn't have to be filled
    std::cout << dummy << '\n';
}

/// Logs new width of line
void TestRenderer::setLineWidth(const double width)
{
    std::cout << "Line width set to: " << width << '\n';
}

/// logs drawing surface dimensions
void TestRenderer::initializeDrawingSurface(const int width, const int height)
{
    std::cout << "Drawing Surface width: " << width
              << "\nDrawing Surface height: " << height << '\n';
}

void TestRenderer::sendToDrawingBuffer()
{
    std::cout << "Sending to drawing buffer...\n";
}

/// logs new color values
void TestRenderer::setDrawingColor(
    const double red,
    const double green,
    const double blue,
    const double alpha
)
{
    std::cout << "Red: " << red << '\n'
              << "Green: "<< green << '\n'
              << "Blue: " << blue << '\n'
              << "Alpha: " << alpha << '\n';
}

bool TestRenderer::hasHardwareAcceleration() const
{
    std::cout << hardcoded::hardwareAcceleration;
    return hardcoded::hardwareAcceleration;
}

/// Logs the cleanup of cairo objects
void TestRenderer::cleanup()
{
    std::cout << "Cleaning up...\n Cairo Context Destroyed!\
                    \n Cairo Surface Destroyed!\n";
}

/// Logs texture update
int TestRenderer::updateTexture()
{
    std::cout << "Updating texture...\n";
    return 0;
}

/// Logs the termination of the renderer
void TestRenderer::terminateRenderer()
{
    std::cout << "Terminating renderer...\n";
}

void TestRenderer::bindSurfaceAndContext()
{
    /// NOTE: Doesn't have to be filled
}

/** Logs the curves that will be drawn
 * \param flexArray including the curves
 */
void TestRenderer::drawCurve(Curve& m_Curve)
{
    for (size_t i = 0; i < m_Curve.size(); ++i)
    {
        std::cout << "Curve coordinates: \n"
                  << "start: " << m_Curve[i].cx1 << ", " << m_Curve[i].cy1
                  << "\nend: " << m_Curve[i].cx2 << ", " << m_Curve[i].cy2
                  << "\ncontrol: " << m_Curve[i].x2 << ", " << m_Curve[i].y2 << '\n';
    }
}

/// Logs rendering
void TestRenderer::render()
{
    std::cout << "Rendering...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

/// Logs surface data being acquired
unsigned char* TestRenderer::getSurfaceData() const
{
    std::cout << "Getting surface data...\n";
    return nullptr;
}

/// Check if it's a test renderer
bool TestRenderer::isTestRenderer() const
{
    return true;
}