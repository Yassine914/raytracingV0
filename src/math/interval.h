#pragma once

#include "../core/defines.h"

class Interval
{
    public:
    f64 min, max;
    static const Interval empty, universe;

    public:
    Interval() : min(+infinity), max(-infinity) {}

    Interval(f64 min, f64 max) : min(min), max(max) {}

    f64 size() const { return max - min; }

    bool contains(f64 x) const { return min <= x && x <= max; }

    bool surrounds(f64 x) const { return min < x && x < max; }
};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);