#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif


#ifdef _WIN32

#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

#endif


int main()
{
    #ifdef __linux__

    Display *display;
    Window window;
    XEvent event;
    GC gc;
    XColor red;
    char *text = "Hello World!";
    int s;

    display = XOpenDisplay(NULL);

    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    s = DefaultScreen(display);

    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 200, 200, 1, BlackPixel(display, s), WhitePixel(display, s));

    XSelectInput(display, window, ExposureMask | KeyPressMask);

    gc = XCreateGC(display, window, 0, NULL);

    if (XAllocNamedColor(display, DefaultColormap(display, s), "red", &red, &red) == 0) {
        fprintf(stderr, "Could not allocate color\n");
        exit(1);
    }


    XMapWindow(display, window);

    while (1) {
        XNextEvent(display, &event);

        if (event.type == Expose) {
            XSetForeground(display, gc, BlackPixel(display, s));
            XFillRectangle(display, window, gc, 20, 20, 40, 40);
            XSetForeground(display, gc, red.pixel);
            XDrawString(display, window, gc, 20, 100, text, strlen(text));
        }

        if (event.type == KeyPress) {
            break;
        }
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);


    return 0;

    #endif

    #ifdef _WIN32

    FreeConsole();
    WNDCLASS windowClass={0};
    windowClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass.hCursor=LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance=NULL;
    windowClass.lpfnWndProc=WndProc;
    windowClass.lpszClassName="Window Class";
    if (!RegisterClass(&windowClass))
        MessageBox(NULL, "Could not register class", "Error", MB_OK);
    HWND windowHandle=CreateWindow("Window Class",
                                    "Sample Window",
                                    WS_OVERLAPPEDWINDOW,
                                    20,
                                    20,
                                    400,
                                    200,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL);
    ShowWindow(windowHandle, SW_RESTORE);
    MSG messages;
    while(GetMessage(&messages, NULL, 0, 0)>0)
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    DeleteObject(windowHandle); //doing it just in case
    return messages.wParam;

    #endif
}

#ifdef _WIN32

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
         case WM_CREATE:
            // Force a WM_PAINT message by invalidating the entire client area
            InvalidateRect(hwnd, NULL, TRUE);
        return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            SetTextColor(hdc, RGB(255, 0, 0)); 
            SetBkColor(hdc, RGB(255, 255, 255));
            RECT squareRect = {20, 20, 40, 40};
            RECT textRect = {20,60,100,50};
            DrawText(hdc, "Hello, world!", -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &squareRect, blackBrush);
            DeleteObject(blackBrush);
            EndPaint(hwnd, &ps);
            return 0;
        }
        default: 
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
#endif



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