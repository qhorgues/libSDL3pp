/**
  libSDL3pp - C++ bindings/wrapper for SDL3
  Copyright (C) 2013-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL3PP_RECT_HPP
#define SDL3PP_RECT_HPP

#include <SDL3/SDL_rect.h>
#include <functional>
#include <optional>
#include <utility>

#include <SDL3pp/Export.hpp>
#include <SDL3pp/Point.hpp>

namespace SDL3pp {

/**
 *  @brief 2D rectangle
 *
 *  @ingroup geometry
 *
 *  @headerfile SDL3pp/Rect.hh
 *
 *  This class is public-derived from SDL_Rect structure,
 *  may generally used as it if passed via pointer or
 *  reference. It also supports direct access to x, y, w
 *  and h members.
 *
 *  @see http://wiki.libsdl.org/SDL_Rect
 *
 */
class SDL3PP_EXPORT Rect : private SDL_Rect
{
public:
  /**
   *  @brief Default constructor
   *
   *  Creates a Rect(0, 0, 0, 0)
   *
   */
  constexpr Rect() noexcept;

  /**
   *  @brief Construct a rect from existing SDL_Rect
   *
   *  @param[in] rect Existing SDL_Rect
   *
   */
  constexpr Rect(const SDL_Rect& rect) noexcept;

  /**
   *  @brief Construct the rect from given corner coordinates, and size
   *
   *  @param[in] corner Coordinates of the top left rectangle corner
   *  @param[in] size Dimensions of the rectangle
   *
   */
  constexpr Rect(Point const& corner, std::pair<int, int> const& size) noexcept;

  /**
   * @brief Construct the rect from giver corner coordinates, width and height
   * 
   * @param[in] corner Coordinates of the top left rectangle corner
   * @param[in] w Width of the rectangle
   * @param[in] h Height of the rectangle
   * 
   */
  constexpr Rect(Point const& corner, int w, int h) noexcept;

  /**
   *  @brief Construct the rect from given corner coordinates, width and height
   *
   *  @param[in] x X coordinate of the top left rectangle corner
   *  @param[in] y Y coordinate of the top left rectangle corner
   *  @param[in] w Width of the rectangle
   *  @param[in] h Height of the rectangle
   *
   */
  constexpr Rect(int x, int y, int w, int h) noexcept;

  /**
   *  @brief Construct the rect from given center coordinates, width and height
   *
   *  @param[in] cx X coordinate of the rectangle center
   *  @param[in] cy Y coordinate of the rectangle center
   *  @param[in] w Width of the rectangle
   *  @param[in] h Height of the rectangle
   *
   */
  static constexpr Rect from_center(int cx, int cy, int w, int h) noexcept;

  /**
   *  @brief Construct the rect from given center coordinates and size
   *
   *  @param[in] center Coordinates of the rectangle center
   *  @param[in] size Dimensions of the rectangle
   *
   */
  static constexpr Rect from_center(Point const& center,
                                    std::pair<int, int> const& size) noexcept;

  /**
   *  @brief Construct the rect from given corners coordinates
   *
   *  @param[in] x1 X coordinate of the top left rectangle corner
   *  @param[in] y1 Y coordinate of the top left rectangle corner
   *  @param[in] x2 X coordinate of the bottom right rectangle corner
   *  @param[in] y2 Y coordinate of the bottom right rectangle corner
   *
   */
  static constexpr Rect from_corners(int x1, int y1, int x2, int y2) noexcept;

  /**
   *  @brief Construct the rect from given centers coordinates
   *
   *  @param[in] p1 Coordinates of the top left rectangle corner
   *  @param[in] p2 Coordinates of the bottom right rectangle corner
   *
   */
  static constexpr Rect from_corners(const Point& p1, const Point& p2) noexcept;

  /**
   *  @brief Copy constructor
   *
   */
  Rect(const Rect&) noexcept = default;

  /**
   *  @brief Move constructor
   *
   */
  Rect(Rect&&) noexcept = default;

  /**
   *  @brief Assignment operator
   *
   *  @returns Reference to self
   *
   */
  Rect& operator=(const Rect&) noexcept = default;

  /**
   *  @brief Move assignment operator
   *
   *  @returns Reference to self
   *
   */
  Rect& operator=(Rect&&) noexcept = default;

  /**
   *  @brief Get X coordinate of the rect corner
   *
   *  @returns X coordinate of the rect corner
   *
   */
  constexpr int get_x() const noexcept;

  /**
   *  @brief Set X coordinate of the rect corner
   *
   *  @param[in] nx New X coordinate value
   *
   *  @returns Reference to self
   *
   */
  constexpr Rect& set_x(int nx) noexcept;

  /**
   *  @brief Get Y coordinate of the rect corner
   *
   *  @returns Y coordinate of the rect corner
   *
   */
  constexpr int get_y() const noexcept;

  /**
   *  @brief Set Y coordinate of the rect corner
   *
   *  @param[in] ny New Y coordinate value
   *
   *  @returns Reference to self
   *
   */
  constexpr Rect& set_y(int ny) noexcept;

  /**
   *  @brief Get width of the rect
   *
   *  @returns Width of the rect
   *
   */
  constexpr int get_width() const noexcept;

  /**
   *  @brief Set width of the rect
   *
   *  @param[in] nw New width of the rect
   *
   *  @returns Reference to self
   *
   */
  constexpr Rect& set_width(int width) noexcept;

  /**
   *  @brief Get height of the rect
   *
   *  @returns Height of the rect
   *
   */
  constexpr int get_height() const noexcept;

  /**
   *  @brief Set height of the rect
   *
   *  @param[in] nh New height of the rect
   *
   *  @returns Reference to self
   *
   */
  constexpr Rect& set_height(int height) noexcept;

  /**
   *  @brief Get X coordinate of the rect second corner
   *
   *  @returns X coordinate of the rect second corner
   *
   */
  constexpr int get_x2() const noexcept;

  /**
   *  @brief Set X coordinate of the rect second corner
   *
   *  @param[in] x2 New X coordinate value
   *
   *  This modifies rectangle width internally
   *
   *  @returns Reference to self
   *
   */
  constexpr Rect& set_x2(int x2) noexcept;

  /**
   *  @brief Get Y coordinate of the rect second corner
   *
   *  @returns Y coordinate of the rect second corner
   *
   */
  constexpr int get_y2() const noexcept;

  /**
   *  @brief Set Y coordinate of the rect second corner
   *
   *  @param[in] y2 New Y coordinate value
   *
   *  This modifies rectangle height internally
   *
   *  @returns Reference to self
   *
   */
  constexpr Rect& set_y2(int y2) noexcept;

  /**
   *  @brief Get top left corner of the rect
   *
   *  @returns Top left corner of the rect
   *
   */
  constexpr Point get_top_left() const noexcept;

  /**
   *  @brief Get top right corner of the rect
   *
   *  @returns Top right corner of the rect
   *
   */
  constexpr Point get_top_right() const noexcept;

  /**
   *  @brief Get bottom left corner of the rect
   *
   *  @returns bottom left corner of the rect
   *
   */
  constexpr Point get_bottom_left() const noexcept;

  /**
   *  @brief Get bottom right corner of the rect
   *
   *  @returns Bottom right corner of the rect
   *
   */
  constexpr Point get_bottom_right() const noexcept;

  /**
   *  @brief Get size of the rect
   *
   *  @returns Size of the rect
   *
   */
  constexpr std::pair<int, int> get_size() const noexcept;

  /**
   *  @brief Get centroid of the rect
   *
   *  @returns Centroid of the rect
   *
   */
  constexpr Point get_centroid() const noexcept;

  /**
   *  @brief Check whether the rect contains given point
   *
   *  @param[in] px X coordinate of a point
   *  @param[in] py Y coordinate of a point
   *
   *  @returns True if the point is contained in the rect
   *
   */
  constexpr bool countains(int px, int py) const noexcept;

  /**
   *  @brief Check whether the rect contains given point
   *
   *  @param[in] point Point to check
   *
   *  @returns True if the point is contained in the rect
   *
   */
  constexpr bool countains(Point const& point) const noexcept;

  /**
   *  @brief Check whether the rect contains another rect
   *
   *  @param[in] rect Rect to check
   *
   *  @returns True if the checked rect is contained in this rect
   *
   */
  constexpr bool countains(Rect const& rect) const noexcept;

  /**
   *  @brief Check whether the rect intersects another rect
   *
   *  @param[in] rect Rect to check
   *
   *  @returns True if rectangles intersect
   *
   */
  constexpr bool intersects(const Rect& rect) const noexcept;

  /**
   *  @brief Calculate union with another rect
   *
   *  @param[in] rect Rect to union with
   *
   *  @returns Rect representing union of two rectangles
   *
   */
  Rect get_union(Rect const& rect) const;

  /**
   *  @brief Union rect with another rect
   *
   *  @param[in] rect Rect to union with
   *
   *  @returns Reference to self
   *
   */
  Rect& union_in_place(const Rect& rect);

  /**
   *  @brief Get a rect extended by specified amount of pixels
   *
   *  @param[in] amount Number of pixels to extend by
   *
   *  @returns Extended rect
   *
   */
  Rect get_extension(unsigned int amount) const;

  /**
   *  @brief Get a rect extended by specified amount of pixels
   *
   *  @param[in] hamount Number of pixels to extend by
   *                     in horizontal direction
   *  @param[in] vamount Number of pixels to extend by
   *                     in vertical direction
   *
   *  @returns Extended rect
   *
   */
  Rect get_extension(unsigned int hamount, unsigned int vamount) const;

  /**
   *  @brief Extend a rect by specified amount of pixels
   *
   *  @param[in] amount Number of pixels to extend by
   *
   *  @returns Reference to self
   *
   */
  Rect& extend_in_place(unsigned int amount);

  /**
   *  @brief Extend a rect by specified amount of pixels
   *
   *  @param[in] hamount Number of pixels to extend by
   *                     in horizontal direction
   *  @param[in] vamount Number of pixels to extend by
   *                     in vertical direction
   *
   *  @returns Reference to self
   *Extend
   */
  Rect& extend_in_place(unsigned int hamount, unsigned int vamount);

  /**
   *  @brief Calculate intersection with another rect
   *
   *  @param[in] rect Rect to intersect with
   *
   *  @returns Rect representing intersection area or NullOpt if there was no
   * intersection
   *
   */
  std::optional<Rect> get_intersection(const Rect& rect) const;

  /**
   *  @brief Calculate the intersection of a rectangle and line segment
   *
   *  @param[in,out] x1 Starting X-coordinate of the line
   *  @param[in,out] y1 Starting Y-coordinate of the line
   *  @param[in,out] x2 Ending X-coordinate of the line
   *  @param[in,out] y2 Ending Y-coordinate of the line
   *
   *  @returns True if there is an intersection, false otherwise
   *
   *  This function is used to clip a line segment to a
   *  rectangle. A line segment contained entirely within the
   *  rectangle or that does not intersect will remain unchanged.
   *  A line segment that crosses the rectangle at either or both
   *  ends will be clipped to the boundary of the rectangle and
   *  the new coordinates saved in x1, y1, x2, and/or y2 as
   *  necessary.
   *
   */
  bool intersect_line(int& x1, int& y1, int& x2, int& y2) const;

  /**
   *  @brief Calculate the intersection of a rectangle and line segment
   *
   *  @param[in,out] p1 Starting coordinates of the line
   *  @param[in,out] p2 Ending coordinates of the line
   *
   *  @returns True if there is an intersection, false otherwise
   *
   *  This function is used to clip a line segment to a
   *  rectangle. A line segment contained entirely within the
   *  rectangle or that does not intersect will remain unchanged.
   *  A line segment that crosses the rectangle at either or both
   *  ends will be clipped to the boundary of the rectangle and
   *  the new coordinates saved in p1 and/or p2 as necessary.
   *
   */
  bool intersect_line(Point& p1, Point& p2) const;

  /**
   *  @brief Get rectangle moved by a given offset
   *
   *  @param[in] offset Point specifying an offset
   *
   *  @returns Moved rectangle
   *
   */
  constexpr Rect operator+(const Point& offset) const
  {
    return Rect(x + offset.get_x(), y + offset.get_y(), w, h);
  }

  /**
   *  @brief Get rectangle moved by an opposite of given offset
   *
   *  @param[in] offset Point specifying an offset
   *
   *  @returns Moved rectangle
   *
   */
  constexpr Rect operator-(const Point& offset) const
  {
    return Rect(x - offset.get_x(), y - offset.get_y(), w, h);
  }

  /**
   *  @brief Move by then given offset
   *
   *  @param[in] offset Point specifying an offset
   *
   *  @returns Reference to self
   *
   */
  Rect& operator+=(const Point& offset)
  {
    x += offset.get_x();
    y += offset.get_y();
    return *this;
  }

  /**
   *  @brief Move by an opposite of the given offset
   *
   *  @param[in] offset Point specifying an offset
   *
   *  @returns Reference to self
   *
   */
  Rect& operator-=(const Point& offset)
  {
    x -= offset.get_x();
    y -= offset.get_y();
    return *this;
  }
};

}

/**
 *  @brief Equality operator for SDL3pp::Rect
 *
 *  @param[in] a First argument for comparison
 *  @param[in] b Second argument for comparison
 *
 *  @returns True if two rectangles are identical
 *
 */
constexpr bool
operator==(const SDL3pp::Rect& a, const SDL3pp::Rect& b)
{
  return a.get_x() == b.get_x() && a.get_y() == b.get_y() &&
         a.get_width() == b.get_width() && a.get_height() == b.get_height();
}

/**
 *  @brief Inequality operator for SDL3pp::Rect
 *
 *  @param[in] a First argument for comparison
 *  @param[in] b Second argument for comparison
 *
 *  @returns True if two rectangles are not identical
 *
 */
constexpr bool
operator!=(const SDL3pp::Rect& a, const SDL3pp::Rect& b)
{
  return !(a == b);
}

/**
 *  @brief Stream output operator overload for SDL3pp::Rect
 *
 *  @param[in] stream Stream to output to
 *  @param[in] rect Rect to output
 *
 *  @returns stream
 *
 */
SDL3PP_EXPORT std::ostream&
operator<<(std::ostream& stream, const SDL3pp::Rect& rect);

namespace std {

/**
 *  @brief std::hash specialization for SDL3pp::Rect
 *
 */
template<>
struct hash<SDL3pp::Rect>
{
  /**
   *  @brief Hash function for SDL3pp::Rect
   *
   *  @param[in] r Input Rect
   *
   *  @returns Hash value
   *
   */
  size_t operator()(const SDL3pp::Rect& r) const
  {
    size_t seed = std::hash<int>()(r.get_x());
    seed ^=
      std::hash<int>()(r.get_y()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^=
      std::hash<int>()(r.get_width()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^=
      std::hash<int>()(r.get_height()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

}

#include "inline_src/Rect.inl"
#endif
