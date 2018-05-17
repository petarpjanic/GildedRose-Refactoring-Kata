// HERE WE PREFORM SOME BASIC TESTING OF THE CODE, CHECKING IF THE CODE FOLLOWS THE BASIC RULES THAT ARE SPECIFIED

// FOR IN DEPTH TESTING ONE SHOULD CREATE TEST COMPARING GOLDEN MASTER FILE "stdout.gr" WITH NEW "out_refactored.txt"
// THIS TESTING CAN INSURE THAT TRASITION BETWEEN THE RULLES IS CORRECT

// ADDITIONALLY WE TEST FOR THE INPUT THAT IS NOT IN CORRECT FORMAT: INITIALISING WITH VALUES THAT ARE OUT OF MIN AND MAX QUALLITY



#include <gtest/gtest.h>

#include "GildedRose.h"

//  Struct for Testing - Testing Examples:
struct AppTest : testing::Test
{
	GildedRose* app = new GildedRose();
	void SetUp()
	{
		vector<ItemWrap*> items;
		items.push_back(new ItemWrap("+5 Dexterity Vest", 10, 20));		// Postive sellIn on regular Item
		items.push_back(new ItemWrap("+5 Dexterity Vest", -10, 20));	// Negative sellIn on regular Item
		items.push_back(new AgedBrie("Aged Brie", 2, 0));				// Positive sellIn on Aged Brie
		items.push_back(new AgedBrie("Aged Brie", -2, 0));				// Negative sellIn on Aged Brie
		items.push_back(new Sulfuras("Sulfuras, Hand of Ragnaros", 0, 80));  // Sulfuras should not change
		items.push_back(new BS_Pass("Backstage passes to a TAFKAL80ETC concert", 15, 20)); // Quallity of tickets should increase by 1
		items.push_back(new BS_Pass("Backstage passes to a TAFKAL80ETC concert", 8, 40)); // Quallity of tickets should increase by 2
		items.push_back(new BS_Pass("Backstage passes to a TAFKAL80ETC concert", 3, 40));  // Quallity of tickets should increase by 3
		items.push_back(new BS_Pass("Backstage passes to a TAFKAL80ETC concert", 0, 49)); // Quallity of tickets should by 0
		items.push_back(new AgedBrie("Aged Brie", -2, 50));				// Qualitty of the Item Not Bigger then 50
		items.push_back(new ItemWrap("+5 Dexterity Vest", -2, 0));				// Qualitty of the Item Not Less then 0
		items.push_back(new ItemWrap("+5 Dexterity Vest", -2, -10));				// Initialized Qualitty of the Item Not Less then 0
		items.push_back(new ItemWrap("+5 Dexterity Vest", -2, 60));				// Initialized Qualitty of the Item Not more then 50

		app->items = items;
	}
	void TearDown()
	{
		delete app;
	}
};


// TESTING ALL RULES WITH THE ELEMENTS FROM THE STRUCT AppTest

// Testing Non-Specilized Item SellIn positive
TEST_F(AppTest, Refular_Item_Rulle_SellIn_Positive) {
    app->updateQuality();
    EXPECT_EQ(app->items[0]->get_quality(), 19);
	EXPECT_EQ(app->items[0]->get_selIn(), 9);
}

// Testing Non-Specilized Item SellIn negative
TEST_F(AppTest, Refular_Item_Rulle_SellIn_Negative) {
	app->updateQuality();
	EXPECT_EQ(app->items[1]->get_quality(), 18);
	EXPECT_EQ(app->items[1]->get_selIn(), -11);
}

// Testing Brie Item SellIn positive
TEST_F(AppTest, Brie_Rulle_SellIn_Positive) {
	app->updateQuality();
	EXPECT_EQ(app->items[2]->get_quality(), 1);
	EXPECT_EQ(app->items[2]->get_selIn(), 1);
}

// Testing Brie Item SellIn negative
TEST_F(AppTest, Brie_Rulle_SellIn_Negative) {
	app->updateQuality();
	EXPECT_EQ(app->items[3]->get_quality(), 2);
	EXPECT_EQ(app->items[3]->get_selIn(), -3);
}

// Testing Sulfuras Item SellIn negative
TEST_F(AppTest, Sulfuras_Rulles) {
	app->updateQuality();
	EXPECT_EQ(app->items[4]->get_quality(), 80);
	EXPECT_EQ(app->items[4]->get_selIn(), 0);
}

// Testing Back Stage Ticket Rulle for More Then 10 days to the concert
TEST_F(AppTest, Back_Stag_Ticket_Rulle_MoreThen10) {
	app->updateQuality();
	EXPECT_EQ(app->items[5]->get_quality(), 21);
	EXPECT_EQ(app->items[5]->get_selIn(), 14);
}

// Testing Back Stage Ticket Rulle for More Then 5 days to the concert
TEST_F(AppTest, Back_Stag_Ticket_Rulle_MoreThen5) {
	app->updateQuality();
	EXPECT_EQ(app->items[6]->get_quality(), 42);
	EXPECT_EQ(app->items[6]->get_selIn(), 7);
}

// Testing Back Stage Ticket Rulle for Less Then 5 days to the concert
TEST_F(AppTest, Back_Stag_Ticket_Rulle_MoreThen0) {
	app->updateQuality();
	EXPECT_EQ(app->items[7]->get_quality(), 43);
	EXPECT_EQ(app->items[7]->get_selIn(), 2);
}

// Testing Back Stage Ticket Rulle, after concert quallity shoud be 0
TEST_F(AppTest, Back_Stag_Ticket_Rulle_After_Concert) {
	app->updateQuality();
	EXPECT_EQ(app->items[8]->get_quality(), 0);
	EXPECT_EQ(app->items[8]->get_selIn(), -1);
}

// Testing Max value should not be over 50
TEST_F(AppTest, MaxValue) {
	app->updateQuality();
	EXPECT_EQ(app->items[9]->get_quality(), 50);
	EXPECT_EQ(app->items[9]->get_selIn(), -3);
}

// Testing  Min value should not be below 0
TEST_F(AppTest, MinValue) {
	app->updateQuality();
	EXPECT_EQ(app->items[10]->get_quality(), 0);
	EXPECT_EQ(app->items[10]->get_selIn(), -3);
}

// Testing Init quality value should not be below 0
TEST_F(AppTest, MaxValueInit) {
	EXPECT_EQ(app->items[11]->get_quality(), 0);
}

// Testing  Min value should not be over 50
TEST_F(AppTest, MinValueInit) {
	EXPECT_EQ(app->items[12]->get_quality(), 50);
}



/*
void example()
{
	vector<ItemWrap*> items;
	items.push_back(new ItemWrap("+5 Dexterity Vest", 10, 20));
	items.push_back(new AgedBrie("Aged Brie", 2, 0));
	items.push_back(new ItemWrap("Elixir of the Mongoose", 5, 7));
	items.push_back(new Sulfuras("Sulfuras, Hand of Ragnaros", 0, 80));
	items.push_back(new Sulfuras("Sulfuras, Hand of Ragnaros", -1, 80));
	items.push_back(new BS_Pass("Backstage passes to a TAFKAL80ETC concert", 15, 20));
	items.push_back(new BS_Pass("Backstage passes to a TAFKAL80ETC concert", 10, 49));
	items.push_back(new BS_Pass("Backstage passes to a TAFKAL80ETC concert", 5, 49));
	// this Conjured item doesn't yet work properly
	items.push_back(new Conjured("Conjured Mana Cake", 3, 6));
	GildedRose app(items);

    app.updateQuality();
}*/
