#include <stdexcept>
#include "rectangleSet.hpp"
#include <iostream>

namespace nitro {

const std::string RectangleSet::outOfRangeErrorMsg = "Index out of range";

RectangleSet::RectangleSet(const std::set<Rectangle> &input) : rectangles{input} {
    //TODO: consider warning if you're trying to put a rectangle with an ID that already exists?
}

std::set<Rectangle> RectangleSet::getRectangles() const {
    return rectangles;
}

size_t RectangleSet::getSize() const {
    return rectangles.size();
}

Rectangle RectangleSet::getRectangleAtIndex(size_t index) const {
    if(index >= rectangles.size()) {
        throw::std::out_of_range(RectangleSet::outOfRangeErrorMsg);
    }

    auto it = rectangles.begin();
    std::advance(it, index);
    return *it;
}

const std::vector<RectangleIntersection> RectangleSet::intersectAll() {
    std::optional<std::set<RectangleIntersection>> pairwiseIntersections = this->determinePairwiseIntersections();

    if (pairwiseIntersections.has_value()) {
        std::optional<std::set<RectangleIntersection>> allIntersections = this->determineAllIntersections(pairwiseIntersections.value());
        if (allIntersections.has_value()) {
            return std::vector<RectangleIntersection>(allIntersections.value().begin(), allIntersections.value().end());
        }
    }

    return std::vector<RectangleIntersection>();
}

std::optional<std::set<RectangleIntersection>> RectangleSet::determinePairwiseIntersections() {
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

std::optional<std::set<RectangleIntersection>> RectangleSet::determineAllIntersections(const std::set<RectangleIntersection> &pairwiseIntersections) {
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
                
                std::optional<Rectangle> interSectionShape = Rectangle::intersection(intersection.getShape(), this->getRectangleAtIndex(i));
                if (!interSectionShape.has_value()) {
                    continue;
                }

                intersectingRectangles.insert(baseRectangleId);
                if(intersectionsFound.find(intersectingRectangles) != intersectionsFound.end()) {
                    continue;
                }
                intersectionsFound.insert(intersectingRectangles);

                RectangleIntersection newIntersection{interSectionShape.value(), intersectingRectangles};
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