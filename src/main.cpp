#include "math/pixel.h"
#include "ray/ray.h"
#include "math/vector.h"

#include <iostream>

f64 HitSphere(const Point3 &center, f64 radius, const Ray &r)
{
    // NOTE: equation to get the points of intersection
    // using (-b +- sqrt(b^2 - 4ac)) / 2a
    // (roots of quadratic func eqn)

    Vector3 oc = center - r.GetOrigin();

    auto a = r.GetDirection().mag_squared();
    auto h = dot(r.GetDirection(), oc);
    auto c = oc.mag_squared() - radius * radius;

    auto discriminant = h * h - a * c;

    // return if there are intersection points
    if(discriminant < 0)
        return -1.0;
    else
        return (h - std::sqrt(discriminant)) / a;
}
// clang-format off
Pixel RayColor(const Ray &r)
{
    auto t = HitSphere(Point3(0, 0, -1), 0.5, r);
    if(t > 0.0)
    {
        Vector3 N = UnitVector(r.at(t) - Vector3(0, 0, -1));
        return 0.5 * Pixel(
            N.x() + 1,
            N.y() + 1,
            N.z() + 1
        );
    }

    Vector3 unitDir = UnitVector(r.GetDirection());
    auto a = 0.5 * (unitDir.y() + 1.0);
    return (1.0 - a) * Pixel(1.0, 1.0, 1.0) + a * Pixel(0.5, 0.7, 1.0);
}
// clang-format on

int main()
{
    //_________ IMAGE _________
    constexpr auto aspect = 16.0 / 9.0;

    i32 width = 800;
    i32 height = width / aspect;
    height = (height < 1) ? 1 : height;

    //________ CAMERA _________
    f64 focalLength = 1.0;

    f64 viewportHeight = 2.0;
    f64 viewportWidth = viewportHeight * (f64(width) / height);

    Point3 cameraCenter(0.0, 0.0, 0.0);

    // x and y for the camera
    Vector3 viewportU(viewportWidth, 0, 0);
    Vector3 viewportV(0, -viewportHeight, 0);

    // calc horizontal and vertical delta (dist btwn pixels)
    auto pxDeltaU = viewportU / width;
    auto pxDeltaV = viewportV / height;

    // calc loc of upper left pixel
    auto viewportUpperLeft = cameraCenter - Vector3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    auto px100Loc = viewportUpperLeft + 0.5 * (pxDeltaU + pxDeltaV);

    //_______ RENDER ________
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    // clang-format off
    for(i32 i = 0; i < height; i++)
    {
        std::clog << "\rscanlines remaining: " << (height - i) << ' ' << std::flush;
        for(i32 j = 0; j < width; j++)
        {
            auto pxCenter = px100Loc + (j * pxDeltaU) + (i * pxDeltaV);
            auto rayDir = pxCenter - cameraCenter;

            Ray r(cameraCenter, rayDir);

            Pixel px = RayColor(r);
            WritePixel(std::cout, px);
        }
    }
    // clang-format on

    std::clog << "\ndone.\n";
}