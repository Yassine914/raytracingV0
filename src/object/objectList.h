#pragma once

#include "object.h"
#include "../core/defines.h"

class ObjectList : public Object
{
    public:
    std::vector<shared_ptr<Object>> objects;

    public:
    ObjectList() {}
    ObjectList(shared_ptr<Object> obj) { Add(obj); }

    void Clear() { objects.clear(); }

    void Add(shared_ptr<Object> obj) { objects.push_back(obj); }

    bool Hit(const Ray &r, Interval rayT, HitRecord &rec) const override
    {
        HitRecord tempRec;
        bool hitAnything = false;
        auto closestSoFar = rayT.max;

        for(const auto &obj : objects)
        {
            if(obj->Hit(r, Interval(rayT.min, closestSoFar), tempRec))
            {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }
};