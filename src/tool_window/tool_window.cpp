#include "tool_window.h"
#include <stdint.h>
#include <dwmapi.h>
#include <winnt.h>
#include <windowsx.h>
#include "d2d/render_d2d.h"
#include "utils/window_utils.h"

#pragma comment(lib, "dwmapi.lib")

HWND g_hwnd = NULL;

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
    static const MARGINS shadow_state[3]{{0, 0, 0, 0}, {1, 1, 1, 1}, {-1, -1, -1, -1}};
    ::DwmExtendFrameIntoClientArea(g_hwnd, &shadow_state[2]);

    BOOL cloak = TRUE;
    DwmSetWindowAttribute(g_hwnd, DWMWA_CLOAK, &cloak, sizeof(cloak));
    ShowWindow(g_hwnd, SW_SHOW);
    UpdateWindow(g_hwnd);
    cloak = FALSE;
    DwmSetWindowAttribute(g_hwnd, DWMWA_CLOAK, &cloak, sizeof(cloak));

    float scale = GetWindowScale(g_hwnd);
    wnd_width = wnd_width_dip * scale;
    wnd_height = wnd_height_dip * scale;
    SetWindowPos(     //
        g_hwnd,       //
        HWND_TOPMOST, //
        100,          //
        100,          //
        wnd_width,    //
        wnd_height,   //
        0             //
    );

    return S_OK;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_NCPAINT:
        return 0;
    case WM_NCACTIVATE:
        return TRUE;
    case WM_NCCALCSIZE:
        return 0;
    case WM_CREATE: {
        if (!InitD2DAndDWrite())
        {
            OutputDebugString(L"InitD2DAndDWrite failed\n");
            return -1;
        }
        if (!InitD2DRenderTarget(hwnd))
        {
            OutputDebugString(L"InitD2DRenderTarget failed\n");
            return -1;
        }
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        PaintToolMenus(hwnd);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_SIZE: {
        break;
    }
    case WM_NCHITTEST: {
        POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
        ScreenToClient(hwnd, &pt);

        RECT rcClient;
        GetClientRect(hwnd, &rcClient);
        int width = rcClient.right;

        if (pt.x < width / 9)
        {
            return HTCAPTION;
        }
        else
        {
            return HTCLIENT;
        }
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