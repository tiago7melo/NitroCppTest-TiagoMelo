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
		std::optional<std::vector<Rectangle>> loadRectangles(const size_t maxRectangles) const;

		void printOutput(const std::vector<Rectangle> &rectangles,
		                 const std::vector<Canvas::RectangleIntersection> &intersections) const;
		void printHelp();
		void reportError(ErrorCode errorCode) const;

		bool initialized;
		std::string filePath;
		JsonHandler jsonHandler;
		size_t maxRectangles;
};

} // namespace nitro

#endif // NITRO_APPLICATION_HPP