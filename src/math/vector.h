#pragma once

#include "../core/defines.h"

#include <cmath>
#include <iostream>

class Vector3
{
    public:
    f64 vec[3];

    public:
    //___ CONSTRUCTORS ___
    Vector3() : vec{0, 0, 0} {}
    Vector3(f64 v0, f64 v1, f64 v2) : vec{v0, v1, v2} {}

    //___ GETTERS ___
    double x() const { return vec[0]; }
    double y() const { return vec[1]; }
    double z() const { return vec[2]; }

    inline Vector3 GetNormalised() { return Vector3(vec[0] / mag(), vec[1] / mag(), vec[2] / mag()); }

    //___ OPERATORS ___
    Vector3 operator-() const { return Vector3(-vec[0], -vec[1], -vec[2]); }

    f64 operator[](int i) const { return vec[i]; }
    f64 &operator[](int i) { return vec[i]; }

    Vector3 &operator+=(const Vector3 &v)
    {
        vec[0] += v.vec[0];
        vec[1] += v.vec[1];
        vec[2] += v.vec[2];

        return *this;
    }

    Vector3 &operator*=(f64 t)
    {
        vec[0] *= t;
        vec[1] *= t;
        vec[2] *= t;

        return *this;
    }

    Vector3 &operator/=(f64 t) { return *this *= 1 / t; }

    f64 mag_squared() const { return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]; }

    f64 mag() const { return std::sqrt(mag_squared()); }

    void normalize()
    {
        f64 magnitude = mag();

        vec[0] /= magnitude;
        vec[1] /= magnitude;
        vec[2] /= magnitude;
    }
};

// NOTE: point alias for differentiation.
using Point3 = Vector3;

//___ VECTOR UTILS ___

inline std::ostream &operator<<(std::ostream &out, const Vector3 &v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vector3 operator+(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vector3 operator-(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vector3 operator*(const Vector3 &u, const Vector3 &v)
{
    return Vector3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vector3 operator*(f64 t, const Vector3 &v)
{
    return Vector3(t * v.x(), t * v.y(), t * v.z());
}

inline Vector3 operator*(const Vector3 &v, f64 t)
{
    return t * v;
}

inline Vector3 operator/(const Vector3 &v, f64 t)
{
    return (1 / t) * v;
}

// clang-format off
inline f64 dot(const Vector3 &u, const Vector3 &v)
{
    return u.x() * v.x()
        +  u.y() * v.y()
        +  u.z() * v.z();
}

inline Vector3 cross(const Vector3 &u, const Vector3 &v)
{
    return Vector3(
        u.y() * v.z() - u.z() * v.y(),
        u.z() * v.x() - u.x() * v.z(),
        u.x() * v.y() - u.y() * v.x()
    );
}
// clang-format on

inline Vector3 UnitVector(const Vector3 &v)
{
    return v / v.mag();
}