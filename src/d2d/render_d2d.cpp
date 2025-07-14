#include "render_d2d.h"
#include <debugapi.h>
#include <fmt/xchar.h>

static ComPtr<ID2D1Factory> pD2DFactory;
static ComPtr<ID2D1HwndRenderTarget> pRenderTarget;
static ComPtr<ID2D1SolidColorBrush> pBrush;
static ComPtr<IDWriteFactory> pDWriteFactory;
static ComPtr<IDWriteTextFormat> pTextFormat;

bool InitD2DAndDWrite()
{
    // Direct2D
    HRESULT hr = D2D1CreateFactory(              //
        D2D1_FACTORY_TYPE_SINGLE_THREADED,       //
        IID_PPV_ARGS(pD2DFactory.GetAddressOf()) //
    );
    if (FAILED(hr))
        return false;

    // DirectWrite
    hr = DWriteCreateFactory(                                        //
        DWRITE_FACTORY_TYPE_SHARED,                                  //
        __uuidof(IDWriteFactory),                                    //
        reinterpret_cast<IUnknown **>(pDWriteFactory.GetAddressOf()) //
    );
    if (FAILED(hr))
        return false;

    // TextFormat
    hr = pDWriteFactory->CreateTextFormat( //
        L"Noto Sans SC",                   //
        nullptr,                           //
        DWRITE_FONT_WEIGHT_NORMAL,         //
        DWRITE_FONT_STYLE_NORMAL,          //
        DWRITE_FONT_STRETCH_NORMAL,        //
        20.0f,                             //
        L"zh-cn",                          //
        pTextFormat.GetAddressOf()         //
    );

    pTextFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);

    if (FAILED(hr))
        return false;

    return true;
}

bool InitD2DRenderTarget(HWND hwnd)
{
    if (!pD2DFactory)
        return false;

    RECT rc;
    GetClientRect(hwnd, &rc);

    HRESULT hr = pD2DFactory->CreateHwndRenderTarget(                             //
        D2D1::RenderTargetProperties(                                             //
            D2D1_RENDER_TARGET_TYPE_DEFAULT,                                      //
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED) //
            ),                                                                    //
        D2D1::HwndRenderTargetProperties(                                         //
            hwnd,                                                                 //
            D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top),                  //
            D2D1_PRESENT_OPTIONS_IMMEDIATELY                                      //
            ),                                                                    //
        pRenderTarget.GetAddressOf()                                              //
    );

    if (SUCCEEDED(hr))
    {
        hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), pBrush.GetAddressOf());
    }

    return SUCCEEDED(hr);
}

int PaintToolMenus(HWND hwnd)
{
    if (!pRenderTarget)
        return -1;

    /* Get the size of the render target */
    D2D1_SIZE_F sizeInDIP = pRenderTarget->GetSize();

    float widthInDIP = sizeInDIP.width;
    float heightInDIP = sizeInDIP.height;

    pRenderTarget->BeginDraw();
    pRenderTarget->Clear(D2D1::ColorF(25.0f / 255.0f, 25.0f / 255.0f, 25.0f / 255.0f));

    //
    // Draw a vertical bar(pill)
    //
    pBrush->SetColor(D2D1::ColorF(142.0f / 255.0f, 140.0f / 255.0f, 216.0f / 255.0f, 1.0f));
    float verticalBarWidth = 3.6f;
    float verticalBarHeight = 0.5f * heightInDIP;
    float x = 10.0f;               // Horizontal position do not need to be centered
    float y = 0.25f * heightInDIP; // Centered
    D2D1_ROUNDED_RECT roundedRect = {
        D2D1::RectF(x,                      //
                    y,                      //
                    x + verticalBarWidth,   //
                    y + verticalBarHeight), //
        verticalBarWidth / 2.0f,            //
        verticalBarWidth / 2.0f             //
    };
    pRenderTarget->FillRoundedRectangle(roundedRect, pBrush.Get());

    pBrush->SetColor(D2D1::ColorF(65.0f / 255.0f, 65.0f / 255.0f, 67.0f / 255.0f, 0.9f));
    pRenderTarget->DrawLine(                                //
        D2D1::Point2F(widthInDIP / 9.0f, 0),                //
        D2D1::Point2F(widthInDIP / 9.0f, sizeInDIP.height), //
        pBrush.Get(),                                       //
        1.5f                                                //
    );

    pRenderTarget->EndDraw();
    return 0;
}