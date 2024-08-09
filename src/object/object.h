#pragma once

#include "../raytracing.h"

struct HitRecord
{
    Point3 pos;
    Vector3 normal;
    f64 t;
    bool frontFace;

    void SetFaceNormal(const Ray &r, const Vector3 &outNormal)
    {
        // sets the normal vector to face the correct way.
        // outNormal must be a unit vector.

        frontFace = dot(r.GetDirection(), outNormal) < 0;
        normal = frontFace ? outNormal : -outNormal;
    }
};

class Object
{
    public:
    virtual bool Hit(const Ray &r, Interval rayT, HitRecord &rec) const = 0;

    virtual ~Object() = default;
};