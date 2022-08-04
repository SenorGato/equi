#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

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
    unsigned i;
    for(i = 0; i < children_count; ++i) {
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

// frontend function: open display connection, start searching from the root window.
Window window_from_name(char const *name) {
  Display *display = XOpenDisplay(NULL);
  Window w = window_from_name_search(display, XDefaultRootWindow(display), name);
  XCloseDisplay(display);
  return w;
}

int main(){
    printf("Testing:%d\n", window_from_name("EverQuest"));
    }
