#include <stdexcept>
#include "canvas.hpp"
#include <iostream>

namespace nitro {

const std::string Canvas::outOfRangeErrorMsg = "Index out of range";

Canvas::Canvas(const std::set<Rectangle> &input) : rectangles{input} {
    //TODO: consider warning if you're trying to put a rectangle with an ID that already exists?
}

std::set<Rectangle> Canvas::getRectangles() const {
    return rectangles;
}

size_t Canvas::getSize() const {
    return rectangles.size();
}

Rectangle Canvas::getRectangleAtIndex(size_t index) const {
    if(index >= rectangles.size()) {
        throw::std::out_of_range(Canvas::outOfRangeErrorMsg);
    }

    auto it = rectangles.begin();
    std::advance(it, index);
    return *it;
}

const std::vector<RectangleIntersection> Canvas::intersectAll() {
    std::optional<std::set<RectangleIntersection>> pairwiseIntersections = this->determinePairwiseIntersections();

    if (pairwiseIntersections.has_value()) {
        std::optional<std::set<RectangleIntersection>> allIntersections = this->determineAllIntersections(pairwiseIntersections.value());
        if (allIntersections.has_value()) {
            return std::vector<RectangleIntersection>(allIntersections.value().begin(), allIntersections.value().end());
        }
    }

    return std::vector<RectangleIntersection>();
}

std::optional<std::set<RectangleIntersection>> Canvas::determinePairwiseIntersections() {
    std::set<RectangleIntersection> result;
    for(size_t i = 0; i < this->rectangles.size(); i++) {
        for(size_t j = i + 1; j < this->rectangles.size(); j++) {
            Rectangle rectangle1 = this->getRectangleAtIndex(i);
            Rectangle rectangle2 = this->getRectangleAtIndex(j);
            std::optional<Rectangle> intersection = Rectangle::intersection(rectangle1, rectangle2);
            if (intersection.has_value()) {
                RectangleIntersection rectangleIntersection{intersection.value(), {rectangle1.getId(), rectangle2.getId()}};
                result.insert(rectangleIntersection);
            }
        }
    } 
    
    return result.empty() ? std::nullopt : std::make_optional(result);
}

std::optional<std::set<RectangleIntersection>> Canvas::determineAllIntersections(const std::set<RectangleIntersection> &pairwiseIntersections) {
    std::set<RectangleIntersection> result{pairwiseIntersections.begin(), pairwiseIntersections.end()};
    std::vector<RectangleIntersection> current{pairwiseIntersections.begin(), pairwiseIntersections.end()};
    std::set<std::set<Rectangle::ID>> intersectionsFound;

    bool moreIntersectionsHappened = true;
    while (moreIntersectionsHappened)    {
        moreIntersectionsHappened = false;
        std::vector<RectangleIntersection> next;
        for(const RectangleIntersection &intersection : current) {
            for(size_t i = 0; i < this->rectangles.size(); i++) {
                Rectangle::ID baseRectangleId = i + 1;
                std::set<Rectangle::ID> intersectingRectangles = intersection.getIntersectingRectangles();

                if(intersectingRectangles.find(baseRectangleId) != intersectingRectangles.end()) {
                    continue;
                }
                
                std::optional<Rectangle> intersectionShape = Rectangle::intersection(intersection.getShape(), this->getRectangleAtIndex(i));
                if (!intersectionShape.has_value()) {
                    continue;
                }

                intersectingRectangles.insert(baseRectangleId);
                if(intersectionsFound.find(intersectingRectangles) != intersectionsFound.end()) {
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