#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

// next handle of clipboard view
HWND hwndNextViewer;
bool clipBoardChanged = false;

// define windows procedure 
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // register clipboard viewer
        hwndNextViewer = SetClipboardViewer(hwnd);
        break;
    
    case WM_DRAWCLIPBOARD:
        // clipboard content changed
        clipBoardChanged = true;
        // send the python application the signal
        break;

    case WM_CHANGECBCHAIN:
        // another clipboard viewer added or removed
        if ((HWND) wParam == hwndNextViewer)
            hwndNextViewer = (HWND) lParam;
        else if (hwndNextViewer != NULL)
            SendMessage(hwndNextViewer, message, wParam, lParam);
        break;

    case WM_DESTROY:
        // unregister clipboard viewer
        ChangeClipboardChain(hwnd, hwndNextViewer);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

int main()
{
    MSG msg;
    WNDCLASS wndClass = {0};
    const wchar_t *className = L"ClipboardViewer";

    // register window class
    wndClass.lpfnWndProc = WindowProcedure;
    wndClass.hInstance = GetModuleHandle(NULL);
    wndClass.lpszClassName = className;

    RegisterClass(&wndClass);

    // hidden window for clipboard viewer
    HWND hwnd = CreateWindowEx(
        0, className, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, NULL, NULL
    );

    if (!hwnd)
    {
        return -1;
    }

    // message loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}