#include <string>
#include <source_location>
#include <SDL3/SDL_video.h>
#include <SDL3pp/Exception.hpp>
#include <SDL3pp/Window.hpp>

namespace SDL3pp
{

Window::Window(std::string const& title, int w, int h, WindowFlags flags)
 : m_window(),  
   m_parent_window(nullptr)
{
    m_window = SDL_CreateWindow(title.data(), w, h, flags);
    if (m_window == nullptr)
    {
        const std::source_location& loc {std::source_location::current()};
        throw Exception(loc.function_name());
    }
} 

Window::Window(Window& parent, int offset_x, int offset_y, int w, int h, WindowFlags flags)
: m_window(),  
  m_parent_window(&parent)
{
    m_window = SDL_CreatePopupWindow(parent.m_window.get(), offset_x, offset_y, w, h, flags);
    if (m_window == nullptr)
    {
        const std::source_location& loc {std::source_location::current()};
        throw Exception(loc.function_name());
    }
}

Window& Window::operator=(Window&& other)
{
    if (&other == this)
        return *this;
    if (m_window != nullptr)
        SDL_DestroyWindow(m_window);
    m_window = std::move(other.m_window);
    m_parent_window = std::move(other.m_parent_window);
    other.m_parent_window = nullptr;
    return *this;
}

Window::~Window()
{
    if (m_window != nullptr)
        SDL_DestroyWindow(m_window);
}

}