#pragma once

#include "object.h"
#include "../math/vector.h"

class Sphere : public Object
{
    private:
    Point3 center;
    f64 radius;

    // clang-format off
    public:
    Sphere(const Point3 &center, f64 radius)
        :center{center}, radius{std::fmax(0, radius)} {}
    // clang-format on

    bool Hit(const Ray &r, Interval rayT, HitRecord &rec) const override
    {
        Vector3 oc = center - r.GetOrigin();

        auto a = r.GetDirection().mag_squared();
        auto h = dot(r.GetDirection(), oc);
        auto c = oc.mag_squared() - radius * radius;

        auto discriminant = h * h - a * c;

        // return if there are intersection points
        if(discriminant < 0)
            return false;

        auto sqrtD = std::sqrt(discriminant);

        // find the nearest root
        auto root = (h - sqrtD) / a;
        if(!rayT.surrounds(root))
        {
            root = (h + sqrtD) / a;
            if(!rayT.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.pos = r.at(rec.t);
        Vector3 outNormal = (rec.pos - center) / radius;
        rec.SetFaceNormal(r, outNormal);

        return true;
    }
};