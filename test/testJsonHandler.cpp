#include "JsonHandler.hpp"
#include "Rectangle.hpp"
#include <gtest/gtest.h>
namespace nitro {

TEST(JsonHandlerTest, EmptyFileThrowsException) {
	std::string filePath = "test/test_files/test2-empty-file.json";
	JsonHandler jsonHandler;
	EXPECT_THROW(jsonHandler.loadFile(filePath), std::runtime_error);
	try {
		jsonHandler.loadFile(filePath);
	} catch (const std::runtime_error &e) {
		EXPECT_STREQ(e.what(), "File is empty:  test/test_files/test2-empty-file.json");
	}
}

TEST(JsonHandlerTest, InvalidFilePathThrowsException) {
	std::string filePath = "test/test_files/thisfiledoesntexist.json";
	JsonHandler jsonHandler;
	EXPECT_THROW(jsonHandler.loadFile(filePath), std::runtime_error);
	try {
		jsonHandler.loadFile(filePath);
	} catch (const std::runtime_error &e) {
		ASSERT_STREQ(e.what(), "File does not exist:  test/test_files/thisfiledoesntexist.json");
	}
}

TEST(JsonHandlerTest, InvalidJSONThrowsException) {
	std::string filePath = "test/test_files/test3-invalid.json";
	JsonHandler jsonHandler;
	EXPECT_THROW(jsonHandler.loadFile(filePath), std::runtime_error);
	try {
		jsonHandler.loadFile(filePath);
	} catch (const std::runtime_error &e) {
        ASSERT_TRUE(std::string(e.what()).contains("Could not parse JSON at  test/test_files/test3-invalid.json"));
	}
}

TEST(JsonHandlerTest, TryToOpenDirectoryThrowsException) {
	std::string filePath = "test/test_files/";
	JsonHandler jsonHandler;
	EXPECT_THROW(jsonHandler.loadFile(filePath), std::invalid_argument);
	try {
		jsonHandler.loadFile(filePath);
	} catch (const std::invalid_argument &e) {
        ASSERT_TRUE(std::string(e.what()).contains("Path is a directory"));
	}
}

TEST(JsonHandlerTest, ValidFileLoads) {
	std::string filePath = "test/test_files/test1-specification-example.json";
	JsonHandler jsonHandler;
    bool ret = jsonHandler.loadFile(filePath);
    ASSERT_TRUE(ret);
    ASSERT_TRUE(jsonHandler.valid());
}

TEST(JsonHandlerTest, GetArrayBaseCase) {
	std::string filePath = "test/test_files/test1-specification-example.json";
	JsonHandler jsonHandler;
    bool ret = jsonHandler.loadFile(filePath);
    ASSERT_TRUE(ret);
    ASSERT_TRUE(jsonHandler.valid());

    std::optional<json> array = jsonHandler.getArray("rects");
    ASSERT_TRUE(array.has_value());
    ASSERT_EQ(array.value().size(), 4);
    
    std::vector<json> rects = array.value();
    for(auto rect : rects) {
        ASSERT_TRUE(rect.contains("x"));
        ASSERT_TRUE(rect["x"].is_number_integer());
        ASSERT_TRUE(rect.contains("y"));
        ASSERT_TRUE(rect["y"].is_number_integer());
        ASSERT_TRUE(rect.contains("w"));
        ASSERT_TRUE(rect["w"].is_number_integer());
        ASSERT_TRUE(rect.contains("h"));
        ASSERT_TRUE(rect["h"].is_number_integer());
    }
}

TEST(JsonHandlerTest, GetRectanglesNotAnArray) {
    std::string filePath = "test/test_files/test6-notanarray.json";
    JsonHandler jsonHandler;
    bool ret = jsonHandler.loadFile(filePath);
    ASSERT_TRUE(ret);
    ASSERT_TRUE(jsonHandler.valid());

    EXPECT_THROW(jsonHandler.getArray("rects"), std::runtime_error);
    try {
		std::optional<json> j = jsonHandler.getArray("rects");
	} catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
		ASSERT_TRUE(std::string(e.what()) == "JSON Object at key [rects] is not an array");
	}
}

TEST(JsonHandlerTest, GetKeyThatDoesntExist) {
    std::string filePath = "test/test_files/test1-specification-example.json";
    JsonHandler jsonHandler;
    bool ret = jsonHandler.loadFile(filePath);
    ASSERT_TRUE(ret);
    ASSERT_TRUE(jsonHandler.valid());

    EXPECT_THROW(jsonHandler.getArray("circles"), std::runtime_error);
    try {
		std::optional<json> j = jsonHandler.getArray("circles");
	} catch (const std::runtime_error &e) {
        std::cout << e.what() << std::endl;
		ASSERT_TRUE(std::string(e.what()) == "JSON File does not contain key: circles");
	}
}

TEST(JsonHandlerTest, UnmarshalSingleRectangleBaseCase) {
	std::string filePath = "test/test_files/test4-singlerect.json";
	JsonHandler jsonHandler;
    bool ret = jsonHandler.loadFile(filePath);
    ASSERT_TRUE(ret);
    ASSERT_TRUE(jsonHandler.valid());

    std::optional<json> j = jsonHandler.getArray("rects").value();
    ASSERT_TRUE(j.has_value());
    ASSERT_EQ(j.value().size(), 1);

    std::optional<Rectangle> rect = jsonHandler.unmarshal<Rectangle>(j.value()[0]);

    ASSERT_TRUE(rect.has_value());
    Rectangle expected(Rectangle::ID_UNDEFINED, {100, 100}, 250, 80);
    ASSERT_EQ(rect.value(), expected);
}

TEST(JsonHandlerTest, UnmarshalMalformedRectangle) {
	std::string filePath = "test/test_files/test5-singlerect-missingfields.json";
	JsonHandler jsonHandler;
    bool ret = jsonHandler.loadFile(filePath);
    ASSERT_TRUE(ret);
    ASSERT_TRUE(jsonHandler.valid());

    std::optional<json> j = jsonHandler.getArray("rects").value();
    ASSERT_TRUE(j.has_value());
    ASSERT_EQ(j.value().size(), 1);

    EXPECT_THROW(jsonHandler.unmarshal<Rectangle>(j.value()[0]), std::runtime_error);
    try {
		std::optional<Rectangle> rect = jsonHandler.unmarshal<Rectangle>(j.value()[0]);
	} catch (const std::runtime_error &e) {
		EXPECT_STREQ(e.what(), "JSON Object does not define a rectangle");
	}
}

TEST(JsonHandlerTest, UnmarshalRectanglesBaseCase) {
    std::string filePath = "test/test_files/test1-specification-example.json";
    JsonHandler jsonHandler;
    bool ret = jsonHandler.loadFile(filePath);
    ASSERT_TRUE(ret);
    ASSERT_TRUE(jsonHandler.valid());

    std::optional<json> j = jsonHandler.getArray("rects").value();
    ASSERT_TRUE(j.has_value());
    ASSERT_EQ(j.value().size(), 4);

    std::optional<std::vector<Rectangle>> rects = jsonHandler.unmarshal<std::vector<Rectangle>>(j.value());
    ASSERT_TRUE(rects.has_value());
    ASSERT_EQ(rects.value().size(), 4);

    std::vector<Rectangle> expected{{Rectangle::ID_UNDEFINED, {100, 100}, 250, 80},
                                    {Rectangle::ID_UNDEFINED, {120, 200}, 250, 150},
                                    {Rectangle::ID_UNDEFINED, {140, 160}, 250, 100},
                                    {Rectangle::ID_UNDEFINED, {160, 140}, 350, 190}};

    ASSERT_EQ(rects.value(), expected);
}

TEST(JsonHandlerTest, UnMarshalRectanglesNotAnArray) {
    std::string filePath = "test/test_files/test6-notanarray.json";
    JsonHandler jsonHandler;
    bool ret = jsonHandler.loadFile(filePath);
    ASSERT_TRUE(ret);
    ASSERT_TRUE(jsonHandler.valid());

    json j = {
        {"rectangles", "this is not an array"}
    };

    EXPECT_THROW(jsonHandler.unmarshal<std::vector<Rectangle>>(j), std::runtime_error);
    try {
		std::optional<std::vector<Rectangle>> rects = jsonHandler.unmarshal<std::vector<Rectangle>>(j);
	} catch (const std::runtime_error &e) {
		EXPECT_STREQ(e.what(), "JSON Object is not an array");
	}
}

} // namespace nitro