#include <iostream>
#include "rectangle.hpp"

using namespace nitro;

int main() {
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {140, 160}, 250, 100};

    std::optional<Rectangle> interRet = Rectangle::intersection(rectangle, rectangle2);
    return 0;
}