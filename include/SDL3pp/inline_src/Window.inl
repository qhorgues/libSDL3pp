#include <utility>
#include <string>
#include <string_view>
#include <source_location>
#include <SDL3/SDL_video.h>
#include <SDL3pp/Exception.hpp>
#include <SDL3pp/Point.hpp>
#include <SDL3pp/Window.hpp>

namespace SDL3pp
{

inline Window::Window(SDL_Window* window)
 : m_window(window), m_parent_window(nullptr)
{}

inline std::pair<int, int> Window::get_size() const
{
    int width, height;
    if (!SDL_GetWindowSize(const_cast<SDL_Window*>(m_window.get()), &width, &height))
    {
        const std::source_location& loc {std::source_location::current()};
        throw Exception(loc.function_name());
    }
    return std::make_pair(width, height);
}

inline int Window::get_width() const
{
    int width;
    if(!SDL_GetWindowSize(const_cast<SDL_Window*>(m_window.get()), &width, nullptr))
    {
        throw Exception("SDL_GetWindowSize");
    }
    return width;
}

inline int Window::get_height() const
{
    int height;
    if(!SDL_GetWindowSize(const_cast<SDL_Window*>(m_window.get()), nullptr, &height))
    {
        throw Exception("SDL_GetWindowSize");
    }
    return height;
}

inline std::pair<int, int> Window::get_size_in_pixel() const
{
    int width, height;
    if (!SDL_GetWindowSizeInPixels(const_cast<SDL_Window*>(m_window.get()), &width, &height))
    {
        throw Exception("SDL_GetWindowSize");
    }
    return std::make_pair(width, height);
}

inline int Window::get_width_in_pixel() const
{
    int width;
    if(!SDL_GetWindowSizeInPixels(const_cast<SDL_Window*>(m_window.get()), &width, nullptr))
    {
        throw Exception("SDL_GetWindowSize");
    }
    return width;
}

inline int Window::get_height_in_pixel() const
{
    int height;
    if(!SDL_GetWindowSizeInPixels(const_cast<SDL_Window*>(m_window.get()), nullptr, &height))
    {
        throw Exception("SDL_GetWindowSize");
    }
    return height;
}

inline std::string_view Window::get_title() const
{
    return SDL_GetWindowTitle(const_cast<SDL_Window*>(m_window.get()));
}

inline void Window::set_title(std::string const& title)
{
    if (!SDL_SetWindowTitle(m_window.get(), title.c_str()))
    {
        throw Exception("SDL_SetWindowTitle");
    }
}

inline observer_ptr<Window> Window::get_parent() const
{
    if (SDL_GetWindowParent(const_cast<SDL_Window*>(m_window.get())) == nullptr)
    {
        return nullptr;
    }
    return m_parent_window;
}

inline void Window::set_parent(Window& parent)
{
    if (!SDL_SetWindowParent(m_window, parent.m_window))
    {
        throw Exception("SDL_SetWindowParent");
    }
    m_parent_window = make_observer(&parent);
}

inline Point Window::get_position() const
{
    int x, y;
    SDL_GetWindowPosition(const_cast<SDL_Window*>(m_window.get()), &x, &y);
    return Point(x, y);
}

}