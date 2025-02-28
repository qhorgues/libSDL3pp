#include <SDL3pp/Point.hpp>

namespace SDL3pp {

constexpr Point::Point() noexcept
  : SDL_Point(0, 0)
{
}

constexpr Point::Point(SDL_Point const& point) noexcept
  : SDL_Point(point.x, point.y)
{
}

constexpr Point::Point(std::pair<int, int> point) noexcept
  : SDL_Point(point.first, point.second)
{
}

constexpr Point::Point(int x, int y) noexcept
  : SDL_Point(x, y)
{
}

constexpr int
Point::get_x() const noexcept
{
  return x;
}

constexpr Point&
Point::set_x(int nx) noexcept
{
    x = nx;
    return *this;
}

constexpr int
Point::get_y() const noexcept
{
  return y;
}

constexpr Point&
Point::set_y(int ny) noexcept
{
  y = ny;
  return *this;
}

constexpr Point::operator std::pair<int, int>() const noexcept
{
  return std::make_pair(x, y);
}

constexpr Point
Point::operator-() const noexcept
{
  return Point(-x, -y);
}

constexpr Point&
Point::operator+=(Point const& other) noexcept
{
  x += other.x;
  y += other.y;
  return *this;
}

constexpr Point&
Point::operator-=(Point const& other) noexcept
{
  x -= other.x;
  y -= other.y;
  return *this;
}

constexpr Point&
Point::operator/=(int divisor)
{
  x /= divisor;
  y /= divisor;
  return *this;
}

constexpr Point&
Point::operator/=(Point const& divisor)
{
  x /= divisor.x;
  y /= divisor.y;
  return *this;
}

constexpr Point&
Point::operator%=(int modulo)
{
  x %= modulo;
  y %= modulo;
  return *this;
}

constexpr Point&
Point::operator%=(Point const& modulo)
{
  x %= modulo.x;
  y %= modulo.y;
  return *this;
}

constexpr Point&
Point::operator*=(int product) noexcept
{
  x *= product;
  y *= product;
  return *this;
}

constexpr Point&
Point::operator*=(Point const& product) noexcept
{
  x *= product.x;
  y *= product.y;
  return *this;
}

}

constexpr SDL3pp::Point
operator+(SDL3pp::Point point, SDL3pp::Point const& other) noexcept
{
  return point += other;
}

constexpr SDL3pp::Point
operator-(SDL3pp::Point point, SDL3pp::Point const& other) noexcept
{
  return point -= other;
}

constexpr SDL3pp::Point
operator/(SDL3pp::Point point, int divisor)
{
  return point /= divisor;
}

constexpr SDL3pp::Point
operator/(SDL3pp::Point point, SDL3pp::Point const& other)
{
  return point /= other;
}

constexpr SDL3pp::Point
operator%(SDL3pp::Point point, int modulo)
{
  return point %= modulo;
}

constexpr SDL3pp::Point
operator%(SDL3pp::Point point, SDL3pp::Point const& modulo)
{
  return point %= modulo;
}

constexpr SDL3pp::Point
operator*(SDL3pp::Point point, int product) noexcept
{
  return point *= product;
}

constexpr SDL3pp::Point
operator*(int product, SDL3pp::Point point) noexcept
{
  return point *= product;
}

constexpr SDL3pp::Point
operator*(SDL3pp::Point point, SDL3pp::Point const& other) noexcept
{
  return point *= other;
}

constexpr bool
operator==(SDL3pp::Point const& a, SDL3pp::Point const& b) noexcept
{
  return a.get_x() == b.get_x() && a.get_y() == b.get_y();
}

constexpr bool
operator!=(SDL3pp::Point const& a, SDL3pp::Point const& b) noexcept
{
  return !(a == b);
}