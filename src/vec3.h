#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

inline double sq(double x) { return x * x; }

class vec3 {
public:
    double e[3];

    vec3() : e{0, 0, 0} {}

    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    [[nodiscard]] double x() const { return e[0]; }

    [[nodiscard]] double y() const { return e[1]; }

    [[nodiscard]] double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    double operator[](int i) const { return e[i]; }

    double &operator[](int i) { return e[i]; }

    double abs() { return sqrt(sq(x())), sq(y()), sq(z()); }

    vec3 &operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3 &operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3 &operator/=(double t) {
        return *this *= 1 / t;
    }

    [[nodiscard]] double length() const {
        return sqrt(length_squared());
    }

    [[nodiscard]] double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline vec3 operator*(double t, const vec3 &v) {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t) {
    return (1 / t) * v;
}

inline vec3 operator-(const vec3 &u, const double &v) {
    return {u.e[0] - v, u.e[1] - v, u.e[2] - v};
}

inline vec3 operator-(const double &v, const vec3 &u) {
    return {v - u.e[0],  v - u.e[1], v - u.e[2]};
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return {u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

inline vec3 unit_vector(const vec3 &v) {
    return v / v.length();
}


#endif