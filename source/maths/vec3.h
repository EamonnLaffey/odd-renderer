#pragma once
#include <iostream>
#include <cmath>
using namespace std;

template <typename T> struct tvec3 {
   T x;
   T y;
   T z;
   tvec3(T x, T y, T z) {
      this->x = x;
      this->y = y;
      this->z = z;
   }
   tvec3(T s) {
      x = s;
      y = s;
      z = s;
   }
   tvec3(tvec2<T> v) {
      x = v.x;
      y = v.y;
      z = T(0);
   }
   T &operator[](ptrdiff_t i) {
      if (i == 0) return x;
      if (i == 1) return y;
      if (i == 2) return z;
      exit(1);
   }
   const T &operator[](ptrdiff_t i) const {
      if (i == 0) return x;
      if (i == 1) return y;
      if (i == 2) return z;
      exit(1);
   }

   tvec3<T> operator*(const T &s) {
      return tvec3<T>(x * s, y * s, z * s);
   }
   tvec3<T> operator-() {
      return tvec3<T>(-x, -y, -z);
   }
};

template <typename T> tvec3<T> operator*(const T &s, const tvec3<T> &v) {
   return tvec3<T>(s * v.x, s * v.y, s * v.z);
}
template <typename T> tvec3<T> normalize(const tvec3<T> v) {
   T sq = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
   if (sq == T(0)) return tvec3<T>(sq);
   return (1 / sq) * v;
}
template <typename T> T dot(const tvec3<T> v1, const tvec3<T> v2) {
   return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template <typename T> tvec3<T> cross(tvec3<T> v1, tvec3<T> v2) {
   return tvec3<T>(v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v2.z * v1.x, v1.x * v2.y - v2.x * v1.y);
}
using vec3 = tvec3<float>;
