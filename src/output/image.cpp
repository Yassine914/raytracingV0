#include "image.h"

#include <iostream>

void Image::DrawImage()
{
    width = height = 256;
    // NOTE: when running => output to a file using "./ray.exe > image.ppm"

    // PPM file header info
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    // pixel data (RGB only)
    // for(std::vector<Pixel> &row : pixels)
    // {
    //     for(Pixel &pixel : row)
    //     {
    //         std::cout << pixel.r << ' ' << pixel.g << ' ' << pixel.b << '\n';
    //     }
    // }

    for(i32 i = 0; i < height; i++)
    {
        std::clog << "\rscanlines remaining: " << (height - i) << ' ' << std::flush;
        for(i32 j = 0; j < width; j++)
        {
            auto r = double(j) / (width - 1);
            auto g = double(i) / (height - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::clog << "\ndone.\n";
}
