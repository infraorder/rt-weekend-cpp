#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

// SDFS todo
// vec3 opU(vec3 d1, vec3 d2) {
//    if (d1.x() < d2.x())
//        return d1;
//    else
//        return d2;
//}
//
//
// vec3 map(point3 pos) {
//    vec3 res = vec3(pos.y(), 0.0, 0.0);
//
//    res = opU(res, vec3(sdSphere(pos - vec3(0.0, 0.0, -1.0), 0.25), 0.0,
//    0.0));
//
//    return res;
//}
//
// inline vec3 normalize(const vec3 &v) {
//    return v / v.length();
//}
//
// inline double clamp(double in) {
//
//    return std::max(0.0, std::min(in, 1.0));
//}
//
// inline vec3 clamp(vec3 in) {
//
//    return {clamp(in.x()), clamp(in.y()), clamp(in.z())};
//}
//
// vec3 calcNormal(vec3 pos) {
//
//    const float h = 0.01;      // replace by an appropriate value
//
//    vec3 n = vec3(0, 0, 0);
//
//    for (int i = 0; i < 4; i++) {
//        vec3 e = 0.5773 * (2.0 * vec3((((i + 3) >> 1) & 1), ((i >> 1) & 1), (i
//        & 1)) - 1.0); n += e * map(pos + e * h).x();
//    }
//
//    return clamp(vec3(normalize(n).x(), 0.0, 0.0));
//}
//
// color rayColor(const ray &r) {
//
//    return calcNormal(r.direction());
//}

double hit_sphere(const point3 &center, double radius, const ray &ray) {

  /*
   * POINT IN A SPHERE
   * To see if a point is within a sphere we can use x² + y² + z² < r²
   * Same for outside of a square x² + y² + z² < r²
   * However when we need to move the location of the sphere around a different
   * origin it gets a little more complex.
   *
   * So we can simplify this, by thinking of the left hand size in terms of the
   * entire vector. if we think of x² + y² + z² in terms of its vector P we can
   * use a dot product:
   * - P⋅P = r²
   * Which makes it easier to do other things on the vec3 like move the spheres
   * origin with:
   * - (C-P)⋅(C-P) = (cx - x)² + (cy - y)² + (cz - z)²
   * - (C-P)⋅(C-P) = r²
   *
   * We now have a way to see if a single point P is within the radius of a
   * circle at center C; However we are casting a ray which is represented as:
   * Q = top right origin of camera
   * d = direction
   * t = index of the ray
   * P(t) = Q + td
   *
   * We want to cast our ray to see if any point t is within the circle with
   * represented as: (𝐂−𝐏(𝑡))⋅(𝐂−𝐏(𝑡)) = 𝑟² We can find this by expanding our
   * P(t) to: (𝐂−(𝐐+𝑡𝐝))⋅(𝐂−(𝐐+𝑡𝐝)) = 𝑟²
   *
   * We need to solve for t so we can separate terms based on whether theres is
   * a t or not. (−𝑡𝐝+(𝐂−𝐐))⋅(−𝑡𝐝+(𝐂−𝐐)) = 𝑟²
   *
   * We can restructure this a little, crude explanation here
   * `claude.ai/chat/a7c716fc-1963-4b6f-a1d1-2a79a3eb4811` Which we now end up
   * with this: `𝑡2𝐝⋅𝐝−2𝑡𝐝⋅(𝐂−𝐐)+(𝐂−𝐐)⋅(𝐂−𝐐)−𝑟²=0`
   *
   * To solve for t we can use a quadratic equation since the only known value
   * close to 𝑡 is 𝑡². Therefore we can solve for a quadratic equation
   * 𝑎𝑥2+𝑏𝑥+𝑐=0 by using the formula:
   * `(−𝑏±√𝑏2−4𝑎𝑐)/√2𝑎`
   * So now we need to input all the known values into a, b and c.
   * a = 𝐝⋅𝐝
   * b = −2𝐝⋅(𝐂−𝐐)
   * c = (𝐂−𝐐)⋅(𝐂−𝐐)−𝑟2
   * Which would look like this in our original equation:
   * With all this we can solve for t.
   *
   * The reason t is quadratic is because there can be multiple contact points
   * for a given ray ie. t = 0 -> ray does not hit the object t = 1 -> ray hit
   * the edge of an object t = 2 -> ray hit the object twice.
   *
   */

  /*
   * Iteration 1
   * //           C        Q
   * auto CminQ = center - ray.origin();
   * auto d = ray.direction();
   * auto r = radius;

   * auto a = dot(d, d);
   * auto b = -2.0 * dot(d, CminQ);
   * auto c = dot(CminQ, CminQ) - (r * r);

   * // this is 𝑏2−4𝑎𝑐 this part of (−𝑏±√𝑏2−4𝑎𝑐)/√2𝑎
   * auto discriminant = b * b - 4 * a * c;

   * if (discriminant < 0) {
   *   return -1.0;
   * } else {
   *   return (-b - sqrt(discriminant)) / (2.0 * a);
   * }
   */

  /*
   * We can simplify this a little.
   * Notcie that b has a factor of -2 in it.
   * Suppose b = -2*h -> h being 𝐝⋅(𝐂−𝐐)
   * -(−2ℎ)±(−2ℎ)2−4𝑎𝑐/√2𝑎
   * which can be simplified to:
   * ℎ±√ℎ2−𝑎𝑐/a
   *
   * Which we can use to for solving h:
   * 𝑏=−2𝐝⋅(𝐂−𝐐)
   * 𝑏=−2ℎ
   * ℎ=𝑏/−2=𝐝⋅(𝐂−𝐐)
   */
  //           C        Q
  auto CminQ = center - ray.origin();
  auto d = ray.direction();
  auto r = radius;

  auto a = dot(d, d);
  auto h = dot(d, CminQ);
  auto c = dot(CminQ, CminQ) - (r * r);

  // this is 𝑏2−4𝑎𝑐 this part of (−𝑏±√𝑏2−4𝑎𝑐)/√2𝑎
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
  auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
              << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto pixel_center =
          pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\rDone.                 \n";

  return 0;
}
