#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>

// SDFS todo
//vec3 opU(vec3 d1, vec3 d2) {
//    if (d1.x() < d2.x())
//        return d1;
//    else
//        return d2;
//}
//
//
//vec3 map(point3 pos) {
//    vec3 res = vec3(pos.y(), 0.0, 0.0);
//
//    res = opU(res, vec3(sdSphere(pos - vec3(0.0, 0.0, -1.0), 0.25), 0.0, 0.0));
//
//    return res;
//}
//
//inline vec3 normalize(const vec3 &v) {
//    return v / v.length();
//}
//
//inline double clamp(double in) {
//
//    return std::max(0.0, std::min(in, 1.0));
//}
//
//inline vec3 clamp(vec3 in) {
//
//    return {clamp(in.x()), clamp(in.y()), clamp(in.z())};
//}
//
//vec3 calcNormal(vec3 pos) {
//
//    const float h = 0.01;      // replace by an appropriate value
//
//    vec3 n = vec3(0, 0, 0);
//
//    for (int i = 0; i < 4; i++) {
//        vec3 e = 0.5773 * (2.0 * vec3((((i + 3) >> 1) & 1), ((i >> 1) & 1), (i & 1)) - 1.0);
//        n += e * map(pos + e * h).x();
//    }
//
//    return clamp(vec3(normalize(n).x(), 0.0, 0.0));
//}
//
//color rayColor(const ray &r) {
//
//    return calcNormal(r.direction());
//}

double hit_sphere(const point3 &center, double radius, const ray &r) {
    // center of sphere from the rays origin (i.e pixel in cam)
    vec3 oc = center - r.origin();
    // dot product of the ray's direction.
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - sqrt(discriminant)) / a;
    }
}

color ray_color(const ray &r) {
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    auto focal_length = 1.0;
    auto viewport_height = 2.0;

    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // u - 0-1 width, v - 0-1 height
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // space between pixels
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";

    return 0;
}
