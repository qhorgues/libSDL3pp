
#ifndef SDL3PP_POINT_HH
#define SDL3PP_POINT_HH

#include <functional>
#include <iostream>

#include <SDL3/SDL_rect.h>

#include <SDL3pp/Export.hpp>

namespace SDL3pp {

class Rect;

/**
 * @brief 2D point
 *
 *  @ingroup geometry
 *
 *  @headerfile SDL3pp/Point.hh
 *
 *  This class is public-derived from SDL_Point structure,
 *  may generally used as it if passed via pointer or
 *  reference. It also supports direct access to x and y
 *  members.
 *
 *  @see http://wiki.libsdl.org/SDL_Point
 *
 */
class SDL3PP_EXPORT Point : private SDL_Point
{
public:
  /**
   * @brief Default constructor
   *
   *  Creates a Point(0, 0)
   *
   */
  constexpr Point() noexcept;

  /**
   * @brief Construct a point from existing SDL_Point
   *
   *  @param[in] point Existing SDL_Point
   *
   */
  constexpr Point(SDL_Point const& point) noexcept;

  /**
   * @brief Construct a point from given coordinates.
   * 
   * @param[in] point Pair of the Point's coordinates.
   */
  constexpr Point(std::pair<int, int> point) noexcept;

  /**
   * @brief Construct the point from given coordinates
   *
   *  @param[in] x X coordinate
   *  @param[in] y Y coordinate
   *
   */
  constexpr Point(int x, int y) noexcept;

  /**
   * @brief Copy constructor
   *
   */
  Point(const Point&) noexcept = default;

  /**
   * @brief Move constructor
   *
   */
  Point(Point&&) noexcept = default;

  /**
   * @brief Assignment operator
   *
   *  @returns Reference to self
   *
   */
  Point& operator=(const Point&) noexcept = default;

  /**
   * @brief Move assignment operator
   *
   *  @returns Reference to self
   *
   */
  Point& operator=(Point&&) noexcept = default;

  /**
   * @brief Get X coordinate of the point
   *
   *  @returns X coordinate of the point
   *
   */
  constexpr int get_x() const noexcept;

  /**
   * @brief Set X coordinate of the point
   *
   *  @param[in] nx New X coordinate value
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& set_x(int nx) noexcept;

  /**
   * @brief Get Y coordinate of the point
   *
   *  @returns Y coordinate of the point
   *
   */
  constexpr int get_y() const noexcept;

  /**
   * @brief Set Y coordinate of the point
   *
   *  @param[in] ny New Y coordinate value
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& set_y(int ny) noexcept;

  /**
   * @brief Convert point to pair of int
   * 
   * @return std::pair<int, int> 
   */
  constexpr operator std::pair<int, int>() const noexcept;

  /**
   * @brief Get point's memberwise negation
   *
   *  @returns New Point representing memberwise negation
   *
   */
  constexpr Point operator-() const noexcept;

  /**
   * @brief Memberwise add another point
   *
   *  @param[in] other Point to add to the current one
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& operator+=(Point const& other) noexcept;

  /**
   * @brief Memberwise subtract another point
   *
   *  @param[in] other Point to subtract from the current one
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& operator-=(Point const& other) noexcept;

  /**
   * @brief Memberwise divide by an integer
   *
   *  @param[in] value Divisor
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& operator/=(int divisor);

  /**
   *  nbrief Memberwise divide by another point
   *
   *  @param[in] other Divisor
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& operator/=(Point const& divisor);

  /**
   * @brief Memberwise remainder from division by an integer
   *
   *  @param[in] value Divisor
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& operator%=(int modulo);

  /**
   * @brief Memberwise remainder from division by another
   *         point
   *
   *  @param[in] other Divisor
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& operator%=(Point const& modulo);

  /**
   * @brief Memberwise multiply by an integer
   *
   *  @param[in] value Multiplier
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& operator*=(int product) noexcept;

  /**
   * @brief Memberwise multiply by another point
   *
   *  @param[in] other Multiplier
   *
   *  @returns Reference to self
   *
   */
  constexpr Point& operator*=(Point const& other) noexcept;

  /**
   * @brief Get a point with coordinates modified so it fits
   *         into a given rect
   *
   *  @param[in] rect Rectangle to clamp with
   *
   *  @returns Clamped point
   *
   */
  Point get_clamped(const Rect& rect) const;

  /**
   * @brief Clamp point coordinates to make it fit into a
   *         given rect
   *
   *  @param[in] rect Rectangle to clamp with
   *
   *  @returns Reference to self
   *
   */
  Point& clamp(const Rect& rect);

  /**
   * @brief Get a point wrapped within a specified rect
   *
   *  @param[in] rect Rectangle to wrap with
   *
   *  @returns Wrapped point
   *
   */
  Point get_wrapped(const Rect& rect) const;

  /**
   * @brief Wrap point coordinates within a spedified rect
   *
   *  @param[in] rect Rectangle to wrap with
   *
   *  @returns Reference to self
   *
   */
  Point& wrap(const Rect& rect);
};

}

/**
 * @brief Get point's memberwise addition with another point
 *
 *  @param[in] other Point to add
 *
 *  @returns New Point representing memberwise addition with another point
 *
 */
constexpr SDL3pp::Point
operator+(SDL3pp::Point point, SDL3pp::Point const& other) noexcept;

/**
 * @brief Get point's memberwise subtraction with another point
 *
 *  @param[in] other Point to subtract
 *
 *  @returns New Point representing memberwise subtraction of another point
 *
 */
constexpr SDL3pp::Point
operator-(SDL3pp::Point point, const SDL3pp::Point& other) noexcept;

/**
 * @brief Get point's memberwise division by an integer
 *
 *  @param[in] value Divisor
 *
 *  @returns New Point representing memberwise division of
 *           point by an integer
 *
 */
constexpr SDL3pp::Point
operator/(SDL3pp::Point point, int divisor);

/**
 * @brief Get point's memberwise division by another point
 *
 *  @param[in] other Divisor
 *
 *  @returns New Point representing memberwise division of
 *           point by another point
 *
 */
constexpr SDL3pp::Point
operator/(SDL3pp::Point point, const SDL3pp::Point& other);

/**
 * @brief Get point's memberwise remainder from division
 *         by an integer
 *
 *  @param[in] value Divisor
 *
 *  @returns New Point representing memberwise remainder
 *           from division by an integer
 *
 */
constexpr SDL3pp::Point
operator%(SDL3pp::Point point, int value);

/**
 * @brief Get point's memberwise remainder from division
 *         by another point
 *
 *  @param[in] other Divisor
 *
 *  @returns New Point representing memberwise remainder
 *           from division by another point
 *
 */
constexpr SDL3pp::Point
operator%(SDL3pp::Point point, const SDL3pp::Point& other);

/**
 * @brief Get point's memberwise multiplication by an
 *         integer
 *
 *  @param[in] value Multiplier
 *
 *  @returns New Point representing memberwise multiplication
 *           of point by an integer
 *
 */
constexpr SDL3pp::Point
operator*(SDL3pp::Point point, int value) noexcept;

/**
 * @brief Get point's memberwise multiplication by anoter
 *         point
 *
 *  @param[in] other Multiplier
 *
 *  @returns New Point representing memberwise multiplication
 *           of point by another point
 *
 */
constexpr SDL3pp::Point
operator*(SDL3pp::Point point, const SDL3pp::Point& other) noexcept;

/**
 * @brief Equality operator for SDL3pp::Point
 *
 *  @param[in] a First argument for comparison
 *  @param[in] b Second argument for comparison
 *
 *  @returns True if two points are identical
 *
 */
constexpr bool
operator==(SDL3pp::Point const& a, SDL3pp::Point const& b) noexcept;

/**
 * @brief Inequality operator for SDL3pp::Point
 *
 *  @param[in] a First argument for comparison
 *  @param[in] b Second argument for comparison
 *
 *  @returns True if two points are not identical
 *
 */
constexpr bool
operator!=(SDL3pp::Point const& a, SDL3pp::Point const& b) noexcept;

/**
 * @brief Stream output operator overload for SDL3pp::Point
 *
 *  @param[in] stream Stream to output to
 *  @param[in] point Point to output
 *
 *  @returns stream
 *
 */
SDL3PP_EXPORT std::ostream&
operator<<(std::ostream& stream, SDL3pp::Point const& point);

/**
 * @brief std::hash specialization for SDL3pp::Rect
 *
 */
template<>
struct std::hash<SDL3pp::Point>
{
  /**
   * @brief Hash function for SDL3pp::Point
   *
   *  @param[in] p Input Point
   *
   *  @returns Hash value
   *
   */
  std::size_t operator()(SDL3pp::Point const& p) const
  {
    std::size_t seed = std::hash<int>()(p.get_x());
    seed ^=
      std::hash<int>()(p.get_y()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

#include "inline_src/Point.inl"
#endif
