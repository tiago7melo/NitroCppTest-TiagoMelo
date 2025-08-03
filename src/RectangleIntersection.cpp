#include "RectangleIntersection.hpp"
#include <stdexcept>
#include <string>

namespace nitro {

Canvas::RectangleIntersection::RectangleIntersection(const Rectangle &shape, const std::set<Rectangle::ID> &members)
    : shape{shape}, intersectingRectangles{members} {

	for (const auto &id : this->intersectingRectangles) {
		if (id <= 0) {
			throw std::invalid_argument("RectangleIntersection: All rectangle IDs must be > 0");
		}
	}
}

Rectangle Canvas::RectangleIntersection::getShape() const {
	return shape;
}

std::set<Rectangle::ID> Canvas::RectangleIntersection::getIntersectingRectangles() const {
	return intersectingRectangles;
}

Rectangle::ID Canvas::RectangleIntersection::getRectIdAtIndex(size_t index) const {
	if (index >= intersectingRectangles.size()) {
		throw std::out_of_range("Index out of range");
	}

	auto it = intersectingRectangles.begin();
	std::advance(it, index);
	return *it;
}

std::string Canvas::RectangleIntersection::toString() const {
	std::string result = "Between rectangles ";
	size_t i = 0;
	for (Rectangle::ID id : intersectingRectangles) {
		result += std::to_string(id);

		if (i < intersectingRectangles.size() - 2) {
			result += ", ";
		} else if (i < intersectingRectangles.size() - 1) {
			result += " and ";
		}
		i++;
	}
	result += " at ";
	Rectangle shape = this->getShape();
	result += "(" + std::to_string(shape.getVertices().topLeft.x) + ", " +
	          std::to_string(shape.getVertices().topLeft.y) + ") w=" + std::to_string(shape.getWidth()) +
	          ", h=" + std::to_string(shape.getHeight());
	return result;
}

} // namespace nitro