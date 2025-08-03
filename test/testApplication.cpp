#include "Application.hpp"
#include <filesystem>
#include <gtest/gtest.h>

namespace nitro {

class ApplicationTest : public ::testing::Test {
	protected:
		void SetUp() override {
		}

		void TearDown() override {
		}

		std::vector<char *> createArgv(const std::vector<std::string> &args) {
			std::vector<char *> argv;
			for (auto &arg : args) {
				argv.push_back(const_cast<char *>(arg.c_str()));
			}
			return argv;
		}

		std::string getPathToTestFile(std::string filename) {
			std::filesystem::path cwd = std::filesystem::current_path();
			std::filesystem::path testFilePath =
			    std::filesystem::current_path().parent_path() / "test" / "test_files" / filename;
			return testFilePath.string();
		}
};

TEST_F(ApplicationTest, ArgCountTooLarge) {
    std::vector<std::string> args = {"rectangle_intersect", "json", "10", "20"};    
    std::vector<char *> argv = createArgv(args);
	Application app(argv.size(), argv.data());
	ASSERT_EQ(app.checkArgCount(argv.size()), Application::ErrorCode::TooManyArguments);
	ASSERT_EQ(app.run(), 1);
}

TEST_F(ApplicationTest, ArgCountTooSmall) {
    std::vector<std::string> args = {"rectangle_intersect"};    
    std::vector<char *> argv = createArgv(args);
	Application app(argv.size(), argv.data());
	ASSERT_EQ(app.checkArgCount(argv.size()), Application::ErrorCode::MissingPathArg);
	ASSERT_EQ(app.run(), 1);
}

TEST_F(ApplicationTest, ArgCountBaseCase) {
    std::vector<std::string> args = {"rectangle_intersect", "json"};    
    std::vector<char *> argv = createArgv(args);
	Application app(argv.size(), argv.data());
	ASSERT_EQ(app.checkArgCount(argv.size()), Application::ErrorCode::Success);
}

TEST_F(ApplicationTest, ArgCountWithMaxRectCountOption) {
    std::vector<std::string> args = {"rectangle_intersect", "json", "5"};    
    std::vector<char *> argv = createArgv(args);
	Application app(argv.size(), argv.data());
	ASSERT_EQ(app.checkArgCount(argv.size()), Application::ErrorCode::Success);
}

TEST_F(ApplicationTest, MaxRectCountIsNegativeNumber) {
    std::vector<std::string> args = {"rectangle_intersect", "json", "-1"};    
    std::vector<char *> argv = createArgv(args);
	Application app(argv.size(), argv.data());
	ASSERT_EQ(app.parseMaxRects(argv[2]), Application::ErrorCode::InvalidSizeArg);
}

TEST_F(ApplicationTest, MaxRectCountIsZero) {
    std::vector<std::string> args = {"rectangle_intersect", "json", "0"};    
    std::vector<char *> argv = createArgv(args);
	Application app(argv.size(), argv.data());
	ASSERT_EQ(app.parseMaxRects(argv[2]), Application::ErrorCode::Success);
}

TEST_F(ApplicationTest, InitMissingPathArg) {
    std::vector<std::string> args = {"rectangle_intersect"};    
    std::vector<char *> argv = createArgv(args);
    Application app(argv.size(), argv.data());
    ASSERT_FALSE(app.init(argv.size(), argv.data()));
}

TEST_F(ApplicationTest, InitTooManyArgs) {
    std::vector<std::string> args = {"rectangle_intersect", "file.json", "42", "7", "123"};    
    std::vector<char *> argv = createArgv(args);
    Application app(argv.size(), argv.data());
    ASSERT_FALSE(app.init(argv.size(), argv.data()));
}

TEST_F(ApplicationTest, InitInvalidMaxRects) {
    std::vector<std::string> args = {"rectangle_intersect", "file.json", "-1"};    
    std::vector<char *> argv = createArgv(args);
    Application app(argv.size(), argv.data());
    ASSERT_FALSE(app.init(argv.size(), argv.data()));
}

TEST_F(ApplicationTest, InitFileDoesNotExist) {
    std::vector<std::string> args = {"rectangle_intersect", "not_a_file.json"};    
    std::vector<char *> argv = createArgv(args);
    Application app(argv.size(), argv.data());
    ASSERT_FALSE(app.init(argv.size(), argv.data()));
}

TEST_F(ApplicationTest, InitSuceedsWithValidFile) {
    std::string path = getPathToTestFile("test1-specification-example.json");
    std::vector<std::string> args = {"rectangle_intersect", path};    
    std::vector<char *> argv = createArgv(args);

    Application app(argv.size(), argv.data());
    ASSERT_TRUE(app.init(argv.size(), argv.data()));
}

TEST_F(ApplicationTest, LoadRectanglesStopsAtMaxRectCount) {
    std::string path = getPathToTestFile("test1-specification-example.json");
    std::vector<std::string> args = {"rectangle_intersect", path};    
    std::vector<char *> argv = createArgv(args);

    Application app(argv.size(), argv.data());
    ASSERT_TRUE(app.init(argv.size(), argv.data()));

    std::vector<Rectangle> rectangles = app.loadRectangles(1);
    ASSERT_EQ(rectangles.size(), 1);
}

TEST_F(ApplicationTest, LoadRectanglesDefaultMaxRectCount) {
    std::string path = getPathToTestFile("test10-twelverectangles.json");
    std::vector<std::string> args = {"rectangle_intersect", path};    
    std::vector<char *> argv = createArgv(args);

    Application app(argv.size(), argv.data());
    ASSERT_TRUE(app.init(argv.size(), argv.data()));

    size_t maxRects = Application::DEFAULT_MAX_RECTS;
    std::vector<Rectangle> rectangles = app.loadRectangles(maxRects);
    ASSERT_EQ(rectangles.size(), maxRects);
}

TEST_F(ApplicationTest, LoadRectanglesOverridesDefault) {
    std::string path = getPathToTestFile("test10-twelverectangles.json");
    std::vector<std::string> args = {"rectangle_intersect", path};    
    std::vector<char *> argv = createArgv(args);

    Application app(argv.size(), argv.data());
    ASSERT_TRUE(app.init(argv.size(), argv.data()));

    size_t maxRects = 12;
    std::vector<Rectangle> rectangles = app.loadRectangles(maxRects);
    ASSERT_EQ(rectangles.size(), maxRects);
}

} // namespace nitro
