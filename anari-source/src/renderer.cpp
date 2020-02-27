#include "anari/renderer.hpp"

Renderer::Renderer()
: m_WindowHandle(nullptr), m_WindowWidth(600), m_WindowHeight(800),
  PITCH(m_WindowWidth * BYTES_PER_PIXEL),
  m_Renderer(nullptr), m_Texture(nullptr),
  m_Context(nullptr), m_Surface(nullptr) {}

Renderer::Renderer(const Window* windowHandle)
: m_WindowHandle(windowHandle), m_WindowWidth(windowHandle->getWindowSize().width),
  m_WindowHeight(windowHandle->getWindowSize().height),
  PITCH(m_WindowWidth * BYTES_PER_PIXEL),
  m_Renderer(nullptr), m_Texture(nullptr),
  m_Context(nullptr), m_Surface(nullptr)
{}

Renderer::~Renderer() {}

unsigned char* Renderer::getSurfaceData() const { return nullptr; }