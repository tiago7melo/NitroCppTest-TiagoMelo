#include <iostream>
#include "rectangle.hpp"
#include "rectangleIntersection.hpp"

using namespace nitro;

int main() {
    Rectangle rectangle{1, {100, 100}, 250, 80};
    Rectangle rectangle2{2, {140, 160}, 250, 100};

    std::optional<Rectangle> interRect = Rectangle::intersection(rectangle, rectangle2);
    Canvas::RectangleIntersection inter = Canvas::RectangleIntersection(interRect.value(), {1, 2});
    Rectangle shape = inter.getShape();
    std::cout << "(x, y, w, h): " << shape.getVertices().topLeft.x << ", " << shape.getVertices().topLeft.y << ", " << shape.getWidth() << ", " << shape.getHeight() << '\n';
    return 0;
}