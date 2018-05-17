I have refactorised the code "GildedRose-Refactoring-Kata/cpp/GildedRose.h" and "GildedRose-Refactoring-Kata/cpp/GildedRose.cpp"
by creating the class hierarhy where:

- ItemWrap is the wraper class for the Item class adding some basic functionality
- inherited calass Sulfuras, BS_Pass, AgedBrie, Conjured are used to decribe the new rulles for specilised items

With GildedRoseTextTests.cpp I created "GildedRose-Refactoring-Kata/out_refactored.txt" which I verified with 
"GildedRose-Refactoring-Kata/stdout.gr" in notepade++ compare option.

In GildedRoseUnitTests.cpp I created several basic tests that are used to validate basic rules and wrongly initalised data.
 