// The main function was modified so that it writes the update quality for each day in the file "out_refactored.txt"
// This data can be then compared to "stdout.gr" data representing golden master
// If the functionality of the function is the same only the Conjured Item values should differ

// One can write a small test comparing new "out_refactored.txt" and old "stdout.gr"


#include "GildedRose.h"

#include <iostream>
#include <fstream>


using namespace std;

ostream& operator<<(ostream& s, ItemWrap* item)
{
    s << item->get_name() << ", " << item->get_selIn() << ", " << item->get_quality();
    return s;
}


int main()
{
	ofstream f;
	f.open("out_refactored.txt");

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

    f << "OMGHAI!" << endl;

    for (int day = 0; day <= 30; day++)
    {
        f << "-------- day " << day << " --------" << endl;
        f << "name, sellIn, quality" << endl;
        for (vector<ItemWrap*>::iterator i = items.begin(); i != items.end(); i++)
        {
            f << *i << endl;
        }
        f << endl;

        app.updateQuality();
    }
}
