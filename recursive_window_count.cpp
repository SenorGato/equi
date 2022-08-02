#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>
#include <iostream>


#define MAX_INDENT 100

unsigned int getWindowCount( Display *display, Window parent_window, int depth )
{
    Window  root_return;
    Window  parent_return;
    Window *children_list = NULL;
    unsigned int list_length = 0;
    char    indent[MAX_INDENT+1];
    char *name;
    int test;

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
        
        XFetchName(display,parent_window, &name);
        printf( "Window name - %s\n", name);
        std::cout << "XYZ:" << name << std::endl;
        //if (strcmp(*name,"Everquest") == 0) {
        //    printf( "We got a hit\n\n\n");
        //}


            //if ( name == "EverQuest") {
        //    printf( "Window name - %s\n\n\n\n\n\n\n", name);
        //}

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

int main( int argc, char **argv )
{
    Display *display;
    Window   root_window;

    display = XOpenDisplay( NULL );
    if ( display ) 
    {
        // Get the number of screens, it's not always one!
        int screen_count = XScreenCount( display );

        // Each screen has a root window
        printf( "There are %d screens available on this X Display\n", screen_count );

        for ( int i=0; i < screen_count; i++ )
        {
            root_window = XRootWindow( display, i );
            printf( "Screen %d - %u windows\n", i, getWindowCount( display, root_window, 0 ) );
        }
        XCloseDisplay( display );
    }

    return 0;
}
