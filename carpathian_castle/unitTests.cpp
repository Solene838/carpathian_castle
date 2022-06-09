#include <gtest/gtest.h>
#include <pugixml.hpp>
#include <Object.h>
#include <Pickable.h>
#include <Door.h>
#include <Assets.h>
#include <SFML/Graphics.hpp>

TEST(TestReadXML, TestObject) {
	std::string s = R"(<?xml version = "1.0"?>
			<Object label="test" x="0" y="1" category="purse"/>)";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(s.c_str());
	ASSERT_TRUE(result) << result.description();
	Object o{ doc.child("Object") };
	auto o_ref = Object(0, 1, "test", "purse");
	EXPECT_EQ(o.getLabel(), o_ref.getLabel());
	EXPECT_EQ(o.getX(), o_ref.getX());
	EXPECT_EQ(o.getY(), o_ref.getY());
	EXPECT_EQ(o.getCategory(), o_ref.getCategory());
}

TEST(TestReadXML, TestPickable) {
	std::string s = R"(<?xml version = "1.0"?>
			<Pickable label="test" x="0" y="1" category="purse" is_locked="false"/>)";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(s.c_str());
	ASSERT_TRUE(result) << result.description();
	Pickable p{ doc.child("Pickable") };
	auto p_ref = Pickable(0, 1, "test", "purse", false);
	EXPECT_EQ(p.getLabel(), p_ref.getLabel());
	EXPECT_EQ(p.getX(), p_ref.getX());
	EXPECT_EQ(p.getY(), p_ref.getY());
	EXPECT_EQ(p.getCategory(), p_ref.getCategory());
	EXPECT_FALSE(p.getLock());
}

TEST(TestReadXML, TestDoor) {
	std::string s = R"(<?xml version = "1.0"?>
			<Door label="test" x="0" y="1" category="purse" room="2"/>)";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(s.c_str());
	ASSERT_TRUE(result) << result.description();
	Door d{ doc.child("Door") };
	auto d_ref = Door(0, 1, "test", "purse", 2);
	EXPECT_EQ(d.getLabel(), d_ref.getLabel());
	EXPECT_EQ(d.getX(), d_ref.getX());
	EXPECT_EQ(d.getY(), d_ref.getY());
	EXPECT_EQ(d.getCategory(), d_ref.getCategory());
	EXPECT_EQ(d.getRoom(), d_ref.getRoom());
}

TEST(TestMap, TestAddToMap) {
	Assets assets;
	ASSERT_TRUE(assets.getTexturesMap().empty());
	assets.addToMap("purse", "purse");
	ASSERT_FALSE(assets.getTexturesMap().empty());
	ASSERT_EQ(assets.getTexturesMap().find("purse")->first, "purse");
}
