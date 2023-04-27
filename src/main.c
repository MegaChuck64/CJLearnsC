#ifdef __linux__

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
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

    return 0;
}



#elif _WIN32

#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "Window Class";
    const char WINDOW_NAME[] = "Sample Window";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        WINDOW_NAME,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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