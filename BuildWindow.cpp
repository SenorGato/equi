#include <X11/Xlib.h>
#include "BuildWindow.h"

BuildWindow::BuildWindow(Window w, std::string pathToImage, std::pair<int, int> cornerCords, std::pair<int, int> seperatorCords) {
    parent = w;
    path = pathToImage;
    corner = cornerCords;
    seperator = seperatorCords;
    Display *dpy = XOpenDisplay(NULL);
}

