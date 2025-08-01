#include "RectangleIntersection.hpp"
#include <stdexcept>
#include <string>

namespace nitro {

const std::string Canvas::RectangleIntersection::outOfRangeErrorMsg = "Index out of range";

Canvas::RectangleIntersection::RectangleIntersection(const Rectangle &shape, const std::set<Rectangle::ID> &members)
    : shape{shape}, intersectingRectangles{members} {

	// TODO: verify uniqueness of members IDs
	// TODO: if we rework this to be uncoupled from Canvas, we'll need to verify
	// that all IDs are valid
	// TODO: IDs also have to be > 0, but that will be automatically checked if we
	// change to std::set<Rectangle>
}

Rectangle Canvas::RectangleIntersection::getShape() const {
	return shape;
}

std::set<Rectangle::ID> Canvas::RectangleIntersection::getIntersectingRectangles() const {
	return intersectingRectangles;
}

Rectangle::ID Canvas::RectangleIntersection::getRectIdAtIndex(size_t index) const {
	if (index >= intersectingRectangles.size()) {
		throw std::out_of_range(Canvas::RectangleIntersection::outOfRangeErrorMsg);
	}

	auto it = intersectingRectangles.begin();
	std::advance(it, index);
	return *it;
}

std::string Canvas::RectangleIntersection::toString() const {
	std::string result = "Between rectangles ";
	for (Rectangle::ID id : intersectingRectangles) {
		result += std::to_string(id) + ", ";
	}
	result += "at ";
	Rectangle shape = this->getShape();
	result += "(" + std::to_string(shape.getVertices().topLeft.x) + ", " +
	          std::to_string(shape.getVertices().topLeft.y) + ") w=" + std::to_string(shape.getWidth()) +
	          ", h=" + std::to_string(shape.getHeight());
	return result;
}

} // namespace nitro