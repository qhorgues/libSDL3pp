#include <string>
#include <SDL3/SDL_video.h>
#include <SDL3pp/Exception/Exception.hpp>
#include "Window.hpp"

namespace SDL3pp
{

Window::Window(std::string const& title, int w, int h, WindowFlags flags)
 : m_window(), m_children_window(0)
{
    m_window = SDL_CreateWindow(title.c_str(), w, h, flags);
    if (m_window == nullptr)
    {
        throw Exception("SDL_CreateWindow");
    }
} 

Window::Window(Window& parent, int offset_x, int offset_y, int w, int h, WindowFlags flags)
 : m_window(), m_children_window(0)
{
    m_window = SDL_CreatePopupWindow(parent.m_window, offset_x, offset_y, w, h, flags);
    if (m_window == nullptr)
    {
        throw Exception("SDL_CreateWindow");
    }
    parent.m_children_window.insert(*this);
}

void Window::clear_children()
{
    for (Window& window : m_children_window)
    {
        window.clear_children();
        window.m_window = nullptr;
        window.m_children_window.clear();
    }
}

Window::~Window()
{
    clear_children();
    if (m_window != nullptr)
    {
        SDL_DestroyWindow(m_window);
    }
}

}