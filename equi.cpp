#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

#include "BuildWindow.h"

Window window_from_name_search(Display *display, Window current, char const *query) {
  Window retval, root, parent, *children;
  unsigned children_count;
  char *name = NULL;
  /* Check if this window has the name we seek */
  if(XFetchName(display, current, &name) > 0) {
    int r = strcmp(query, name);
    XFree(name);
    if(r == 0) {
      return current;
    }
  }

  retval = 0;

  /* If it does not: check all subwindows recursively. */
  if(0 != XQueryTree(display, current, &root, &parent, &children, &children_count)) {
    for(unsigned i = 0; i < children_count; ++i) {
      Window win = window_from_name_search(display, children[i], query);

      if(win != 0) {
        retval = win;
        break;
      }
    }

    XFree(children);
  }

  return retval;
}

int main(){
    Window mainWin;
    char const* name = "EverQuest";
    Display *display = XOpenDisplay(NULL);
    //Color defintions

    XColor color;
    Colormap colormap;
    char green[] = "#00FF00";
    int blackColor = BlackPixel(display, DefaultScreen(display));
    int whiteColor = WhitePixel(display, DefaultScreen(display));
    colormap = DefaultColormap(display, 0);
    XParseColor(display, colormap, green, &color);
    XAllocColor(display, colormap, &color);
    //Window Init
    
    system("./wine.sh &");
    sleep(10);
    Window w = window_from_name_search(display, XDefaultRootWindow(display), name);
    mainWin = XCreateSimpleWindow(display,DefaultRootWindow(display),0,0,1920,1080,0,blackColor, whiteColor);
    XSelectInput(display, mainWin, StructureNotifyMask);
    XMapWindow(display,mainWin);
    XReparentWindow(display,w,mainWin,320,160);
    for(;;) {
        XEvent e;
        XNextEvent(display, &e);
        if (e.type == MapNotify)
            break;
    }
    BuildWindow(mainWin, "/home/senoraraton/bins/equi/assets/border.jpg", {0,0}, {0,0});



    std::cin.get();

    XCloseDisplay(display);
    }
