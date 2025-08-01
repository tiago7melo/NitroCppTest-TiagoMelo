#include "Rectangle.hpp"
#include "RectangleIntersection.hpp"
#include <iostream>

using namespace nitro;

int main() {
	Rectangle rectangle{1, {100, 100}, 250, 80};
	Rectangle rectangle2{2, {140, 160}, 250, 100};

	std::optional<Rectangle> interRect = Rectangle::intersection(rectangle, rectangle2);
	Canvas::RectangleIntersection inter = Canvas::RectangleIntersection(interRect.value(), {1, 2});
	std::cout << inter.toString() << std::endl;
	return 0;
}