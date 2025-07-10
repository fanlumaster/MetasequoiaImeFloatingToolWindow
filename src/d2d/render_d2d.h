#pragma once

#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <utility>
#include <wrl.h>
#include <string>
#include <wrl/client.h>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "dxguid")

using namespace Microsoft::WRL;

bool InitD2DAndDWrite();
bool InitD2DRenderTarget(HWND hwnd);
std::pair<float, float> MeasureTextWidth(   //
    ComPtr<IDWriteFactory> &pDWriteFactory, //
    ComPtr<IDWriteTextFormat> &pTextFormat, //
    const std::wstring &text                //
);
int PaintToolMenus(HWND hwnd);