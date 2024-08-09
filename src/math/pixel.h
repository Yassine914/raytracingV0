#pragma once

#include "vector.h"
#include <iostream>

using Pixel = Vector3;

// NOTE: translate from [0, 1] to [0, 255]
void WritePixel(std::ostream &out, const Pixel &pixel)
{
    i32 rbyte = int(255.99 * pixel.x());
    i32 gbyte = int(255.99 * pixel.y());
    i32 bbyte = int(255.99 * pixel.z());

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}