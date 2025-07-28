#include <stdexcept>
#include <limits>
#include "rectangle.hpp"

namespace nitro {
    
const std::string Rectangle::vertexDefErrorMsg = "Vertex definition error";
const std::string Rectangle::underflowErrorMsg = "Underflow error";
const std::string Rectangle::overflowErrorMsg = "Overflow error";
const std::string Rectangle::canvasXBoundExceededErrorMsg = "Rectangle exceeds canvas X bounds";
const std::string Rectangle::canvasYBoundExceededErrorMsg = "Rectangle exceeds canvas Y bounds";

Rectangle::Rectangle(Vertex2D topLeft, uint32_t width, uint32_t height) {
    // overflow, underflow checks
    if (width == 0 || height == 0) {
        throw std::overflow_error(Rectangle::underflowErrorMsg);
    }

    const uint32_t maxInt = std::numeric_limits<uint32_t>::max();
    if(topLeft.x > maxInt - width) {
        throw std::overflow_error(Rectangle::canvasXBoundExceededErrorMsg);
    }

    if(topLeft.y > maxInt - height) {
        throw std::underflow_error(Rectangle::canvasYBoundExceededErrorMsg);
    }
    
    vertices.topLeft = topLeft;
    vertices.bottomLeft = {topLeft.x, topLeft.y + static_cast<int>(height)};
    vertices.topRight = {topLeft.x + static_cast<int>(width), topLeft.y};
    vertices.bottomRight = {vertices.topRight.x, vertices.bottomLeft.y};

    if (!Rectangle::validateVertices(vertices.bottomLeft, vertices.bottomRight, vertices.topLeft, vertices.topRight)) {
        throw std::invalid_argument(Rectangle::vertexDefErrorMsg);
    }

    this->width = width;
    this->height = height;
}

Rectangle::Vertices Rectangle::getVertices() const{
    return vertices;
}

uint32_t Rectangle::getWidth() const {
    return width;
}

uint32_t Rectangle::getHeight() const {
    return height;
}

bool Rectangle::validateVertices(const Vertex2D &bottomLeft, const Vertex2D &bottomRight, 
                                 const Vertex2D &topLeft, const Vertex2D &topRight) {
    return  bottomLeft.y == bottomRight.y &&
            bottomLeft.x == topLeft.x &&
            bottomRight.x == topRight.x &&
            topLeft.y == topRight.y &&
            bottomLeft.x < topRight.x &&
            bottomLeft.y > topRight.y;
}

std::optional<Rectangle> Rectangle::intersection(const Rectangle &rectangle1, const Rectangle &rectangle2) {
    Rectangle::Vertices r1Vertices = rectangle1.getVertices();
    Rectangle::Vertices r2Vertices = rectangle2.getVertices();

    const int intLeftEdge = std::max(r1Vertices.topLeft.x, r2Vertices.topLeft.x);
    const int intRightEdge = std::min(r1Vertices.topRight.x, r2Vertices.topRight.x);
    const int intTopEdge = std::max(r1Vertices.topLeft.y, r2Vertices.topLeft.y);
    const int intBottomEdge = std::min(r1Vertices.bottomLeft.y, r2Vertices.bottomLeft.y);

    if ((intLeftEdge < intRightEdge) && ( intBottomEdge > intTopEdge)) {
        Vertex2D topLeftVertexX = {intLeftEdge, intTopEdge};
        uint32_t width = static_cast<uint32_t>(intRightEdge - intLeftEdge);
        uint32_t height = static_cast<uint32_t>(intBottomEdge - intTopEdge);
        Rectangle result{topLeftVertexX, width, height};
        return result;
    }

    return std::nullopt;
}

} //namespace nitro