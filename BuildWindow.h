#ifndef BuildWindow_H 
#define BuildWindow_H
#endif

#include <iostream>
#include <X11/Xlib.h>

class BuildWindow {

    public:
    Window parent;
    std::string path;
    std::pair<int,int> corner;
    std::pair<int,int> seperator;
    BuildWindow (Window parent, std::string pathToImage, std::pair<int, int> cornerCords, std::pair<int, int> seperatorCords);
};
