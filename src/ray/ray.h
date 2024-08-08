#pragma once

#include "../core/defines.h"
#include "../math/vector.h"

class Ray
{
    private:
    Vector3 origin;
    Vector3 direction;

    public:
    Ray() {}

    Ray(const Vector3 &orig, const Vector3 &dir) : origin{orig}, direction{dir} {}

    //_______ GETTERS ________
    inline const Vector3 &GetOrigin() const { return origin; }
    inline const Vector3 &GetDirection() const { return direction; }

    // get the position of a point on the ray
    inline Vector3 at(f64 t) const { return origin + t * direction; }
};