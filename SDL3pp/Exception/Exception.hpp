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

    explicit inline Exception(std::string const& function);
    explicit inline Exception(const char* function);

    Exception(Exception const&) = default;
    Exception& operator=(Exception const&) = default;

    Exception(Exception &&) = default;
    Exception& operator=(Exception &&) = default;

    virtual ~Exception() = default;

    inline std::string get_sdl_function() const;
    inline std::string get_sdl_error() const;
private:
    static std::string make_what(std::string const& sdl_function, std::string const& sdl_error);

    std::string m_sdl_function;
    std::string m_sdl_error;
};

}

#endif