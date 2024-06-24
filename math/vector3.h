#ifndef Y0_CCUTIL_MATH_VECTOR3_H
#define Y0_CCUTIL_MATH_VECTOR3_H

#include <cmath>

namespace y0_ccutil {
  template<typename T>
  struct Vector3 {
    public:
      explicit Vector3() {
        Vector3(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
      }

      explicit Vector3(T x_value, T y_value, T z_value)
        : x(x_value), y(y_value), z(z_value)
      {
      }

      T x;
      T y;
      T z;

      static Vector3<float> get_zero_vector() {
        Vector3<float> v(0.0f, 0.0f, 0.0f);
        return v;
      }

      T SquareLength() {
        return x * x + y * y + z * z;
      }

      T Length {
        return std::sqrt(x * x + y * y + z * z);
      }
  };
} // namespace y0_ccutil

#endif
