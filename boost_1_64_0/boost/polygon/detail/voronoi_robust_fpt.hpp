// Boost.Polygon library detail/voronoi_robust_fpt.hpp header file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POLYGON_DETAIL_VORONOI_ROBUST_FPT
#define BOOST_POLYGON_DETAIL_VORONOI_ROBUST_FPT

#include <algorithm>
#include <cmath>

// Geometry predicates with floating-point variables usually require
// high-precision predicates to retrieve the correct result.
// Epsilon robust predicates give the result within some epsilon relative
// error, but are a lot faster than high-precision predicates.
// To make algorithm robust and efficient epsilon robust predicates are
// used at the first step. In case of the undefined result high-precision
// arithmetic is used to produce required robustness. This approach
// requires exact computation of epsilon intervals within which epsilon
// robust predicates have undefined value.
// There are two ways to measure an error of floating-point calculations:
// relative error and ULPs (units in the last place).
// Let EPS be machine epsilon, then next inequalities have place:
// 1 EPS <= 1 ULP <= 2 EPS (1), 0.5 ULP <= 1 EPS <= 1 ULP (2).
// ULPs are good for measuring rounding errors and comparing values.
// Relative errors are good for computation of general relative
// error of formulas or expressions. So to calculate epsilon
// interval within which epsilon robust predicates have undefined result
// next schema is used:
//     1) Compute rounding errors of initial variables using ULPs;
//     2) Transform ULPs to epsilons using upper bound of the (1);
//     3) Compute relative error of the formula using epsilon arithmetic;
//     4) Transform epsilon to ULPs using upper bound of the (2);
// In case two values are inside undefined ULP range use high-precision
// arithmetic to produce the correct result, else output the result.
// Look at almost_equal function to see how two floating-point variables
// are checked to fit in the ULP range.
// If A has relative error of r(A) and B has relative error of r(B) then:
//     1) r(A + B) <= max(r(A), r(B)), for A * B >= 0;
//     2) r(A - B) <= B*r(A)+A*r(B)/(A-B), for A * B >= 0;
//     2) r(A * B) <= r(A) + r(B);
//     3) r(A / B) <= r(A) + r(B);
// In addition rounding error should be added, that is always equal to
// 0.5 ULP or at most 1 epsilon. As you might see from the above formulas
// subtraction relative error may be extremely large, that's why
// epsilon robust comparator class is used to store floating point values
// and compute subtraction as the final step of the evaluation.
// For further information about relative errors and ULPs try this link:
// http://docs.sun.com/source/806-3568/ncg_goldberg.html

namespace boost {
namespace polygon {
namespace detail {

template <typename T>
T get_sqrt(const T& that) {
  return (std::sqrt)(that);
}

template <typename T>
bool is_pos(const T& that) {
  return that > 0;
}

template <typename T>
bool is_neg(const T& that) {
  return that < 0;
}

template <typename T>
bool is_zero(const T& that) {
  return that == 0;
}

template <typename _fpt>
class robust_fpt {
 public:
  typedef _fpt floating_point_type;
  typedef _fpt relative_error_type;

  // Rounding error is at most 1 EPS.
  enum {
    ROUNDING_ERROR = 1
  };

  robust_fpt() : fpv_(0.0), re_(0.0) {}
  explicit robust_fpt(floating_point_type fpv) :
      fpv_(fpv), re_(0.0) {}
  robust_fpt(floating_point_type fpv, relative_error_type error) :
      fpv_(fpv), re_(error) {}

  floating_point_type fpv() const { return fpv_; }
  relative_error_type re() const { return re_; }
  relative_error_type ulp() const { return re_; }

  robust_fpt& operator=(const robust_fpt& that) {
    this->fpv_ = that.fpv_;
    this->re_ = that.re_;
    return *this;
  }

  bool has_pos_value() const {
    return is_pos(fpv_);
  }

  bool has_neg_value() const {
    return is_neg(fpv_);
  }

  bool has_zero_value() const {
    return is_zero(fpv_);
  }

  robust_fpt operator-() const {
    return robust_fpt(-fpv_, re_);
  }

  robust_fpt& operator+=(const robust_fpt& that) {
    floating_point_type fpv = this->fpv_ + that.fpv_;
    if ((!is_neg(this->fpv_) && !is_neg(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_pos(that.fpv_))) {
      this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      this->re_ = temp + ROUNDING_ERROR;
    }
    this->fpv_ = fpv;
    return *this;
  }

  robust_fpt& operator-=(const robust_fpt& that) {
    floating_point_type fpv = this->fpv_ - that.fpv_;
    if ((!is_neg(this->fpv_) && !is_pos(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_neg(that.fpv_))) {
       this->re_ = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
         temp = -temp;
      this->re_ = temp + ROUNDING_ERROR;
    }
    this->fpv_ = fpv;
    return *this;
  }

  robust_fpt& operator*=(const robust_fpt& that) {
    this->re_ += that.re_ + ROUNDING_ERROR;
    this->fpv_ *= that.fpv_;
    return *this;
  }

  robust_fpt& operator/=(const robust_fpt& that) {
    this->re_ += that.re_ + ROUNDING_ERROR;
    this->fpv_ /= that.fpv_;
    return *this;
  }

  robust_fpt operator+(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ + that.fpv_;
    relative_error_type re;
    if ((!is_neg(this->fpv_) && !is_neg(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_pos(that.fpv_))) {
      re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ - that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      re = temp + ROUNDING_ERROR;
    }
    return robust_fpt(fpv, re);
  }

  robust_fpt operator-(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ - that.fpv_;
    relative_error_type re;
    if ((!is_neg(this->fpv_) && !is_pos(that.fpv_)) ||
        (!is_pos(this->fpv_) && !is_neg(that.fpv_))) {
      re = (std::max)(this->re_, that.re_) + ROUNDING_ERROR;
    } else {
      floating_point_type temp =
        (this->fpv_ * this->re_ + that.fpv_ * that.re_) / fpv;
      if (is_neg(temp))
        temp = -temp;
      re = temp + ROUNDING_ERROR;
    }
    return robust_fpt(fpv, re);
  }

  robust_fpt operator*(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ * that.fpv_;
    relative_error_type re = this->re_ + that.re_ + ROUNDING_ERROR;
    return robust_fpt(fpv, re);
  }

  robust_fpt operator/(const robust_fpt& that) const {
    floating_point_type fpv = this->fpv_ / that.fpv_;
    relative_error_type re = this->re_ + that.re_ + ROUNDING_ERROR;
    return robust_fpt(fpv, re);
  }

  robust_fpt sqrt() const {
    return robust_fpt(get_sqrt(fpv_),
                      re_ * static_cast<relative_error_type>(0.5) +
                      ROUNDING_ERROR);
  }

 private:
  floating_point_type fpv_;
  relative_error_type re_;
};

template <typename T>
robust_fpt<T> get_sqrt(const robust_fpt<T>& that) {
  return that.sqrt();
}

template <typename T>
bool is_pos(const robust_fpt<T>& that) {
  return that.has_pos_value();
}

template <typename T>
bool is_neg(const robust_fpt<T>& that) {
  return that.has_neg_value();
}

template <typename T>
bool is_zero(const robust_fpt<T>& that) {
  return that.has_zero_value();
}

// robust_dif consists of two not negative values: value1 and value2.
// The resulting expression is equal to the value1 - value2.
// Subtraction of a positive value is equivalent to the addition to value2
// and subtraction of a negative value is equivalent to the addition to
// value1. The structure implicitly avoids difference computation.
template <typename T>
class robust_dif {
 public:
  robust_dif() :
      positive_sum_(0),
      negative_sum_(0) {}

  explicit robust_dif(const T& value) :
      positive_sum_((value > 0)?value:0),
      negative_sum_((value < 0)?-value:0) {}

  robust_dif(const T& pos, const T& neg) :
      positive_sum_(pos),
      negative_sum_(neg) {}

  T dif() const {
    return positive_sum_ - negative_sum_;
  }

  T pos() const {
    return positive_sum_;
  }

  T neg() const {
    return negative_sum_;
  }

  robust_dif<T> operator-() const {
    return robust_dif(negative_sum_, positive_sum_);
  }

  robust_dif<T>& operator+=(const T& val) {
    if (!is_neg(val))
      positive_sum_ += val;
    else
      negative_sum_ -= val;
    return *this;
  }

  robust_dif<T>& operator+=(const robust_dif<T>& that) {
    positive_sum_ += that.positive_sum_;
    negative_sum_ += that.negative_sum_;
    return *this;
  }

  robust_dif<T>& operator-=(const T& val) {
    if (!is_neg(val))
      negative_sum_ += val;
    else
      positive_sum_ -= val;
    return *this;
  }

  robust_dif<T>& operator-=(const robust_dif<T>& that) {
    positive_sum_ += that.negative_sum_;
    negative_sum_ += that.positive_sum_;
    return *this;
  }

  robust_dif<T>& operator*=(const T& val) {
    if (!is_neg(val)) {
      positive_sum_ *= val;
      negative_sum_ *= val;
    } else {
      positive_sum_ *= -val;
      negative_sum_ *= -val;
      swap();
    }
    return *this;
  }

  robust_dif<T>& operator*=(const robust_dif<T>& that) {
    T positive_sum = this->positive_sum_ * that.positive_sum_ +
                     this->negative_sum_ * that.negative_sum_;
    T negative_sum = this->positive_sum_ * that.negative_sum_ +
                     this->negative_sum_ * that.positive_sum_;
    positive_sum_ = positive_sum;
    negative_sum_ = negative_sum;
    return *this;
  }

  robust_dif<T>& operator/=(const T& val) {
    if (!is_neg(val)) {
      positive_sum_ /= val;
      negative_sum_ /= val;
    } else {
      positive_sum_ /= -val;
      negative_sum_ /= -val;
      swap();
    }
    return *this;
  }

 private:
  void swap() {
    (std::swap)(positive_sum_, negative_sum_);
  }

  T positive_sum_;
  T negative_sum_;
};

template<typename T>
robust_dif<T> operator+(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  return robust_dif<T>(lhs.pos() + rhs.pos(), lhs.neg() + rhs.neg());
}

template<typename T>
robust_dif<T> operator+(const robust_dif<T>& lhs, const T& rhs) {
  if (!is_neg(rhs)) {
    return robust_dif<T>(lhs.pos() + rhs, lhs.neg());
  } else {
    return robust_dif<T>(lhs.pos(), lhs.neg() - rhs);
  }
}

template<typename T>
robust_dif<T> operator+(const T& lhs, const robust_dif<T>& rhs) {
  if (!is_neg(lhs)) {
    return robust_dif<T>(lhs + rhs.pos(), rhs.neg());
  } else {
    return robust_dif<T>(rhs.pos(), rhs.neg() - lhs);
  }
}

template<typename T>
robust_dif<T> operator-(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  return robust_dif<T>(lhs.pos() + rhs.neg(), lhs.neg() + rhs.pos());
}

template<typename T>
robust_dif<T> operator-(const robust_dif<T>& lhs, const T& rhs) {
  if (!is_neg(rhs)) {
    return robust_dif<T>(lhs.pos(), lhs.neg() + rhs);
  } else {
    return robust_dif<T>(lhs.pos() - rhs, lhs.neg());
  }
}

template<typename T>
robust_dif<T> operator-(const T& lhs, const robust_dif<T>& rhs) {
  if (!is_neg(lhs)) {
    return robust_dif<T>(lhs + rhs.neg(), rhs.pos());
  } else {
    return robust_dif<T>(rhs.neg(), rhs.pos() - lhs);
  }
}

template<typename T>
robust_dif<T> operator*(const robust_dif<T>& lhs,
                        const robust_dif<T>& rhs) {
  T res_pos = lhs.pos() * rhs.pos() + lhs.neg() * rhs.neg();
  T res_neg = lhs.pos() * rhs.neg() + lhs.neg() * rhs.pos();
  return robust_dif<T>(res_pos, res_neg);
}

template<typename T>
robust_dif<T> operator*(const robust_dif<T>& lhs, const T& val) {
  if (!is_neg(val)) {
    return robust_dif<T>(lhs.pos() * val, lhs.neg() * val);
  } else {
    return robust_dif<T>(-lhs.neg() * val, -lhs.pos() * val);
  }
}

template<typename T>
robust_dif<T> operator*(const T& val, const robust_dif<T>& rhs) {
  if (!is_neg(val)) {
    return robust_dif<T>(val * rhs.pos(), val * rhs.neg());
  } else {
    return robust_dif<T>(-val * rhs.neg(), -val * rhs.pos());
  }
}

template<typename T>
robust_dif<T> operator/(const robust_dif<T>& lhs, const T& val) {
  if (!is_neg(val)) {
    return robust_dif<T>(lhs.pos() / val, lhs.neg() / val);
  } else {
    return robust_dif<T>(-lhs.neg() / val, -lhs.pos() / val);
  }
}

// Used to compute expressions that operate with sqrts with predefined
// relative error. Evaluates expressions of the next type:
// sum(i = 1 .. n)(A[i] * sqrt(B[i])), 1 <= n <= 4.
template <typename _int, typename _fpt, typename _converter>
class robust_sqrt_expr {
 public:
  enum MAX_RELATIVE_ERROR {
    MAX_RELATIVE_ERROR_EVAL1 = 4,
    MAX_RELATIVE_ERROR_EVAL2 = 7,
    MAX_RELATIVE_ERROR_EVAL3 = 16,
    MAX_RELATIVE_ERROR_EVAL4 = 25
  };

  // Evaluates expression (re = 4 EPS):
  // A[0] * sqrt(B[0]).
  _fpt eval1(_int* A, _int* B) {
    _fpt a = convert(A[0]);
    _fpt b = convert(B[0]);
    return a * get_sqrt(b);
  }

  // Evaluates expression (re = 7 EPS):
  // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]).
  _fpt eval2(_int* A, _int* B) {
    _fpt a = eval1(A, B);
    _fpt b = eval1(A + 1, B + 1);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    return convert(A[0] * A[0] * B[0] - A[1] * A[1] * B[1]) / (a - b);
  }

  // Evaluates expression (re = 16 EPS):
  // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) + A[2] * sqrt(B[2]).
  _fpt eval3(_int* A, _int* B) {
    _fpt a = eval2(A, B);
    _fpt b = eval1(A + 2, B + 2);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    tA[3] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] - A[2] * A[2] * B[2];
    tB[3] = 1;
    tA[4] = A[0] * A[1] * 2;
    tB[4] = B[0] * B[1];
    return eval2(tA + 3, tB + 3) / (a - b);
  }


  // Evaluates expression (re = 25 EPS):
  // A[0] * sqrt(B[0]) + A[1] * sqrt(B[1]) +
  // A[2] * sqrt(B[2]) + A[3] * sqrt(B[3]).
  _fpt eval4(_int* A, _int* B) {
    _fpt a = eval2(A, B);
    _fpt b = eval2(A + 2, B + 2);
    if ((!is_neg(a) && !is_neg(b)) ||
        (!is_pos(a) && !is_pos(b)))
      return a + b;
    tA[0] = A[0] * A[0] * B[0] + A[1] * A[1] * B[1] -
            A[2] * A[2] * B[2] - A[3] * A[3] * B[3];
    tB[0] = 1;
    tA[1] = A[0] * A[1] * 2;
    tB[1] = B[0] * B[1];
    tA[2] = A[2] * A[3] * -2;
    tB[2] = B[2] * B[3];
    return eval3(tA, tB) / (a - b);
  }

 private:
  _int tA[5];
  _int tB[5];
  _converter convert;
};
}  // detail
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_DETAIL_VORONOI_ROBUST_FPT

/* voronoi_robust_fpt.hpp
6efEOvbXvpw/Xt+H8wbG/Q79C0dO55FjFf0IIl5VMF8fExd248f7YJ9v4G/+Tjx340+xt7JD2H0TdjqKeiopvxv7Yr/jupn5uJZ2sIP8z9iXDMROxjM+4pArgP7ch730YZ/7OPbKevfQddhNIfH/E+T1GnHh64z7etZrxIXEScQ35mviP2i7F+g2ywKM4+nIIMMMOuyg0047yLBopx0UKdJBp50W7bRo0aKddthBBx1krEimRYMEyTRopkUCZhAggwwyCRikw0wyyCSDTDMIkEEmQTvINMNMMgwawH/PnnpiLXg5x53zO1+S7/beL1/SvZeqf35F7bHSc3NB9foNtaOq36/foPJ/psahE/PtAY2DM2rnVW4Oqp9Z+rDCOaT5g8rZUvXb059XfVF+vf5rHaf2fMte5efnNV62qn1TeZh3g9IpUqX5k9Kp6jD1w6qnl2ncqOehVUfo/tP0f1fquLWK1xKFZ/869aOqV/OVj1vUTu5ZofnwLSrHb+jzd+vzkvrRx9SOPav46bitCufWWWrP9f6A8mftYUrHd2u/V/mhcjnzAY0jChp/hJV/6oeeWqVtUOOOk1TuLtb5d6veXK/0U3u8SO3aOqX7Vp/qm0Hzx5TqwR80XmvVOFDbW9WOnaT43ni6vi/7reb7W1SfLlW6Z9Q/fEz9+PdVf96ned5WXecbah+V/yepXF9+UNffrfbJpHqs+15/ispRSPXjIT3/O0PtifqHJWk999L8jmw51P++rq3G33N+qPb8BLWzAY1Hnlb+Hqv2MqXx1O/VLqh+X/VZlYeJ71fV/6xoUX4eqXqp8C+dr/o78T2++vMZardWvqznKo8o3Deofq5UOELqD2dre7faoyaNQ3S/BWeqPdqh+q9wr1ug8G1ReFTPVp6qfu4l9c+ad563X+VW9WJOm8bdF6g++pXvt6v9nKV2o0n9xSWarzyt9kX9/fylE+2Kxi8mtUcrlR9rVW913Q1nKT9VLrb8VuVX7e11YeX7dWov96qeaB63Pq/+8Tc67jLNYzTfOnWh8vWzut4Rmo+pPF51suZxNyu/lK4HZmtccLrKd1Tla7Pq1TtUP5apf1L7MVfjvvvPUL+s9L7OOL7FRvUjv1K/daTyD4eem6nc637r3qPyf6/K4y/VD6se779H99e4/3K9X7JV8dTvY5YvUnmLKj97FS+1Yyt2KjyXTdPzUl23We2VtpuUbhuHVV5MCp/iu2qfrne42pkHVb7UHsydofmvxjfbjlb7q3xctV/j17LK23Eqz3oecO8uhUvt4vVPad5xvMrt5RovToyblE4bVD7mqV5tVrreqPtdc7LKiVXt+ojG3e9TOq9WuOtVn45SP5dV+/xBtTOvqB6crP5sm9JN85LpZ6i8Vyn8adXbj6j/0vPFBQnFc7bKvVH5crTaGafK1ymqZ2pH9p2r8DypflH9wvY9ql/r1I/v1rh+ueKndnKW4r/hgOqh0n3bJ1SefGqHFqrev1P5e7jmv7rvvP2q94ep/Ayo/Ol3aFvvVHnPaf889Qua565UeHcqn3dcpnKg9map2sFlZ+l85dPuosYNp+r51+9Vnr6h639F7YD6uSvvU33cpvmd8nmX2p0Dqkerp6k8LlM9e1792jzln0H9uMZp85Tv+9Uv3a/n4qv3qr+zqjwcrf55k673mtqZiObxKteL1qo8blf/pecMc/R8f7nm31Wqzyc9MzF/UzlUe712mvJpVPlm0zjoXvU7GbXPj6n/uVzlQ+Vukfrl9WcovdeoHK5X+3vHxPMOpW9S4/8jVC80Drwyq/L0R7Wzl6qerlL8L1L/dY3y8SRd92SFL6d+VfebfYXqjZ4PLbtR/bSOf0HvZ30=
*/