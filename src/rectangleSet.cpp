#include "rectangleSet.hpp"

namespace nitro {

    RectangleSet::RectangleSet(const std::set<Rectangle, RectangleComparator> &input) {
        for (const Rectangle& rect : input) {
            this->rectangles.insert(rect);
        }
    }

    std::set<Rectangle, RectangleComparator> RectangleSet::getRectangles() const {
        // return a set of rectangles that 
        return rectangles;
    }

    std::vector<std::vector<Rectangle::ID>> RectangleSet::calculateAllSubsets(size_t maxRectangles) {
        std::vector<Rectangle::ID> subset;
        std::vector<std::vector<Rectangle::ID>> result;

        //TODO: fix magic numbers
        subsetRecursion(1, maxRectangles, 2,  subset, result);
        return result;
    }

    void RectangleSet::subsetRecursion(Rectangle::ID start, Rectangle::ID max, size_t minSize,
                                       std::vector<Rectangle::ID> &subset, 
                                       std::vector<std::vector<Rectangle::ID>> &result) 
    {
        if(subset.size() >= minSize) {
            result.push_back(subset);
        }

        for (Rectangle::ID i = start; i <= max; i++) {
            subset.push_back(i);
            subsetRecursion(i + 1, max, minSize, subset, result);
            subset.pop_back();
        }

    }

} // namespace nitro