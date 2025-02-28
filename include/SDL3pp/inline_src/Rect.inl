#include <SDL3pp/Point.hpp>
#include <SDL3pp/Rect.hpp>
#include <utility>

namespace SDL3pp {

constexpr Rect::Rect() noexcept
  : SDL_Rect{ 0, 0, 0, 0 }
{
}

constexpr Rect::Rect(SDL_Rect const& rect) noexcept
  : SDL_Rect{ rect.x, rect.y, rect.w, rect.h }
{
}

constexpr Rect::Rect(Point const& corner, std::pair<int, int> const& size) noexcept
  : SDL_Rect{ corner.get_x(), corner.get_y(), size.first, size.second }
{
}

constexpr Rect::Rect(Point const& corner, int w, int h) noexcept
  : SDL_Rect{ corner.get_x(), corner.get_y(), w, h }
{
}

constexpr Rect::Rect(int x, int y, int w, int h) noexcept
  : SDL_Rect{ x, y, w, h }
{
}

constexpr Rect
Rect::from_center(int cx, int cy, int w, int h) noexcept
{
  return Rect(cx - w / 2, cy - h / 2, w, h);
}

constexpr Rect
Rect::from_center(Point const& center, std::pair<int, int> const& size) noexcept
{
  return Rect(Point(center.get_x() - size.first/2,
                    center.get_y() - size.second/2), 
              size);
}

constexpr Rect
Rect::from_corners(int x1, int y1, int x2, int y2) noexcept
{
  return Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

constexpr Rect
Rect::from_corners(Point const& p1, Point const& p2) noexcept
{
  return Rect(p1, 
              p2.get_x() - p1.get_x() +1,
              p2.get_y() - p1.get_y() +1);
}

constexpr int
Rect::get_x() const noexcept
{
  return x;
}

constexpr Rect&
Rect::set_x(int nx) noexcept
{
  x = x;
  return *this;
}

constexpr int
Rect::get_y() const noexcept
{
  return y;
}

constexpr Rect&
Rect::set_y(int ny) noexcept
{
  y = ny;
  return *this;
}

constexpr int
Rect::get_width() const noexcept
{
  return w;
}

constexpr Rect&
Rect::set_width(int width) noexcept
{
  w = width;
  return *this;
}

constexpr int
Rect::get_height() const noexcept
{
  return h;
}

constexpr Rect&
Rect::set_height(int height) noexcept
{
  h = height;
  return *this;
}

constexpr int
Rect::get_x2() const noexcept
{
  return x + w - 1;
}

constexpr Rect&
Rect::set_x2(int x2) noexcept
{
  w = x2 - x + 1;
  return *this;
}

constexpr int
Rect::get_y2() const noexcept
{
  return y + h - 1;
}

constexpr Rect& 
Rect::set_y2(int y2) noexcept
{
  h = y2 - y + 1;
  return *this;
}

constexpr Point
Rect::get_top_left() const noexcept
{
  return Point(x, y);
}

constexpr Point
Rect::get_top_right() const noexcept
{
  return Point(get_x2(), y);
}

constexpr Point
Rect::get_bottom_left() const noexcept
{
  return Point(x, get_y2());
}

constexpr Point
Rect::get_bottom_right() const noexcept
{
  return Point(get_x2(), get_y2());
}

constexpr std::pair<int, int>
Rect::get_size() const noexcept
{
  return std::make_pair(get_width(), get_height());
}

constexpr Point
Rect::get_centroid() const noexcept
{
  return Point(x + w / 2, y + h / 2);
}

constexpr bool
Rect::countains(int px, int py) const noexcept
{
  return px >= x && py >= y && px <= get_x2() && py <= get_y2();
}

constexpr bool
Rect::countains(Point const& point) const noexcept
{
  return point.get_x() >= x && point.get_y() >= y && point.get_x() <= get_x2() &&
         point.get_y() <= get_y2();
}

constexpr bool
Rect::countains(Rect const& rect) const noexcept
{
  return rect.x >= x && rect.y >= y && rect.get_x2() <= get_x2() &&
         rect.get_y2() <= get_y2();
}

constexpr bool
Rect::intersects(Rect const& rect) const noexcept
{
  return !(rect.get_x2() < x || rect.get_y2() < y || rect.x > get_x2() ||
           rect.y > get_y2());
}

}