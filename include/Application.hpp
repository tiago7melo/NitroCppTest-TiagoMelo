#ifndef NITRO_APPLICATION_HPP
#define NITRO_APPLICATION_HPP

#include <string>
#include <vector>
#include "Rectangle.hpp"
#include "Canvas.hpp"
#include "RectangleIntersection.hpp"

namespace nitro {

class Application {
	public:
    Application(int argc, char **argv);
    ~Application() = default;
    
        // TODO: don't forget to try catch stuff
        void run();

    private:
        bool validateInput(int argc, char **argv);
        std::vector<Rectangle> handleInput(const std::string &input);
        //TODO: just call Canvas.intersectAll directly instead of dedicating a whole function to it?
        std::vector<Canvas::RectangleIntersection> handleIntersections(const std::vector<Rectangle> &rectangles);
        void printIntersections(const std::vector<Canvas::RectangleIntersection> &intersections) const;
        void printHelp();

        std::string filePath;
        size_t maxRectangles;
    };

} // namespace nitro

#endif // NITRO_APPLICATION_HPP