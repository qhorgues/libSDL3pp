#ifndef SDL3PP_RANGES_HPP
#define SDL3PP_RANGES_HPP

#include <concepts>
#include <ranges>

template <typename T, typename U>
concept range_of = std::ranges::range<T> && std::same_as<std::ranges::range_value_t<T>, U>;


template <typename T, typename U>
concept base_range_of = std::ranges::range<T> && std::is_base_of_v<std::ranges::range_value_t<T>, U>;

#endif