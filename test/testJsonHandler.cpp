#include "jsonHandler.hpp"
#include <gtest/gtest.h>

namespace nitro {

TEST(TestJsonHandler, EmptyFileThrowsException) {
	std::string filePath = "test_files/test2-empty-file.json";
	JsonHandler jsonHandler;
	EXPECT_THROW(jsonHandler.loadFile(filePath), std::invalid_argument);
}

TEST(TestJsonHandler, InvalidFilePathThrowsException) {
	std::string filePath = "test_files/thisfiledoesntexist.json";
	JsonHandler jsonHandler;
	EXPECT_THROW(jsonHandler.loadFile(filePath), std::invalid_argument);
}

} // namespace nitro