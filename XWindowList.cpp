#include "XWindowList.h"

Map::Map(int w, int h, int tWidth, int tHeight) {
        width = w;
        height = h;
        tileWidth = tWidth;
        tileHeight = tHeight;
        init();        
}

std::vector<Tile> Map::init(){
       int numXTiles, numYTiles;
       numXTiles = width / tileWidth;
       numYTiles = height / tileHeight;
       for(int i = 0; i< numXTiles; i++) {
               for(int p = 0; p< numYTiles; p++) {
                        grid.push_back (Tile());
               }
       }
       return grid;
}
