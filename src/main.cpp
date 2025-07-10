#include "tool_window/tool_window.h"

#pragma comment(lib, "dwmapi.lib")

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
    /* Set DPI awareness */
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    HRESULT hr = CreateToolWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    if (FAILED(hr))
    {
        // TODO: handle error
        OutputDebugString(L"CreateToolWindow failed\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
