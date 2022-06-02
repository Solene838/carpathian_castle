#include <gtest/gtest.h>
#include <pugixml.hpp>
#include <Object.h>
#include <Assets.h>
#include <SFML/Graphics.hpp>

TEST(TestTmxLite, AlwaysTrue) {
	EXPECT_EQ(true, true);
}

TEST(TestReadXML, TestObject) {
	std::string s = R"(<?xml version = "1.0"?>
			<Object label="test" x="0" y="1"/>)";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(s.c_str());
	ASSERT_TRUE(result) << result.description();
	Object o{ doc.child("Object") };
	auto o_ref = Object(0, 1, "test", "purse");
	EXPECT_EQ(o.getLabel(), o_ref.getLabel());
	EXPECT_EQ(o.getX(), o_ref.getX());
	EXPECT_EQ(o.getY(), o_ref.getY());
	//EXPECT_EQ(o.getType(), o_ref.getType());
}

TEST(TestMap, TestAddToMap) {
	Assets assets;
	ASSERT_TRUE(assets.getTexturesMap().empty());
	assets.addToMap("purse", "purse");
	ASSERT_FALSE(assets.getTexturesMap().empty());
	ASSERT_EQ(assets.getTexturesMap().find("purse")->first, "purse");
}
