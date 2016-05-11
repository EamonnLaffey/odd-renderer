#pragma once
#include <iostream>
#include <cmath>
using namespace std;

template <typename T> struct tvec4 {
   T x;
   T y;
   T z;
   T w;
   tvec4() {}
   tvec4(T x, T y, T z, T w) {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = w;
   }
   const T &operator[](ptrdiff_t i) const {
      if (i == 0) return x;
      if (i == 1) return y;
      if (i == 2) return z;
      if (i == 3) return w;
      exit(1);
   }
   T &operator[](ptrdiff_t i) {
      if (i == 0) return x;
      if (i == 1) return y;
      if (i == 2) return z;
      if (i == 3) return w;
      exit(1);
   }
   tvec4<T> &operator=(const tvec4<T> &v) {
      x = v.x;
      y = v.y;
      z = v.z;
      w = v.w;
      return *this;
   }
   tvec4<T> operator+(const tvec4<T> &v) {
      return tvec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
   }
   const tvec4<T> operator+(const tvec4<T> &v) const {
      return tvec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
   }

   tvec4<T> operator*(const tvec4<T> &v) {
      return tvec4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
   }
   tvec4<T> operator+(const T &s) {
      return tvec4<T>(x + s, y + s, z + s, w + s);
   }
   tvec4<T> operator*(const T &s) {
      return tvec4<T>(x * s, y * s, z * s, w * s);
   }

   const tvec4<T> operator*(const T &s) const {
      return tvec4<T>(x * s, y * s, z * s, w * s);
   }
};

template <typename T> tvec4<T> operator+(const T &s, const tvec4<T> &v) {
   return tvec4<T>(s + v.x, s + v.y, s + v.z, s + v.w);
}
template <typename T> tvec4<T> operator*(const T &s, const tvec4<T> &v) {
   return tvec4<T>(s * v.x, s * v.y, s * v.z, s * v.w);
}

using vec4 = tvec4<float>;