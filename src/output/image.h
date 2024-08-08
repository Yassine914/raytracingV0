#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include <vector>

struct Pixel
{
    u16 r;
    u16 g;
    u16 b;
};

class Image
{
    private:
    i32 width;
    i32 height;

    // 2D vector of pixels
    std::vector<std::vector<Pixel>> pixels;

    public:
    Image()
    {
        width = 256;
        height = 256;
    }

    Image(std::vector<std::vector<Pixel>> px) : pixels{px}
    {
        width = pixels.size();
        height = pixels[0].size();
    }

    void DrawImage();

    ~Image() = default;
};