#ifndef NITRO_APPLICATION_HPP
#define NITRO_APPLICATION_HPP

#include "Canvas.hpp"
#include "JsonHandler.hpp"
#include "Rectangle.hpp"
#include "RectangleIntersection.hpp"
#include <string>
#include <vector>

namespace nitro {

class Application {
	public:
		/* Defines */
		static const size_t DEFAULT_MAX_RECTS = 10;

		enum class ErrorCode {
			Success = 0,
			TooManyArguments,
			MissingPathArg,
			InvalidFileExtension,
			InvalidSizeArg,
			InvalidFile
		};

		/* Constructor and Destructor*/
		Application(int argc, char **argv);
		~Application() = default;

		/* Functions */
		int run();

	private:
		bool init(int argc, char **argv);
		ErrorCode checkArgCount(int argc) const;
		ErrorCode parseMaxRects(const char *arg);
		ErrorCode parseFile(const std::string &path);
		std::vector<Rectangle> handleInput(const std::string &input);
		// TODO: just call Canvas.intersectAll directly instead of dedicating a whole function to it?
		std::vector<Canvas::RectangleIntersection> handleIntersections(const std::vector<Rectangle> &rectangles);
		void printOutput(const std::vector<Canvas::RectangleIntersection> &intersections) const;
		void printHelp();
		void reportError(ErrorCode errorCode) const;

		bool initialized;
		std::string filePath;
		JsonHandler jsonHandler;
		size_t maxRectangles;
};

} // namespace nitro

#endif // NITRO_APPLICATION_HPP