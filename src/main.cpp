#include "core/window.h"

constexpr i32 winWidth = 720;
constexpr i32 winHeight = 480;

int main()
{
    // clang-format off
    Window *window = new Window(
        "Raytracing -- v0.0.1", winWidth,
        winHeight, false, true
    );
    // clang-format on

    window->InitializeWindow();

    while(!window->WindowShouldClose())
    {
        window->NewFrame();
    }

    delete window;
}