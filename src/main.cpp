#include "core/defines.h"
#include "raytracing.h"

#include "ray/camera.h"

#include "object/object.h"
#include "object/objectList.h"
#include "object/sphere.h"

int main()
{
    //_________ WORLD _________
    ObjectList world;
    world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    Camera cam;
    cam.aspect = 16.0 / 9.0;
    cam.width = 800;

    cam.Render(world);
}