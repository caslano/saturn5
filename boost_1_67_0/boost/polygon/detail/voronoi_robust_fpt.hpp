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
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
*/