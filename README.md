# COMP 345, Winter 2020 - New Haven

### Team 4
Jamal Ghamraoui - 40027657    
Manpreet Tahim  - 26592066  
Yaroslav Bilodid  - 40068605  
Thomas Gillard  - 40031490  


### Creating .exe files

To create the executable files, g++ was used.

GBMapsDriver: `g++ GBMapsDriver.cpp GBMaps.cpp -o GBMapsDriver`  
MapLoaderDriver: `g++ MapLoaderDriver.cpp Resources.cpp VGMap.cpp GBMaps.cpp GBMapLoader.cpp VGMapLoader.cpp Score.cpp -o MapLoaderDriver`  
PlayerDriver: `g++ PlayerDriver.cpp GBMaps.cpp Player.cpp Score.cpp VGMap.cpp Resources.cpp -o PlayerDriver`  
ResourcesDriver: `g++ ResourcesDriver.cpp GBMaps.cpp Score.cpp VGMap.cpp -o ResourcesDriver`  
ScoreDriver: `g++ ScoreDriver.cpp Score.cpp GBMaps.cpp VGMap.cpp -o ScoreDriver`  
VGMapDriver: `g++ VGMapDriver.cpp VGMap.cpp -o VGMapDriver.exe`  
