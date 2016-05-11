#pragma once
#include <iostream>
#include <cmath>
#include "vec4.h"
#include "vec3.h"
#include "vec2.h"
#include "mat4.h"
using namespace std;

template <typename T> T to_degrees(T angle) {
   return M_PI * angle / 180;
}

template <typename T> tmat4<T> ortho(const T &left, const T &right, const T &bottom, const T &top) {
   tmat4<T> result(1);
   result[0][0] = T(2) / (right - left);
   result[1][1] = T(2) / (top - bottom);
   result[2][2] = -T(1);
   result[3][0] = -(right + left) / (right - left);
   result[3][1] = -(top + bottom) / (top - bottom);
   return result;
}

template <typename T> tmat4<T> translate(tmat4<T> m, tvec3<T> v) {
   tmat4<T> result = m;
   tvec4<T> tmp1 = m[0] * v[0];
   tvec4<T> tmp2 = m[1] * v[1];
   tvec4<T> tmp3 = m[2] * v[2];
   result[3] = tmp1 + tmp2 + tmp3 + m[3];
   return result;
}

template <typename T> tvec2<T> rotate(const tvec2<T> &v, const T &angle) {
   return tvec2<T>(v.x * cos(angle) - v.y * sin(angle), v.x * sin(angle) + v.y * cos(angle));
}

template <typename T> tmat4<T> rotate(const tmat4<T> &m, const T &angle, const tvec3<T> &v) {
   T a = angle;
   T c = cos(a);
   T s = sin(a);

   tvec3<T> axis = normalize(v);
   tvec3<T> temp = (T(1) - c) * axis;
   tmat4<T> rot;

   rot[0][0] = c + temp[0] * axis[0];
   rot[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
   rot[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

   rot[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
   rot[1][1] = c + temp[1] * axis[1];
   rot[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

   rot[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
   rot[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
   rot[2][2] = c + temp[2] * axis[2];

   tmat4<T> result;

   result[0] = m[0] * rot[0][0] + m[1] * rot[0][1] + m[2] * rot[0][2];
   result[1] = m[0] * rot[1][0] + m[1] * rot[1][1] + m[2] * rot[1][2];
   result[2] = m[0] * rot[2][0] + m[1] * rot[2][1] + m[2] * rot[2][2];
   result[3] = m[3];
   return result;
}

template <typename T> tmat4<T> scale(const tmat4<T> &m, const tvec3<T> &v) {
   tmat4<T> result;
   result[0] = m[0] * v[0];
   result[1] = m[1] * v[1];
   result[2] = m[2] * v[2];
   result[3] = m[3];
   return result;
}