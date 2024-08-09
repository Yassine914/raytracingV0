#include "../core/defines.h"
#include "../raytracing.h"

#include "../object/object.h"

class Camera
{
    private:
    i32 height;
    Point3 center;
    Point3 px100Loc;
    Vector3 pxDeltaU;
    Vector3 pxDeltaV;

    public:
    f64 aspect = 16.0 / 9.0;
    i32 width = 800;

    private:
    void Initialize()
    {
        i32 height = width / aspect;
        height = (height < 1) ? 1 : height;

        f64 focalLength = 1.0;
        f64 viewportHeight = 2.0;
        f64 viewportWidth = viewportHeight * (f64(width) / height);

        // x and y for the camera
        Vector3 viewportU(viewportWidth, 0, 0);
        Vector3 viewportV(0, -viewportHeight, 0);

        // calc horizontal and vertical delta (dist btwn pixels)
        auto pxDeltaU = viewportU / width;
        auto pxDeltaV = viewportV / height;

        // calc loc of upper left pixel
        auto viewportUpperLeft = center - Vector3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
        auto px100Loc = viewportUpperLeft + 0.5 * (pxDeltaU + pxDeltaV);
    }

    Pixel RayColor(const Ray &r, const Object &world) const
    {
        HitRecord rec;
        if(world.Hit(r, Interval(0, infinity), rec))
            return 0.5 * (rec.normal + Pixel(1, 1, 1));

        Vector3 unitDir = UnitVector(r.GetDirection());
        auto a = 0.5 * (unitDir.y() + 1.0);
        return (1.0 - a) * Pixel(1.0, 1.0, 1.0) + a * Pixel(0.5, 0.7, 1.0);
    }

    public:
    void Render(const Object &world)
    {
        std::cout << "P3\n" << width << ' ' << height << "\n255\n";

        for(i32 i = 0; i < height; i++)
        {
            std::clog << "\rscanlines remaining: " << (height - i) << ' ' << std::flush;
            for(i32 j = 0; j < width; j++)
            {
                auto pxCenter = px100Loc + (j * pxDeltaU) + (i * pxDeltaV);
                auto rayDir = pxCenter - center;

                Ray r(center, rayDir);

                Pixel px = RayColor(r, world);
                WritePixel(std::cout, px);
            }
        }

        std::clog << "\rdone.\n";
    }
};