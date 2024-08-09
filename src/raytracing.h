#include "core/defines.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

// consts

const f64 infinity = std::numeric_limits<f64>::infinity();
const f64 pi = 3.1415926535897932385;

// utils

inline f64 radians(f64 deg)
{
    return deg * pi / 180.0;
}

// common headers

#include "math/pixel.h"
#include "ray/ray.h"
#include "math/vector.h"
#include "math/interval.h"