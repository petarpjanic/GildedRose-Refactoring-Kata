// CPP FILE DICRIBING DESCRIBING THE FUNCTIONS FOR THE CLASSSES: Item, ItemWrap, Sulfuras, BS_Pass, AgedBrie, Conjured and GildedRose

#include <algorithm>
#include "GildedRose.h"

GildedRose::GildedRose(vector<ItemWrap*> & items) : items(items)
{}
 
// FOR REGULAR ITEMS
ItemWrap::ItemWrap(string name, int sellIn, int quality, int minQVal, int maxQVal)
{	
	_minQVal = minQVal;
	_maxQVal = maxQVal;

	auto qual_caped = min(quality, _maxQVal);
	qual_caped = max(qual_caped, _minQVal); //capped quallity value between minQVal and maxQVal

	it = new Item(name, sellIn, qual_caped); // create new item
}

ItemWrap::~ItemWrap()
{
	delete it;
}

//return name of item
string ItemWrap::get_name()
{
	return it->name;
}

//return quality value of item
int ItemWrap::get_quality()
{
	return it->quality;
}

//return sellIn value of item
int ItemWrap::get_selIn()
{
	return it->sellIn;
}

//set sellIn modifier value
void ItemWrap::setSellInMod(int value)
{
	_selInValMod = value;
}

//set quallity modifier value
void ItemWrap::setQualityMod(int value)
{
	_qualValMod = value;
}

//set max Quality value
void ItemWrap::setMaxQuality(int value)
{
	_maxQVal = value;
}

//set min Quality value
void ItemWrap::setMinQuality(int value)
{
	_minQVal = value;
}


// Update Quality value of the Item
void ItemWrap::updateQuallity()
{
	// Update Quality
	it->quality += _qualValMod;

	if (it->quality < _minQVal)  //  UNIVERSAL RULE: quality is not less then _minQVal
		it->quality = _minQVal;

	if (it->quality > _maxQVal)  //  UNIVERSAL RULE: quality is not more then _maxQVal
		it->quality = _maxQVal;
}

// Update SellIn value of the Item
void ItemWrap::updateSellIn()
{
	it->sellIn += _selInValMod;
}

// Rulles for quality chagnge for non-specilized Items
void ItemWrap::rullesForQualityVal() 
{
	if (get_selIn() >= 0)
		setQualityMod(-1); // decrease quality by -1
	else
		setQualityMod(-2); // decrease quality by -2
}

// Rulles for sellIn chagnge for non-specilized  Item
void ItemWrap::rullesForSellInVal() 
{
	setSellInMod(-1); // decrease sellIn by -1
}




// RULLES FORS SPECIALIZED ITEMS

// Sulfuras constructors
Sulfuras::Sulfuras(string name, int sellIn) : ItemWrap(name, sellIn, 80, 80, 80)
{}
Sulfuras::Sulfuras(string name, int sellIn, int quality) : ItemWrap(name, sellIn, quality, 80, 80)
{}

// Rules for Sulfuras item
void Sulfuras::rullesForQualityVal()
{
	// The value is not changed
	setQualityMod(0);
}
void Sulfuras::rullesForSellInVal()
{
	// The value is not changed
	setSellInMod(0);
}

//AgedBrie Constructor
AgedBrie::AgedBrie(string name, int sellIn, int quality) : ItemWrap(name, sellIn, quality)
{}
// Rules for AgedBrie item
void AgedBrie::rullesForQualityVal()
{
	if (get_selIn() >= 0)
		setQualityMod(1); // increases quality by 1
	else
		setQualityMod(2); // increases quality by 2
}


//BS_Pass constructor
BS_Pass::BS_Pass(string name, int sellIn, int quality) : ItemWrap(name, sellIn, quality)
{}
// Rules for BS_Pass item
void BS_Pass::rullesForQualityVal()
{
	if (get_selIn() >= 10)
		setQualityMod(1); // If more then 10 days to the concert increase quality by 1
	else if (get_selIn() >= 5)
		setQualityMod(2); //  If more then 5 days to the concert increase quality by 2
	else if (get_selIn() >= 0)
		setQualityMod(3); // If less then 5 days to the concert increase quality by 3
	else
		setQualityMod(-get_quality()); // after concert quality is 0, it will never go below 0
}

//Conjured consructor
Conjured::Conjured(string name, int sellIn, int quality) : ItemWrap(name, sellIn, quality)
{}
// Rules for Conjured item
void Conjured::rullesForQualityVal()
{
	// Conjured Items decrease in quality twice as fast
	if (get_selIn() >= 0)
		setQualityMod(-2); // decrease quality by -2
	else
		setQualityMod(-4); // decrease quality by -4
}


void GildedRose::updateQuality()
{
	for (auto &it : items)
	{
		// To preserve the original fuctionallity of the function first we update the sellIn then we update the Quallity

		it->rullesForSellInVal(); // update value modifier for SellIn based on the specific rule for the item
		it->updateSellIn(); // update SellIn values for the item

		it->rullesForQualityVal(); // update value modifier for Quality based on the specific rule for the item
		it->updateQuallity(); // update Quality values for the item
	}
}