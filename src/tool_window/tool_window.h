#include <Windows.h>
#include <stdint.h>

/* Window size in DIP, for D2D */
inline uint32_t wnd_width_dip = 216;
inline uint32_t wnd_height_dip = 36;
/* Window size in pixels */
inline uint32_t wnd_width = wnd_width_dip * 1.5;
inline uint32_t wnd_height = wnd_height_dip * 1.5;

HRESULT CreateToolWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow);
