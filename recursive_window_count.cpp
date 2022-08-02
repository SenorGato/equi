#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <chrono>


#define MAX_INDENT 100

unsigned int getWindowCount( Display *display, Window parent_window, int depth )
{
    Window  root_return;
    Window  parent_return;
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
        /*printf( "getWindowCount() - %s    %d window handle returned\n", indent, list_length );*/
        if (XFetchName(display, parent_window, &name) != 0 && *name != '\0') { 
                if (strcmp(name, "EverQuest") == 0) {
                    std::cout << "Display" << display << " Parent_window:" << &parent_window << " Name:" << name << std::endl;
                    //XDestroyWindow(display,parent_window);
                    //proplist = XListProperties(display, parent_window, num_prop_return);
                    //if (&num_prop_return == 0) {
                    //    std::cout << "Props are zero" << std::endl;
                    //} else {
                    //    std::cout << "Props #:" << num_prop_return << std::end;
                    //}
                    //for (int x : proplist) {
                    //    std::cout << "Prop:" << proplist[x] << std::endl;
                    //}
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
                    unsigned int child_length = getWindowCount( display, children_list[i], depth+1 );
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

    return list_length; 
}

int main()
{
    Display *display;
    Window   root_window;
    Window testcase;

    display = XOpenDisplay( NULL );
    if ( display ) 
    {
        // Get the number of screens, it's not always one!
        int screen_count = XScreenCount( display );

        // Each screen has a root window
        printf( "There are %d screens available on this X Display\n", screen_count );
        int blackColor = BlackPixel(display, DefaultScreen(display));
        int whiteColor = WhitePixel(display, DefaultScreen(display));
        XSizeHints my_hints = {0};
        my_hints.flags = PPosition | PSize;
        my_hints.x = 0;
        my_hints.y = 0;
        my_hints.width = 800;
        my_hints.height = 600;

        //XSetWMNormalHints(display, testcase, my_hints);





        testcase = XCreateSimpleWindow(display, DefaultRootWindow(display),0,0,800,600,0, blackColor, blackColor);
        XSelectInput(display, testcase, StructureNotifyMask);
        XMapWindow(display,testcase);
        GC gc = XCreateGC(display, testcase, 0, 0);
        XSetForeground(display, gc, whiteColor);
        for(;;) {
	        XEvent e;
	        XNextEvent(display, &e);
	        if (e.type == MapNotify)
		        break;
        }
       
        std::cin.get();
        for ( int i=0; i < screen_count; i++ )
        {
            root_window = XRootWindow( display, i );
            printf( "Screen %d - %u windows\n", i, getWindowCount( display, root_window, 0 ) );
        }
        
        XCloseDisplay( display );
    }

    return 0;
}
