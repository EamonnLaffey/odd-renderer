#pragma once
#include "vec4.h"
#include <iostream>
#include <cmath>
using namespace std;

template <typename T> struct tmat4 {
   tvec4<T> values[4];
   const tvec4<T> &operator[](ptrdiff_t i) const {
      return values[i];
   }
   tvec4<T> &operator[](ptrdiff_t i) {
      return values[i];
   }

   tmat4<T>() {
      T z(0);
      T o(1);
      values[0] = tvec4<T>(o, z, z, z);
      values[1] = tvec4<T>(z, o, z, z);
      values[2] = tvec4<T>(z, z, o, z);
      values[3] = tvec4<T>(z, z, z, o);
   }
   tmat4<T>(T s) {
      T z(0);
      values[0] = tvec4<T>(s, z, z, z);
      values[1] = tvec4<T>(z, s, z, z);
      values[2] = tvec4<T>(z, z, s, z);
      values[3] = tvec4<T>(z, z, z, s);
   }
   tmat4<T>(const tmat4<T> &m) {
      values[0] = m[0];
      values[1] = m[1];
      values[2] = m[2];
      values[3] = m[3];
   }
   tmat4<T> operator*(const tmat4<T> &m2) {
      tmat4<T> &m1 = *this;
      tvec4<T> a0 = m1[0];
      tvec4<T> a1 = m1[1];
      tvec4<T> a2 = m1[2];
      tvec4<T> a3 = m1[3];

      tvec4<T> b0 = m2[0];
      tvec4<T> b1 = m2[1];
      tvec4<T> b2 = m2[2];
      tvec4<T> b3 = m2[3];

      tmat4<T> result;
      result[0] = a0 * b0[0] + a1 * b0[1] + a2 * b0[2] + a3 * b0[3];
      result[1] = a0 * b1[0] + a1 * b1[1] + a2 * b1[2] + a3 * b1[3];
      result[2] = a0 * b2[0] + a1 * b2[1] + a2 * b2[2] + a3 * b2[3];
      result[3] = a0 * b3[0] + a1 * b3[1] + a2 * b3[2] + a3 * b3[3];
      return result;
   }
};

using mat4 = tmat4<float>;