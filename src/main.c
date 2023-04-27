
#ifdef __linux__
#include <X11/Xlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
#ifdef _WIN32
    printf("Hello, Windows!\n");
#elif __linux__
    Display *d;
    Window w;
    XEvent e;
    const char *msg = "Hello, World!";
    int s;

    d = XOpenDisplay(NULL);
    if (d == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    while (1)
    {
        XNextEvent(d, &e);
        if (e.type == Expose)
        {
            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(d);
#endif

    return 0;
}

/*
    we want to support all functionality on windows and linux

    create a window
    draw pixels to the window
    draw text to the window
    handle keyboard input
    handle mouse input
    handle window events (resize, close, etc)
    handle window icon
    handle window title
    handle window position
    handle window size
*/