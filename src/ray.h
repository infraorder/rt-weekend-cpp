#ifndef RAY_H
#define RAY_H

#include "vec3.h"

inline double min(double x, double y) { return x < y ? x : y; }

inline double max(double x, double y) { return x < y ? y : x; }

inline point3 max(point3 x, double y) { return {max(x.x(), y), max(x.y(), y), max(x.z(), y)}; }

inline double sdSphere(point3 rayPos, double radius) {
    return rayPos.length() - radius;
}

inline double sdBox(point3 rayPos, point3 boxDim) {
    vec3 d = rayPos.abs() - boxDim;
    return min(max(d.x(), max(d.y(), d.z())), 0.0) + max(d, 0.0).length();
}

class ray {
public:
    ray() {}

    ray(const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}

    const point3 &origin() const { return orig; }

    const vec3 &direction() const { return dir; }

    point3 at(double t) const {
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};


#endif