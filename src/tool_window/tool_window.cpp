#include "tool_window.h"
#include <stdint.h>
#include <dwmapi.h>
#include <winnt.h>

#pragma comment(lib, "dwmapi.lib")

HWND g_hwnd = NULL;
uint32_t wnd_width = 326;
uint32_t wnd_height = 56;

static const wchar_t *windowClassName = L"metaseuqoiaimefloatingtoolwindowclass";
static const wchar_t *windowTitle = L"Metaseuqoiaimefloatingtoolwindow";

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

HRESULT CreateToolWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
    //
    // Register window class
    //
    WNDCLASSEX windowClass = {};
    windowClass.cbSize = sizeof(WNDCLASSEXW);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = &WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(hInstance, NULL);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = NULL;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = windowClassName;
    windowClass.hIconSm = LoadIcon(hInstance, NULL);
    static ATOM hr = RegisterClassEx(&windowClass);
    if (hr == 0)
    {
        // TODO: handle error
        OutputDebugString(L"RegisterClassEx failed\n");
        return S_FALSE;
    }

    //
    // Create window
    //
    DWORD dwExStyle = WS_EX_TOPMOST;
    DWORD style = WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
    style = WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
    g_hwnd = CreateWindowEx( //
        dwExStyle,           //
        windowClassName,     //
        windowTitle,         //
        style,               //
        100,                 //
        100,                 //
        wnd_width,           //
        wnd_height,          //
        NULL,                //
        NULL,                //
        hInstance,           //
        nullptr              //
    );
    if (g_hwnd == NULL)
    {
        // TODO: handle error
        OutputDebugString(L"CreateWindowEx failed\n");
        return S_FALSE;
    }

    /* Extend frame into client area */
    static const MARGINS shadow_state[2]{{0, 0, 0, 0}, {1, 1, 1, 1}};
    ::DwmExtendFrameIntoClientArea(g_hwnd, &shadow_state[1]);

    ShowWindow(g_hwnd, SW_SHOW);
    UpdateWindow(g_hwnd);

    return S_OK;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_NCPAINT: {
        return 0;
    }
    case WM_NCACTIVATE:
        return TRUE;
    case WM_NCCALCSIZE:
        return 0;
    case WM_CREATE: {
        break;
    }
    case WM_SIZE: {
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}