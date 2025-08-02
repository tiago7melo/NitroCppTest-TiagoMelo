#include "Canvas.hpp"
#include "RectangleIntersection.hpp"
#include <iostream>
#include <stdexcept>

namespace nitro {

Canvas::Canvas(const std::vector<Rectangle> &input) {
	std::set<Rectangle::ID> seen;
	for (const auto &rect : input) {
		int id = rect.getId();
		if (seen.find(id) != seen.end()) {
			throw std::invalid_argument("Duplicate ID: " + std::to_string(id));
		}

		seen.insert(id);
		rectangles.insert(rect);
	}
}

std::set<Rectangle> Canvas::getRectangles() const {
	return rectangles;
}

size_t Canvas::getRectangleCount() const {
	return rectangles.size();
}

Rectangle Canvas::getRectangleAtIndex(size_t index) const {
	if (index >= rectangles.size()) {
		throw std::out_of_range("Index out of range");
	}

	auto it = rectangles.begin();
	std::advance(it, index);
	return *it;
}

const std::vector<Canvas::RectangleIntersection> Canvas::intersectAll() {
	std::optional<std::set<Canvas::RectangleIntersection>> pairwiseIntersections =
	    this->determinePairwiseIntersections();

	if (pairwiseIntersections.has_value()) {
		std::optional<std::set<Canvas::RectangleIntersection>> allIntersections =
		    this->determineAllIntersections(pairwiseIntersections.value());
		return std::vector<Canvas::RectangleIntersection>(allIntersections.value().begin(),
		                                                  allIntersections.value().end());
	}

	return std::vector<Canvas::RectangleIntersection>();
}

std::optional<std::set<Canvas::RectangleIntersection>> Canvas::determinePairwiseIntersections() {
	// Determines all 2nd-order intersections: intersections that only have 2 intersecting rectangles
	// Utilized as the basis to determine all higher order intersections
	std::set<Canvas::RectangleIntersection> result;
	for (size_t i = 0; i < this->rectangles.size(); i++) {
		for (size_t j = i + 1; j < this->rectangles.size(); j++) {
			Rectangle rectangle1 = this->getRectangleAtIndex(i);
			Rectangle rectangle2 = this->getRectangleAtIndex(j);
			std::optional<Rectangle> intersection = Rectangle::intersection(rectangle1, rectangle2);
			if (intersection.has_value()) {
				Canvas::RectangleIntersection rectangleIntersection{intersection.value(),
				                                                    {rectangle1.getId(), rectangle2.getId()}};
				result.insert(rectangleIntersection);
			}
		}
	}

	return result.empty() ? std::nullopt : std::make_optional(result);
}

//TODO: try to improve clarity of algorithm by showing its analogous to a BFS
std::optional<std::set<Canvas::RectangleIntersection>>
Canvas::determineAllIntersections(const std::set<RectangleIntersection> &pairwiseIntersections) {
	// Determines all higher-order intersections: intersections with 3+ intersecting rectangles
	std::set<RectangleIntersection> result{pairwiseIntersections.begin(), pairwiseIntersections.end()};
	std::vector<RectangleIntersection> current{pairwiseIntersections.begin(), pairwiseIntersections.end()};
	std::set<std::set<Rectangle::ID>> intersectionsFound;
	// TODO: max rectangles sanity check?
	bool moreIntersectionsHappened = true;
	while (moreIntersectionsHappened) {
		moreIntersectionsHappened = false;
		std::vector<RectangleIntersection> next;
		for (const RectangleIntersection &intersection : current) {
			// All intersections are considered as virtual rectangles that can be intersected with the actual rectangles
			// in order to form new higher-order intersections
			for (size_t i = 0; i < this->rectangles.size(); i++) {
				Rectangle::ID baseRectangleId = i + 1;
				std::set<Rectangle::ID> intersectingRectangles = intersection.getIntersectingRectangles();

				if (intersectingRectangles.find(baseRectangleId) != intersectingRectangles.end()) {
					continue;
				}

				std::optional<Rectangle> intersectionShape =
				    Rectangle::intersection(intersection.getShape(), this->getRectangleAtIndex(i));
				if (!intersectionShape.has_value()) {
					continue;
				}

				intersectingRectangles.insert(baseRectangleId);
				if (intersectionsFound.find(intersectingRectangles) != intersectionsFound.end()) {
					continue;
				}
				intersectionsFound.insert(intersectingRectangles);

				RectangleIntersection newIntersection{intersectionShape.value(), intersectingRectangles};
				result.insert(newIntersection);
				next.push_back(newIntersection);

				moreIntersectionsHappened = true;
			}
		}
		current = next;
	}

	return result.empty() ? std::nullopt : std::make_optional(result);
}

} // namespace nitro