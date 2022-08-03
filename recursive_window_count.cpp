#include <stdio.h> 
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>
#include <iostream>

#define MAX_INDENT 100

Window getWindowData( Display *display, Window parent_window, int depth, const char* query )
{
    Window  root_return;
    Window  parent_return;
    Window match;
    Window *children_list = NULL;
    unsigned int list_length = 0;
    char    indent[MAX_INDENT+1];
    char *name = nullptr;

    // Make some indentation space, depending on the depth
    memset( indent, '\0', MAX_INDENT+1 );
    for ( int i=0; i<depth*4 && i<MAX_INDENT; i++ )
    {
        indent[i] = ' ';
    }

    // query the window list recursively, until each window reports no sub-windows
    if ( 0 != XQueryTree( display, parent_window, &root_return, &parent_return, &children_list, &list_length ) )
    {
        if (XFetchName(display, parent_window, &name) != 0 && *name != '\0') { 
                if (strcmp(name, query) == 0) {
                    std::cout << "Display" << display << " Parent_window:" << &parent_window << " Name:" << name << std::endl;
                    match = parent_window;
                    std::cout << "Match:" << match << std::endl;
                }; 
        } 


        if ( list_length > 0 && children_list != NULL )
        {
            for ( int i=0; i<list_length; i++)
            {
                // But typically the "top-level" window is not what the user sees, so query any children
                // Only the odd window has child-windows.  XEyes does.
                if ( children_list[i] != 0 )
                {
                    unsigned int child_length = getWindowData( display, children_list[i], depth+1, query );
                }
                else
                {
                    // There's some weirdness with the returned list
                    // We should not have to be doing this at all
                    printf( "%sHuh? child window handle at index #%d (of %d) is zero?\n", indent, i, list_length );
                    break;  
                }
            }
        
            XFree( children_list ); // cleanup
        }
    }
    std::cout << "Match loop:" << match << std::endl;
            return match; 
}

int main()
{
    Display *display;
    Window   root_window;
    Window testcase;
    Window gameclient;
    Window mainclient;
    Window splits;
    Window buffs;
    Window mobs;
    Window statusbar;
    Window notes;
    Window drops;
    XWindowAttributes *winattr;


    display = XOpenDisplay( NULL );
    if ( display ) 
    {
        // Get the number of screens, it's not always one!
        int screen_count = XScreenCount( display );

        // Each screen has a root window
        printf( "There are %d screens available on this X Display\n", screen_count );

        root_window = XRootWindow( display, 0);
        
        //Color defintions
        XColor color;
        Colormap colormap;
        char green[] = "#00FF00";
        int blackColor = BlackPixel(display, DefaultScreen(display));
        int whiteColor = WhitePixel(display, DefaultScreen(display));
        colormap = DefaultColormap(display, 0);
        XParseColor(display, colormap, green, &color);
        XAllocColor(display, colormap, &color);

        testcase = XCreateSimpleWindow(display,DefaultRootWindow(display),0,0,1920,1080,0,blackColor, whiteColor);

        mainclient = XCreateSimpleWindow(display,testcase,320,180,1280,720,0,blackColor, color.pixel);
        gameclient = getWindowData(display,root_window,0, "EverQuest");
        //XGetWindowAttributes(display, gameclient, winattr);
        std::cout << "gameclient:" << gameclient << std::endl;
        
        XSelectInput(display, testcase, StructureNotifyMask);
        XMapWindow(display,testcase);
        
        //XReparentWindow(display,gameclient,mainclient,10,10);
        XMapWindow(display,mainclient);
        
        //XReparentWindow(display,gameclient,mainclient,10,10);
        //splits = XCreateSimpleWindow(display,testcase,0,0,200,200,0,blackColor, color.pixel);
        //XSelectInput(display, splits, StructureNotifyMask);
        //XMapWindow(display, splits);
        //XMapWindow(display, mainclient);
        //splits = XCreateSimpleWindow(display,testcase,1700,0,220,1280,0,blackColor, color.pixel);
        //XSelectInput(display, splits, StructureNotifyMask);
        //XMapWindow(display, splits);
        //XReparentWindow(display, EQ, testcase, x, y)





        for(;;) {
            XEvent e;
            XNextEvent(display, &e);
            if (e.type == MapNotify)
                break;
        }
        std::cin.get();
        
        //XCloseDisplay( display );
    }

    return 0;
}
