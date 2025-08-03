#ifndef NITRO_APPLICATION_HPP
#define NITRO_APPLICATION_HPP

#include "Canvas.hpp"
#include "JsonHandler.hpp"
#include "Rectangle.hpp"
#include "RectangleIntersection.hpp"
#include <string>
#include <vector>

#ifdef TEST
#include <gtest/gtest.h>
#endif

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
		Application();
		Application(int argc, char **argv);
		~Application() = default;

		/* Functions */
		int run();

	private:
		bool init(int argc, char **argv);
		ErrorCode checkArgCount(int argc) const;
		ErrorCode parseMaxRects(const char *arg);
		ErrorCode parseFile(const std::string &path);
		std::vector<Rectangle> loadRectangles(const size_t maxRectangles) const;

		void printOutput(const std::vector<Rectangle> &rectangles,
		                 const std::vector<Canvas::RectangleIntersection> &intersections) const;
		void printHelp();
		void reportError(ErrorCode errorCode) const;

		/* Member variables */
		bool initialized;
		JsonHandler jsonHandler;
		Canvas canvas;
		size_t maxRectangles;

		/* For Testing */
#ifdef TEST
		friend class ApplicationTest;
		FRIEND_TEST(ApplicationTest, ArgCountTooLarge);
		FRIEND_TEST(ApplicationTest, ArgCountTooSmall);
		FRIEND_TEST(ApplicationTest, ArgCountBaseCase);
		FRIEND_TEST(ApplicationTest, ArgCountWithMaxRectCountOption);
		FRIEND_TEST(ApplicationTest, MaxRectCountIsNegativeNumber);
		FRIEND_TEST(ApplicationTest, MaxRectCountIsZero);
		FRIEND_TEST(ApplicationTest, InitMissingPathArg);
		FRIEND_TEST(ApplicationTest, InitTooManyArgs);
		FRIEND_TEST(ApplicationTest, InitInvalidMaxRects);
		FRIEND_TEST(ApplicationTest, InitFileDoesNotExist);
		FRIEND_TEST(ApplicationTest, InitSuceedsWithValidFile);
		FRIEND_TEST(ApplicationTest, LoadRectanglesStopsAtMaxRectCount);
		FRIEND_TEST(ApplicationTest, LoadRectanglesDefaultMaxRectCount);
		FRIEND_TEST(ApplicationTest, LoadRectanglesOverridesDefault);
#endif
};

} // namespace nitro

#endif // NITRO_APPLICATION_HPP