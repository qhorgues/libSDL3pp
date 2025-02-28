#ifndef SDL3PP_EXCEPTION_HPP
#define SDL3PP_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace SDL3pp
{

class Exception : public std::runtime_error
{
public:
    Exception() = delete;

    explicit constexpr Exception(std::string const& function);
    explicit constexpr Exception(const char* function);

    Exception(Exception const&) = default;
    Exception& operator=(Exception const&) = default;

    Exception(Exception &&) = default;
    Exception& operator=(Exception &&) = default;

    virtual ~Exception() = default;

    constexpr std::string get_sdl_function() const;
    constexpr std::string get_sdl_error() const;
private:
    static std::string make_what(std::string const& sdl_function, std::string const& sdl_error);

    std::string m_sdl_function;
    std::string m_sdl_error;
};

}

#include "inline_src/Exception.inl"
#endif
