#include <string>
#include <SDL3/SDL_error.h>
#include "Exception.hpp"

namespace SDL3pp {

std::string Exception::make_what(std::string const& function, std::string const& sdl_error) {
    using namespace std::literals;
    return function + " failed: "s + sdl_error;
}

inline Exception::Exception(std::string const& function)
: std::runtime_error(make_what(function, SDL_GetError())),
  m_sdl_function(function),
  m_sdl_error(SDL_GetError())
{
}

inline Exception::Exception(const char* function)
: std::runtime_error(make_what(function, SDL_GetError())),
  m_sdl_function(function),
  m_sdl_error(SDL_GetError())
{
}

inline std::string Exception::get_sdl_function() const {
    return m_sdl_function;
}

inline std::string Exception::get_sdl_error() const {
    return m_sdl_error;
}

} // namespace SDL3pp