// HEADER FILE DICRIBING THE CLASSSES: Item, ItemWrap, Sulfuras, BS_Pass, AgedBrie, Conjured and GildedRose

// Item	class is the basic class describing the item in the store
// ItemWrap	class is the wrapper adding functionallites to the Item class
// Sulfuras, BS_Pass, AgedBrie, Conjured  classes decribe the new rulles for specilised items
// GildedRose is the class handeling all the items in the store

#include <string>
#include <vector>

using namespace std;


// Item class defining the properties for each item in the store
class Item
{
public:
    string name;
    int sellIn;
    int quality;
    Item(string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) 
    {}
};

// Wraper class addding basic functionality for the items in the store 
class ItemWrap
{
public:
	ItemWrap(string name, int sellIn, int quality, int minQVal = 0, int maxQVal =50);
	
	virtual ~ItemWrap();

	//Return Values from the Item class
	int get_quality(); //quallity
	int get_selIn();   //sellIn
	string get_name(); //quallity

	// Set Values in the Item class
	void setQualityMod(int value); //set quality modifier
	void setSellInMod(int value);  //set sellIn modifier
	void setMaxQuality(int value); //set max qualtiy
	void setMinQuality(int value); //set min quality


	// define Quality modification rules based on sellIn value - can be defined in inherited classes
	virtual void rullesForQualityVal();

	// define SellIn modification rules - can be defined in inherited classes
	virtual void rullesForSellInVal();

	// updates quallity and SellIn values for the Item - based on the modification values
	void updateQuallity();
	void updateSellIn();

private:
	Item *it;  // Item
	int _qualValMod; // Quality modifier
	int _selInValMod;// SellIn modifier
	int _minQVal;	 // min Quality Value
	int _maxQVal;	 // max Quality Value 
};


// Classes for specialized items - they have there own rules for modifing SellIn and Quality 
// Sulfuras Item
class Sulfuras : public ItemWrap
{
public:
	Sulfuras(string name, int sellIn);
	Sulfuras(string name, int sellIn, int quality);
	// changes both sellIn and quallity
	 void rullesForQualityVal()  override;

	void rullesForSellInVal() override;
};

// AgedBrie Item
class AgedBrie : public ItemWrap
{
public:
	AgedBrie(string name, int sellIn, int quality);
	// Rules for Brie item
	void rullesForQualityVal();
};

// Back stage pass Item
class BS_Pass : public ItemWrap
{
public:
	BS_Pass(string name, int sellIn, int quality);
	// Rules for BS_Pass item
	void rullesForQualityVal();
};

// Conjured Item - New Item
class Conjured : public ItemWrap
{
public:
	Conjured(string name, int sellIn, int quality);
	// Rules for Brie item
	void rullesForQualityVal();
};

// Gilded Rose class containgn all items
class GildedRose
{
public:
    vector<ItemWrap*> items; // all items
	GildedRose(){}
    GildedRose(vector<ItemWrap*> &items); 
    
    void updateQuality(); // function daily updating quality and sellIn values of all items
};

