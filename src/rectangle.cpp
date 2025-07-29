#include <stdexcept>
#include <limits>
#include "rectangle.hpp"
#include <iostream> //TODO: rm iostream later

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

    const int64_t maxInt = std::numeric_limits<int>::max();
    std::cout << "topLeft.x: " << topLeft.x << ", width: " << width << '\n';
    if (static_cast<int64_t>(topLeft.x) > maxInt - static_cast<int64_t>(width)) {
        throw std::overflow_error(Rectangle::canvasXBoundExceededErrorMsg);
    }

    if(static_cast<int64_t>(topLeft.y) > maxInt - static_cast<int64_t>(height)) {
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

    const int interLeftEdge = std::max(r1Vertices.topLeft.x, r2Vertices.topLeft.x);
    const int interRightEdge = std::min(r1Vertices.topRight.x, r2Vertices.topRight.x);
    const int interTopEdge = std::max(r1Vertices.topLeft.y, r2Vertices.topLeft.y);
    const int interBottomEdge = std::min(r1Vertices.bottomLeft.y, r2Vertices.bottomLeft.y);
    
    // std::cout << "intLeftEdge: " << interLeftEdge << '\n';
    // std::cout << "intRightEdge: " << interRightEdge << '\n';
    // std::cout << "intTopEdge: " << interTopEdge << '\n';
    // std::cout << "intBottomEdge: " << interBottomEdge << '\n';

    if ((interLeftEdge < interRightEdge) && ( interBottomEdge > interTopEdge)) {
        Vertex2D topLeftVertexX = {interLeftEdge, interTopEdge};
        uint32_t width = static_cast<uint32_t>(interRightEdge - interLeftEdge);
        uint32_t height = static_cast<uint32_t>(interBottomEdge - interTopEdge);
        // std::cout << "topLeft: " << topLeftVertexX.x << ", " << topLeftVertexX.y << '\n';
        // std::cout << "width: " << width << '\n';
        // std::cout << "height: " << height << '\n';
        Rectangle result{topLeftVertexX, width, height};
        return result;
    }

    return std::nullopt;
}

} //namespace nitro