#include <SDL3pp/SDL.hpp>
#include <SDL3/SDL.h>
#include <iostream>
#include <array>

#include <vector>
#include <memory>

class Personne
{};

int main(void)
{
    sdl::Rect rect {0, 0, 100, 100};
    sdl::Rect rect2 {99, 100, -20, -20};

    sdl::Point a {10, 20};
    std::pair<int, int> b {10, 20};

    sdl::Point c = a + b;

    std::cout << c << std::endl;

    std::cout << std::boolalpha << rect.intersects(rect2) << std::endl;
    std::cout << rect2.get_width() << std::endl;

    return 0;
}

