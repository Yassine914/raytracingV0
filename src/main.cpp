#include "core/window.h"
#include "output/image.h"

constexpr i32 winWidth = 720;
constexpr i32 winHeight = 480;

#ifndef RES_PATH
    #define RES_PATH
#endif

int main()
{
    // clang-format off
    Window *window = new Window(
        "Raytracing -- v0.0.1", winWidth,
        winHeight, false, true
    );
    // clang-format on

    window->InitializeWindow();

    Image img;
    img.DrawImage();

    while(!window->WindowShouldClose())
    {
        window->NewFrame();
    }

    delete window;
}