#pragma once
#include <iostream>
#include <cmath>
using namespace std;

template <typename T> struct tvec2 {
   union {
      T x;
      T w;
   };
   union {
      T y;
      T h;
   };

   tvec2(const T x, const T y) {
      this->x = x;
      this->y = y;
   }
   template <typename N> tvec2(tvec2<N> v) {
      this->x = v.x;
      this->y = v.y;
   }
   tvec2(T s) {
      x = s;
      y = s;
   }
   tvec2() {}

   T &operator[](ptrdiff_t i) {
      if (i == 0) return x;
      if (i == 1) return y;
      cout << "Index: " << i << " out of bounds" << endl;
      exit(1);
   }
   const T &operator[](ptrdiff_t i) const {
      if (i == 0) return x;
      if (i == 1) return y;
      cout << "Index: " << i << " out of bounds" << endl;
      exit(1);
   }

   bool operator<(const tvec2<T> &v) {
      return x < v.x && y < v.y;
   }
   bool operator>(const tvec2<T> &v) {
      return x > v.x && y > v.y;
   }
   bool operator<=(const tvec2<T> &v) {
      return x <= v.x && y <= v.y;
   }
   bool operator>=(const tvec2<T> &v) {
      return x >= v.x && y >= v.y;
   }
   bool operator==(const tvec2<T> &v) {
      return (x == v.x && y == v.y);
   }
   bool operator!=(const tvec2<T> &v) {
      return (x != v.x && y != v.y);
   }

   tvec2<T> operator+(const tvec2<T> &v) {
      return tvec2<T>(x + v.x, y + v.y);
   }
   tvec2<T> operator-(const tvec2<T> &v) {
      return tvec2<T>(x - v.x, y - v.y);
   }
   tvec2<T> operator*(const tvec2<T> &v) {
      return tvec2<T>(x * v.x, y * v.y);
   }
   tvec2<T> operator/(const tvec2<T> &v) {
      return tvec2<T>(x / v.x, y / v.y);
   }

   tvec2<T> operator+(const T &s) {
      return tvec2<T>(x + s, y + s);
   }
   tvec2<T> operator-(const T &s) {
      return tvec2<T>(x - s, y - s);
   }
   tvec2<T> operator*(const T &s) {
      return tvec2<T>(x * s, y * s);
   }
   tvec2<T> operator/(const T &s) {
      return tvec2<T>(x / s, y / s);
   }

   tvec2<T> &operator=(const tvec2<T> &v) {
      x = v.x;
      y = v.y;
      return *this;
   }
   tvec2<T> &operator=(const T &s) {
      x = s;
      y = s;
      return *this;
   }
   tvec2<T> &operator+=(const tvec2<T> &v) {
      *this = *this + v;
      return *this;
   }
   tvec2<T> &operator-=(const tvec2<T> &v) {
      *this = *this - v;
      return *this;
   }
   tvec2<T> &operator/=(const tvec2<T> &v) {
      *this = *this / v;
      return *this;
   }
   tvec2<T> &operator*=(const tvec2<T> &v) {
      *this = *this * v;
      return *this;
   }
   tvec2<T> &operator+=(const T &s) {
      *this = *this + s;
      return *this;
   }
   tvec2<T> &operator-=(const T &s) {
      *this = *this - s;
      return *this;
   }
   tvec2<T> &operator/=(const T &s) {
      *this = *this / s;
      return *this;
   }
   tvec2<T> &operator*=(const T &s) {
      *this = *this * s;
      return *this;
   }
   tvec2<T> &operator++() {
      return *this += T(1);
   }
   tvec2<T> &operator++(int) {
      return *this += T(1);
   }
   tvec2<T> &operator--() {
      return *this -= T(1);
   }
   tvec2<T> &operator--(int) {
      return *this -= T(1);
   }
   tvec2<T> operator-() {
      return tvec2<T>(-x, -y);
   }
};

template <typename T> tvec2<T> operator+(const T &s, const tvec2<T> &v) {
   return tvec2<T>(s + v.x, s + v.y);
}
template <typename T> tvec2<T> operator-(const T &s, const tvec2<T> &v) {
   return tvec2<T>(s - v.x, s - v.y);
}
template <typename T> tvec2<T> operator/(const T &s, const tvec2<T> &v) {
   return tvec2<T>(s / v.x, s / v.y);
}
template <typename T> tvec2<T> operator*(const T &s, const tvec2<T> &v) {
   return tvec2<T>(s * v.x, s * v.y);
}
template <typename T> ostream &operator<<(ostream &os, const tvec2<T> &v) {
   return os << "x: " << v.x << "    y: " << v.y;
}
template <typename T> T distance(tvec2<T> v1, tvec2<T> v2) {
   tvec2<T> diff = v1 - v2;
   return sqrt(diff.x * diff.x + diff.y * diff.y);
}
template <typename T> tvec2<T> normalize(const tvec2<T> v) {
   T sq = sqrt(v.x * v.x + v.y * v.y);
   if (sq == T(0)) return tvec2<T>(sq);
   return (1 / sq) * v;
}
template <typename T> string to_string(const tvec2<T> v) {
   return string("x: " + to_string(v.x) + "    y: " + to_string(v.y));
}
template <typename T> T dot(const tvec2<T> v1, const tvec2<T> v2) {
   return v1.x * v2.x + v1.y * v2.y;
}

using vec2 = tvec2<float>;
using dvec2 = tvec2<double>;
using ivec2 = tvec2<int>;
