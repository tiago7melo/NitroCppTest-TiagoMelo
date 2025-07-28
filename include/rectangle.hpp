#ifndef NITRO_RECTANGLE_HPP
#define NITRO_RECTANGLE_HPP

#include <cstdint>
#include <string>
#include "vertex.hpp"

namespace nitro {
    
class Rectangle {
    public:
        typedef struct {
            Vertex2D bottomLeft;
            Vertex2D bottomRight;
            Vertex2D topLeft;
            Vertex2D topRight;
        } Vertices;

        Rectangle();
        // Rectangle(Vertex2D bottomLeft, Vertex2D bottomRight, Vertex2D topLeft, Vertex2D topRight);
        Rectangle(Vertex2D topLeft, uint32_t width, uint32_t height);
        ~Rectangle() = default;

        const Vertices getVertices(); 
        const uint32_t getWidth();
        const uint32_t getHeight();
        const bool empty();
        const bool valid();

        static const std::string vertexDefErrorMsg;
        static const std::string underflowErrorMsg;
        static const std::string overflowErrorMsg;
        static const std::string canvasXBoundExceededErrorMsg;
        static const std::string canvasYBoundExceededErrorMsg;
        static const std::string accessEmptyRectangleErrorMsg;
        static const std::string accessInvalidRectangleErrorMsg;
        
    private:
        static bool validateVertices(const Vertex2D &bottomLeft, const Vertex2D &bottomRight, 
                                     const Vertex2D &topLeft, const Vertex2D &topRight);

        bool m_empty = true;
        bool m_valid = false;
        Vertices vertices;
        uint32_t width;
        uint32_t height;
};

} // namespace nitro
#endif // NITRO_RECTANGLE_HPP