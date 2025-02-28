#include <SDL3pp/Point.hpp>
#include <SDL3pp/Rect.hpp>
#include <algorithm>
#include <optional>

namespace SDL3pp {

Rect
Rect::get_union(Rect const& rect) const
{
  return Rect::from_corners(std::min(x, rect.x),
                            std::min(y, rect.y),
                            std::max(get_x2(), rect.get_x2()),
                            std::max(get_y2(), rect.get_y2()));
}

Rect&
Rect::union_in_place(const Rect& rect)
{
  int nx = std::min(x, rect.x);
  int ny = std::min(y, rect.y);
  int nx2 = std::max(get_x2(), rect.get_x2());
  int ny2 = std::max(get_y2(), rect.get_y2());
  x = nx;
  y = ny;
  set_x2(nx2);
  set_y2(ny2);
  return *this;
}

Rect
Rect::get_extension(unsigned int amount) const
{
  Rect r = *this;
  r.extend_in_place(amount);
  return r;
}

Rect
Rect::get_extension(unsigned int hamount, unsigned int vamount) const
{
  Rect r = *this;
  r.extend_in_place(hamount, vamount);
  return r;
}

Rect&
Rect::extend_in_place(unsigned int amount)
{
  return extend_in_place(amount, amount);
}

Rect&
Rect::extend_in_place(unsigned int hamount, unsigned int vamount)
{
  x -= hamount;
  y -= vamount;
  w += hamount * 2;
  h += vamount * 2;
  return *this;
}

std::optional<Rect>
Rect::get_intersection(const Rect& rect) const
{
  if (!intersects(rect))
    return std::nullopt;

  return Rect::from_corners(std::max(x, rect.x),
                            std::max(y, rect.y),
                            std::min(get_x2(), rect.get_x2()),
                            std::min(get_y2(), rect.get_y2()));
}

bool
Rect::intersect_line(int& x1, int& y1, int& x2, int& y2) const
{
  return SDL_GetRectAndLineIntersection(this, &x1, &y1, &x2, &y2) == true;
}

bool
Rect::intersect_line(Point& p1, Point& p2) const
{
  int x1, y1, x2, y2;
  bool res = SDL_GetRectAndLineIntersection(
              this, &x1, &y1, &x2, &y2);
  p1.set_x(x1);
  p1.set_y(y1);
  p2.set_x(x2);
  p2.set_y(y2);
  return res;
}

}

std::ostream&
operator<<(std::ostream& stream, const SDL3pp::Rect& rect)
{
  stream << "[x:" << rect.get_x() << ",y:" << rect.get_y() 
         << ",w:" << rect.get_width() 
         << ",h:" << rect.get_height() << "]";
  return stream;
}
